/*
 * Copyright (C) 2009-2010 Advanced Micro Devices, Inc.  All Rights Reserved.
 */

/*
 *  Copyright (C) 2007 QLogic Corporation.  All Rights Reserved.
 */

/*
 * Copyright 2003, 2004, 2005, 2006 PathScale, Inc.  All Rights Reserved.
 */

/*

  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if 
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan

*/


/* ====================================================================
 * ====================================================================
 *
 * Module: targ_const.c
 * $Revision: 1.21 $
 * $Date: 05/08/24 21:12:32-07:00 $
 * $Author: fchow@fluorspar.internal.keyresearch.com $
 * $Source: common/com/x8664/SCCS/s.targ_em_const.cxx $
 *
 * Revision history:
 *  10-Feb-95 - Original Version
 *
 * Description:
 *
 * This file was originally part of targ_const.c.  The CG-related routines
 * are moved into this file.
 *
 * Refer to targ_const.c for details of description.
 * ====================================================================
 * ====================================================================
 */

#include <stdint.h>
#include "elf_stuff.h"
#include <ctype.h>

#define USE_STANDARD_TYPES 1 
#include "defs.h"
#include "targ_const.h"
#include "targ_const_private.h"
#include "erglob.h"		    /* EC_Inv_Mtype */
#include "errors.h"		    /* Is_True(), ErrMsg(), etc. */
#include "config_asm.h"		    /* ASM_CMNT, etc. */

#ifndef QIKKI_BE
#include "stab.h"		    /* TY */
#endif /*!defined(QIKKI_BE)*/

#define APPEND_TO_DBUF(a,b) a = Targ_Append_To_Dbuf(a,b)

extern BOOL CG_emit_non_gas_syntax;


// has char that can't be printed in string directive
static BOOL
Has_Control_Char (char *str, INT len)
{
	INT i;
	for (i = 0; i < len; ++i) {
		if (iscntrl(str[i]))
			return TRUE;
		if (str[i] == '"')
			return TRUE;
		if (str[i] == '\\')
			return TRUE;
	}
	return FALSE;
}

static void 
emit_bytes( FILE *fl, char *str, INT32 len )
{
#define MAXIMUM_LEN 8
  INT ch, i;
  INT16 n_on_line = 0;
  for ( i=0; i<len; ++i ) {
    ch = str[i];
    fprintf ( fl, n_on_line ? ", " : "\t%s\t", AS_BYTE );
    fprintf ( fl, "0x%x", ch );
    n_on_line++;
    if ( n_on_line == MAXIMUM_LEN ) {
      fprintf ( fl, "\n" );
      n_on_line = 0;
    }
  }
#undef MAXIMUM_LEN
}

/* ====================================================================
 *
 * Targ_Emit_String
 *
 * This routine emits constant strings to the file fl.  The string is
 * defined by a pointer (str) and a length (len).  This routine must
 * *always* output assembler commands which will occupy *exactly* len 
 * bytes in the .o file, since the caller is relying on that.  If the 
 * str[len-1] is not the null byte, then the caller must output one.
 * 
 * loc is the offset from the appropriate symbol at which we begin 
 * putting out characters.  This is used for a comment in the output 
 * .s file only, not for any real purpose. If loc is 0, the comment
 * is not written out (it has already been written out).
 *
 * ====================================================================
 */
void
Targ_Emit_String ( FILE *fl, char *str, INT32 len, INTSC loc )
{
#define MAX_LEN 8
    INT ch, i;
    INT16 n_on_line = 0;
    char dbuf[(1+MAX_LEN)*4], *dptr;
    dptr = dbuf;

    if (loc != 0)
	fprintf(fl, "\t%s offset %1ld\n", ASM_CMNT, loc);
    
    // if simple string, print as such
    if (len < 80 && str[len-1] == '\0' && ! Has_Control_Char(str,len-1)) {
	if (CG_emit_non_gas_syntax)
	  fprintf(fl, "\t%s \"%s\\0\"\n", ".ascii", str);
	else fprintf(fl, "\t%s \"%s\"\n", AS_STRING, str);
	return;
    }
    for ( i=0; i<len; ++i ) {
	ch = str[i];
	fprintf ( fl, n_on_line ? ", " : "\t%s\t", AS_BYTE );
	fprintf ( fl, "0x%x", ch );
	APPEND_TO_DBUF(dptr, ch);
	++n_on_line;
	if ( n_on_line == MAX_LEN ) {
	    *dptr = '\0';
	    fprintf(fl, "\t%s %s", ASM_CMNT, dbuf);
	    dptr = dbuf;
	    fprintf ( fl, "\n" );
	    n_on_line = 0;
	}
    }
    *dptr = '\0';
    fprintf(fl, "\t%s %s", ASM_CMNT, dbuf);
    dptr = dbuf;
    fprintf(fl, "\n");

#if TARGET_88000 || TARGET_spc00
    INT l, line_len, ch, i;

    fprintf(fl, "\t%s loc %1d\n", ASM_CMNT, loc);
#define MAX_LEN 60
    line_len = -1; 
    for (i=0; i<len; i++) {
	ch = str[i] & 0xff;
	if (ch < ' ' || ch > '~' || ch == '\\' || ch == '"')
	    l = 4;
	else 
	    l = 1;
	if (line_len > (MAX_LEN-l)) {
	    fprintf(fl, "\"\n");
	    line_len = -1;
	}
	if (line_len < 0) {
	    if (CG_emit_non_gas_syntax)
	      fprintf(fl, "\t%s\t\"", ".ascii" );
	    else fprintf(fl, "\t%s\t\"", AS_STRING );
	    line_len = 0;
	} 
	if (l == 4)
	    fprintf(fl, "\\%03o", ch);
	else
	    fprintf(fl, "%c", ch);
	line_len +=  l;
    }
    Is_True(line_len, ("Expecting non zero line_len"));
    if (line_len >= 0) 
	fprintf(fl, "\"\n");
#endif /* TARGET_88000 || TARGET_spc00 */
} /* Targ_Emit_String */

/* ====================================================================
 *
 * Emit_Repeated_Constant
 *
 * Emit a simple numeric constant one or more times.
 * To conserve space we try to emit more than one value per directive.
 *
 * ====================================================================
 */

static void Emit_Repeated_Constant(
  FILE *fl,			/* file which to write */
  const char *dir, 		/* directive name */
  INT64 val,			/* value to be written */
  INTSC rc,			/* repeat count */
  INTSC maxc)			/* max count per directive */
{
  INTSC this_rc;
  do {
    INT i;
    this_rc = MIN(rc, maxc);
    if ((val >= INT32_MIN) && (val <= INT32_MAX)) 
      fprintf(fl, "\t%s\t%lld", dir, val);
    else
      fprintf(fl, "\t%s\t%#llx", dir, val);
    for (i = 1; i < this_rc; ++i) {
      if ((val >= INT32_MIN) && (val <= INT32_MAX)) 
	fprintf(fl, ", %lld", val);
      else
	fprintf(fl, ", %#llx", val);
    }
    fprintf(fl, "\n");
  } while (rc -= this_rc);
}

/* ====================================================================
 *
 * Targ_Emit_Const
 *
 * Print routine to be used to print constants on the assembly file.
 *
 * NOTE: There is a parallel routine to this one that writes out TCONs
 *       to elf sections. Any changes here should be reflected in the 
 *       Em_Targ_Emit_Const routine .
 *
 * ====================================================================
 */

void
Targ_Emit_Const (FILE *fl,	    /* File to which to write */
		 TCON tc,	    /* Constant to be written */
		 BOOL add_null,	    /* whether to add null to strings */
		 INTSC rc,	    /* Repeat count */
		 INTSC loc )	    /* Location (i.e. offset from some base) */
{
    Is_True ( rc > 0, ("Targ_Emit_Const: repeat count is %d", rc ) );
    
    /* loc only used here (in a comment in the output file) */
    fprintf(fl, "\t%s offset %1ld\n", ASM_CMNT, loc);

    /* Loop until the repeat count is exhausted. For simple constants we'll
     * optimize the emission, otherwise we just repeat the whole directive.
     */
    while (rc) {
      switch (TCON_ty(tc)) {
      case MTYPE_I1:
      case MTYPE_U1:
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v0(tc) & 0xff, rc, 10 );
	rc = 0;
	break;

      case MTYPE_I2:
      case MTYPE_U2:
	if (CG_emit_non_gas_syntax)
	  Emit_Repeated_Constant ( fl, ".half", TCON_v0(tc) & 0xffff, rc, 8 );
	else Emit_Repeated_Constant ( fl,
		((loc % 2) == 0 ? AS_HALF : AS_HALF_UNALIGNED), 
		TCON_v0(tc) & 0xffff, rc, 8 );
	rc = 0;
	break;

      case MTYPE_I4:
      case MTYPE_U4:
	if (CG_emit_non_gas_syntax)
	  Emit_Repeated_Constant ( fl, ".word", TCON_v0(tc), rc, 4 );
	else Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_v0(tc), rc, 4 );
	rc = 0;
	break;

      case MTYPE_I8:
      case MTYPE_U8:
	if (CG_emit_non_gas_syntax)
	  Emit_Repeated_Constant ( fl, ".dword", TCON_I8(tc), rc, 2 );
	else Emit_Repeated_Constant ( fl, 
		((loc % 8) == 0 ? AS_DWORD : AS_DWORD_UNALIGNED), 
		TCON_I8(tc), rc, 2 );
	rc = 0;
	break;

      case MTYPE_F4: {
	if (CG_emit_non_gas_syntax)
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	else Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	fprintf(fl, "\t%s float %#g\n", ASM_CMNT, TCON_R4(tc) );
	rc = 0;
	break;
        }

      case MTYPE_C4: {
	INT i;
        char *p = (char *) & TCON_R4(tc);
	emit_bytes( fl, p, sizeof(TCON_R4(tc)) );
	fprintf(fl, "\t%s complex float real part %#g\n", ASM_CMNT, TCON_R4(tc) );

        p = (char *) & TCON_IR4(tc);
	emit_bytes( fl, p, sizeof(TCON_IR4(tc)) );
	fprintf(fl, "\t%s complex float imag part %#g\n", ASM_CMNT, TCON_IR4(tc) );
	--rc;
	break;
	}

      case MTYPE_F8: {
	/* Emit doubles as two words, to match how the constants are
           handled in the code. */
	if (CG_emit_non_gas_syntax) {
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	}
	else {
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	}

	fprintf(fl, "\t%s double %#g\n", ASM_CMNT, TCON_R8(tc) );
	--rc;
	break;
	}

      case MTYPE_C8: 
      case MTYPE_V16C8: {
	INT i;
        char *p = (char *) & TCON_R8(tc);
	emit_bytes( fl, p, sizeof(TCON_R8(tc)) );
	fprintf(fl, "\t%s complex double real part %#g\n", ASM_CMNT, TCON_R8(tc) );

        p = (char *) & TCON_IR8(tc);
	emit_bytes( fl, p, sizeof(TCON_IR8(tc)) );
	fprintf(fl, "\t%s complex double imag part %#g\n", ASM_CMNT, TCON_IR8(tc) );
	--rc;
	break;
	}

      case MTYPE_F10: {
        char *p = (char *) & TCON_R16(tc);
        // Force the size of MTYPE_F10 to 16 for 64bit code and 12 for 32bit code
	emit_bytes( fl, p, Is_Target_64bit() ? 16 : 12 /* sizeof(TCON_R16(tc)) */ );
	fprintf(fl, "\t%s long double %#Lg\n", ASM_CMNT, TCON_R16(tc) );
	--rc;
	break;
	}

      case MTYPE_FQ: {
        char *p = (char *) & TCON_R16(tc);
        // Force the size of MTYPE_FQ to 16 for 64bit code and 12 for 32bit code
	emit_bytes( fl, p, Is_Target_64bit() ? 16 : 12 /* sizeof(TCON_R16(tc)) */ );
	fprintf(fl, "\t%s quad %#Lg\n", ASM_CMNT, TCON_R16(tc) );
	--rc;
	break;
	}

      case MTYPE_C10: {
	INT i;
        char *p = (char *) & TCON_R16(tc);
	emit_bytes( fl, p, sizeof(TCON_R16(tc)) );
	fprintf(fl, "\t%s complex long double real part %#Lg\n", ASM_CMNT, TCON_R16(tc) );

        p = (char *) & TCON_IR16(tc);
	emit_bytes( fl, p, sizeof(TCON_IR16(tc)) );
	fprintf(fl, "\t%s complex long double imag part %#Lg\n", ASM_CMNT, TCON_IR16(tc) );
	--rc;
	break;
	}

      case MTYPE_CQ: {
	INT i;
        char *p = (char *) & TCON_R16(tc);
	emit_bytes( fl, p, sizeof(TCON_R16(tc)) );
	fprintf(fl, "\t%s complex quad real part %#Lg\n", ASM_CMNT, TCON_R16(tc) );

        p = (char *) & TCON_IR16(tc);
	emit_bytes( fl, p, sizeof(TCON_IR16(tc)) );
	fprintf(fl, "\t%s complex quad imag part %#Lg\n", ASM_CMNT, TCON_IR16(tc) );
	--rc;
	break;
	}

      case MTYPE_STRING: {
	INTSC count;
#if defined(KEY) && ! defined(BUILD_OS_DARWIN)	// Use .rept/.endr to reduce .s file size.  Bug 4620.
	if (rc > 1)
	  fprintf(fl, ".rept %ld\n", rc);
	char *p = Index_to_char_array (TCON_cp(tc));
	Targ_Emit_String ( fl, p, TCON_len(tc) + (add_null ? 1 : 0), 0 );
	if (rc > 1)
	  fprintf(fl, ".endr\n");
#else
	for (count=0; count<rc; ++count) {
	  char *p = Index_to_char_array (TCON_cp(tc));
	  Targ_Emit_String ( fl, p, TCON_len(tc) + (add_null ? 1 : 0), 0 );
	}
#endif
	rc = 0;
	break;
	}

      case MTYPE_V8I1:
      case MTYPE_M8I1:
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v0(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v0(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v0(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v0(tc)>>24) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v1(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v1(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v1(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v1(tc)>>24) & 0xff, rc, 10 );
	rc = 0;
	break;

      case MTYPE_V8I2:
      case MTYPE_M8I2:
	if (CG_emit_non_gas_syntax) {
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v0(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v0(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v1(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v1(tc)>>16) & 0xffff, rc, 8 );
	}
	else {	  
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v0(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v0(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v1(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v1(tc)>>16) & 0xffff, rc, 8 );
	}
	rc = 0;
	break;

      case MTYPE_V8I4:
      case MTYPE_M8I4:
	{
	  if (CG_emit_non_gas_syntax) {
	    Emit_Repeated_Constant ( fl, ".word", TCON_v0(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, ".word", TCON_v1(tc), rc, 4 );
	  } else {
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v0(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v1(tc), rc, 4 );
	  }
	  rc = 0;
	  break;
	}

      case MTYPE_V8I8:
	if (CG_emit_non_gas_syntax)
	  Emit_Repeated_Constant ( fl, ".dword", TCON_ll0(tc), rc, 2 );
	else Emit_Repeated_Constant ( fl, 
		((loc % 8) == 0 ? AS_DWORD : AS_DWORD_UNALIGNED), 
		TCON_ll0(tc), rc, 2 );
	rc = 0;
	break;

      case MTYPE_V16F4: {
	if (CG_emit_non_gas_syntax) {
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	} 
	else {
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	}
	fprintf(fl, "\t%s float[4] %#g %#g %#g %#g\n", ASM_CMNT, 
		TCON_R4(tc), TCON_R4(tc), TCON_R4(tc), TCON_R4(tc));
	rc = 0;
	break;
        }
      case MTYPE_V16F8: {
	/* Emit doubles as two words, to match how the constants are
           handled in the code. */
	if (CG_emit_non_gas_syntax) {
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	}
	else {
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	}

	fprintf(fl, "\t%s double[2] %#g %#g\n", ASM_CMNT, 
		TCON_R8(tc), TCON_R8(tc) );
	--rc;
	break;
        }

      case MTYPE_V16C4: {
	INT i;
        char *p = (char *) & TCON_R4(tc);
	emit_bytes( fl, p, sizeof(TCON_R4(tc)) );
	fprintf(fl, "\t%s complex float real part %#g\n", ASM_CMNT, TCON_R4(tc) );

        p = (char *) & TCON_IR4(tc);
	emit_bytes( fl, p, sizeof(TCON_IR4(tc)) );
	fprintf(fl, "\t%s complex float imag part %#g\n", ASM_CMNT, TCON_IR4(tc) );

        p = (char *) & TCON_R4(tc);
	emit_bytes( fl, p, sizeof(TCON_R4(tc)) );
	fprintf(fl, "\t%s complex float real part %#g\n", ASM_CMNT, TCON_R4(tc) );

        p = (char *) & TCON_IR4(tc);
	emit_bytes( fl, p, sizeof(TCON_IR4(tc)) );
	fprintf(fl, "\t%s complex float imag part %#g\n", ASM_CMNT, TCON_IR4(tc) );
	--rc;
	break;
        }

      case MTYPE_V16I1:
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v0(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v0(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v0(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v0(tc)>>24) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v1(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v1(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v1(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v1(tc)>>24) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v2(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v2(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v2(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v2(tc)>>24) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v3(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v3(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v3(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v3(tc)>>24) & 0xff, rc, 10 );
	rc = 0;
	break;

      case MTYPE_V16I2:
	if (CG_emit_non_gas_syntax) {
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v0(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v0(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v1(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v1(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v2(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v2(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v3(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v3(tc)>>16) & 0xffff, rc, 8 );
	}
	else {	  
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v0(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v0(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v1(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v1(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v2(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v2(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v3(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v3(tc)>>16) & 0xffff, rc, 8 );
	}
	rc = 0;
	break;

      case MTYPE_V16I4: 
	{
	  if (CG_emit_non_gas_syntax) {
	    Emit_Repeated_Constant ( fl, ".word", TCON_v0(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, ".word", TCON_v1(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, ".word", TCON_v2(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, ".word", TCON_v3(tc), rc, 4 );
	  } else {
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v0(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v1(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v2(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v3(tc), rc, 4 );
	  }
	  rc = 0;
	  break;
	}

      case MTYPE_V16I8:
	{
	  if (CG_emit_non_gas_syntax) {
	    Emit_Repeated_Constant ( fl, ".dword", TCON_ll0(tc), rc, 2 );
	    Emit_Repeated_Constant ( fl, ".dword", TCON_ll1(tc), rc, 2 );
	  } else {
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 8) == 0 ? AS_DWORD : AS_DWORD_UNALIGNED), 
				     TCON_ll0(tc), rc, 2 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 8) == 0 ? AS_DWORD : AS_DWORD_UNALIGNED), 
				     TCON_ll1(tc), rc, 2 );
	  }
	  rc = 0;
	  break;
	}

      case MTYPE_V32F4: {
	if (CG_emit_non_gas_syntax) {
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	} 
	else {
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	}
	fprintf(fl, "\t%s float[8] %#g %#g %#g %#g %#g %#g %#g %#g\n", ASM_CMNT, 
		TCON_R4(tc), TCON_R4(tc), TCON_R4(tc), TCON_R4(tc),
		TCON_R4(tc), TCON_R4(tc), TCON_R4(tc), TCON_R4(tc));
	rc = 0;
	break;
        }
      case MTYPE_V32F8: {
	/* Emit doubles as two words, to match how the constants are
           handled in the code. */
	if (CG_emit_non_gas_syntax) {
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	}
	else {
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	}

	fprintf(fl, "\t%s double[4] %#g %#g %#g %#g\n", ASM_CMNT, 
		TCON_R8(tc), TCON_R8(tc), TCON_R8(tc), TCON_R8(tc) );
	--rc;
	break;
        }

      case MTYPE_V32C4: {
	INT i;
        char *p = (char *) & TCON_R4(tc);
	emit_bytes( fl, p, sizeof(TCON_R4(tc)) );
	fprintf(fl, "\t%s complex float real part %#g\n", ASM_CMNT, TCON_R4(tc) );

        p = (char *) & TCON_IR4(tc);
	emit_bytes( fl, p, sizeof(TCON_IR4(tc)) );
	fprintf(fl, "\t%s complex float imag part %#g\n", ASM_CMNT, TCON_IR4(tc) );

        p = (char *) & TCON_R4(tc);
	emit_bytes( fl, p, sizeof(TCON_R4(tc)) );
	fprintf(fl, "\t%s complex float real part %#g\n", ASM_CMNT, TCON_R4(tc) );

        p = (char *) & TCON_IR4(tc);
	emit_bytes( fl, p, sizeof(TCON_IR4(tc)) );
	fprintf(fl, "\t%s complex float imag part %#g\n", ASM_CMNT, TCON_IR4(tc) );

        p = (char *) & TCON_R4(tc);
	emit_bytes( fl, p, sizeof(TCON_R4(tc)) );
	fprintf(fl, "\t%s complex float real part %#g\n", ASM_CMNT, TCON_R4(tc) );

        p = (char *) & TCON_IR4(tc);
	emit_bytes( fl, p, sizeof(TCON_IR4(tc)) );
	fprintf(fl, "\t%s complex float imag part %#g\n", ASM_CMNT, TCON_IR4(tc) );

        p = (char *) & TCON_R4(tc);
	emit_bytes( fl, p, sizeof(TCON_R4(tc)) );
	fprintf(fl, "\t%s complex float real part %#g\n", ASM_CMNT, TCON_R4(tc) );

        p = (char *) & TCON_IR4(tc);
	emit_bytes( fl, p, sizeof(TCON_IR4(tc)) );
	fprintf(fl, "\t%s complex float imag part %#g\n", ASM_CMNT, TCON_IR4(tc) );

	--rc;
	break;
        }

      case MTYPE_V32I1:
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v0(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v0(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v0(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v0(tc)>>24) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v1(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v1(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v1(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v1(tc)>>24) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v2(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v2(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v2(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v2(tc)>>24) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v3(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v3(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v3(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v3(tc)>>24) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v4(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v4(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v4(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v4(tc)>>24) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v5(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v5(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v5(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v5(tc)>>24) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v6(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v6(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v6(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v6(tc)>>24) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, TCON_v7(tc) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v7(tc)>>8) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v7(tc)>>16) & 0xff, rc, 10 );
	Emit_Repeated_Constant ( fl, AS_BYTE, (TCON_v7(tc)>>24) & 0xff, rc, 10 );
	rc = 0;
	break;

      case MTYPE_V32I2:
	if (CG_emit_non_gas_syntax) {
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v0(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v0(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v1(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v1(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v2(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v2(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v3(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v3(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v4(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v4(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v5(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v5(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v6(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v6(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   TCON_v7(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl, ".half", 
				   (TCON_v7(tc)>>16) & 0xffff, rc, 8 );
	}
	else {	  
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v0(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v0(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v1(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v1(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v2(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v2(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v3(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v3(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v4(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v4(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v5(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v5(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v6(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v6(tc)>>16) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   TCON_v7(tc) & 0xffff, rc, 8 );
	  Emit_Repeated_Constant ( fl,
				   ((loc % 2) == 0 ? AS_HALF : 
				    AS_HALF_UNALIGNED), 
				   (TCON_v7(tc)>>16) & 0xffff, rc, 8 );
	}
	rc = 0;
	break;

      case MTYPE_V32I4: 
	{
	  if (CG_emit_non_gas_syntax) {
	    Emit_Repeated_Constant ( fl, ".word", TCON_v0(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, ".word", TCON_v1(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, ".word", TCON_v2(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, ".word", TCON_v3(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, ".word", TCON_v4(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, ".word", TCON_v5(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, ".word", TCON_v6(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, ".word", TCON_v7(tc), rc, 4 );
	  } else {
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v0(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v1(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v2(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v3(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v4(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v5(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v6(tc), rc, 4 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
				     TCON_v7(tc), rc, 4 );
	  }
	  rc = 0;
	  break;
	}

      case MTYPE_V32I8:
	{
	  if (CG_emit_non_gas_syntax) {
	    Emit_Repeated_Constant ( fl, ".dword", TCON_ll0(tc), rc, 2 );
	    Emit_Repeated_Constant ( fl, ".dword", TCON_ll1(tc), rc, 2 );
	    Emit_Repeated_Constant ( fl, ".dword", TCON_ll2(tc), rc, 2 );
	    Emit_Repeated_Constant ( fl, ".dword", TCON_ll3(tc), rc, 2 );
	  } else {
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 8) == 0 ? AS_DWORD : AS_DWORD_UNALIGNED), 
				     TCON_ll0(tc), rc, 2 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 8) == 0 ? AS_DWORD : AS_DWORD_UNALIGNED), 
				     TCON_ll1(tc), rc, 2 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 8) == 0 ? AS_DWORD : AS_DWORD_UNALIGNED), 
				     TCON_ll2(tc), rc, 2 );
	    Emit_Repeated_Constant ( fl, 
				     ((loc % 8) == 0 ? AS_DWORD : AS_DWORD_UNALIGNED), 
				     TCON_ll3(tc), rc, 2 );
	  }
	  rc = 0;
	  break;
	}

      default:
	ErrMsg ( EC_Inv_Mtype, Mtype_Name(TCON_ty(tc)),
		"Targ_Emit_Const" );
    }
  }
} /* Targ_Emit_Const */

#ifdef KEY
const char * ULEBDIR = ".uleb128";
const char * SLEBDIR = ".sleb128";

// Version of Targ_Emit_Const to emit exception handling constants, which
// use the .uleb128 directive
// Encode the constants if required according to 'format'
void
Targ_Emit_EH_Const (FILE *fl,	    /* File to which to write */
		 TCON tc,	    /* Constant to be written */
		 BOOL add_null,	    /* whether to add null to strings */
		 INTSC rc,	    /* Repeat count */
		 INTSC loc,	    /* Location (i.e. offset from some base) */
		 INT format)	    /* Indicates encoding */
{
    Is_True ( rc > 0, ("Targ_Emit_Const: repeat count is %d", rc ) );
    const char * encoding = ULEBDIR;

    if (format == INITVFLAGS_ACTION_REC)
    	encoding = SLEBDIR;
    
    /* loc only used here (in a comment in the output file) */
    fprintf(fl, "\t%s offset %1ld\n", ASM_CMNT, loc);

    /* Loop until the repeat count is exhausted. For simple constants we'll
     * optimize the emission, otherwise we just repeat the whole directive.
     */
    while (rc) {
      switch (TCON_ty(tc)) {
      case MTYPE_I1:
      case MTYPE_U1:
	Emit_Repeated_Constant ( fl, encoding, TCON_v0(tc) & 0xff, rc, 10 );
	rc = 0;
	break;

      case MTYPE_I2:
      case MTYPE_U2:
	Emit_Repeated_Constant ( fl, encoding, TCON_v0(tc) & 0xffff, rc, 8 );
	rc = 0;
	break;

      case MTYPE_I4:
      case MTYPE_U4:
	Emit_Repeated_Constant ( fl, encoding, TCON_v0(tc), rc, 4 );
	rc = 0;
	break;

      case MTYPE_I8:
      case MTYPE_U8:
	Emit_Repeated_Constant ( fl, encoding, TCON_I8(tc), rc, 2 );
	rc = 0;
	break;

      case MTYPE_F4: {
	Emit_Repeated_Constant ( fl, encoding, TCON_word0(tc), rc, 4 );
	rc = 0;
	break;
        }

      case MTYPE_C4: {
	INT i;
        char *p = (char *) & TCON_R4(tc);
	emit_bytes( fl, p, sizeof(TCON_R4(tc)) );
	fprintf(fl, "\t%s complex float real part %#g\n", ASM_CMNT, TCON_R4(tc) );

        p = (char *) & TCON_IR4(tc);
	emit_bytes( fl, p, sizeof(TCON_IR4(tc)) );
	fprintf(fl, "\t%s complex float imag part %#g\n", ASM_CMNT, TCON_IR4(tc) );
	--rc;
	break;
	}

      case MTYPE_F8: {
	/* Emit doubles as two words, to match how the constants are
           handled in the code. */
	  Emit_Repeated_Constant ( fl, encoding, 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, encoding, 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );

	fprintf(fl, "\t%s double %#g\n", ASM_CMNT, TCON_R8(tc) );
	--rc;
	break;
	}

      case MTYPE_C8: {
	INT i;
        char *p = (char *) & TCON_R8(tc);
	emit_bytes( fl, p, sizeof(TCON_R8(tc)) );
	fprintf(fl, "\t%s complex double real part %#g\n", ASM_CMNT, TCON_R8(tc) );

        p = (char *) & TCON_IR8(tc);
	emit_bytes( fl, p, sizeof(TCON_IR8(tc)) );
	fprintf(fl, "\t%s complex double imag part %#g\n", ASM_CMNT, TCON_IR8(tc) );
	--rc;
	break;
	}

      case MTYPE_F10: {
        char *p = (char *) & TCON_R16(tc);
	emit_bytes( fl, p, sizeof(TCON_R16(tc)) );
	fprintf(fl, "\t%s long double %#Lg\n", ASM_CMNT, TCON_R16(tc) );
	--rc;
	break;
	}

      case MTYPE_FQ: {
        char *p = (char *) & TCON_R16(tc);
	emit_bytes( fl, p, sizeof(TCON_R16(tc)) );
	fprintf(fl, "\t%s quad %#Lg\n", ASM_CMNT, TCON_R16(tc) );
	--rc;
	break;
	}

      case MTYPE_C10: {
	INT i;
        char *p = (char *) & TCON_R16(tc);
	emit_bytes( fl, p, sizeof(TCON_R16(tc)) );
	fprintf(fl, "\t%s complex long double real part %#Lg\n", ASM_CMNT, TCON_R16(tc) );

        p = (char *) & TCON_IR16(tc);
	emit_bytes( fl, p, sizeof(TCON_IR16(tc)) );
	fprintf(fl, "\t%s complex long double imag part %#Lg\n", ASM_CMNT, TCON_IR16(tc) );
	--rc;
	break;
	}

      case MTYPE_CQ: {
	INT i;
        char *p = (char *) & TCON_R16(tc);
	emit_bytes( fl, p, sizeof(TCON_R16(tc)) );
	fprintf(fl, "\t%s complex quad real part %#Lg\n", ASM_CMNT, TCON_R16(tc) );

        p = (char *) & TCON_IR16(tc);
	emit_bytes( fl, p, sizeof(TCON_IR16(tc)) );
	fprintf(fl, "\t%s complex quad imag part %#Lg\n", ASM_CMNT, TCON_IR16(tc) );
	--rc;
	break;
	}

      case MTYPE_STRING: {
	INTSC count;
	for (count=0; count<rc; ++count) {
	  char *p = Index_to_char_array (TCON_cp(tc));
	  Targ_Emit_String ( fl, p, TCON_len(tc) + (add_null ? 1 : 0), 0 );
	}
	rc = 0;
	break;
	}

      case MTYPE_V16F4: {
	if (CG_emit_non_gas_syntax) {
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, ".word", TCON_word0(tc), rc, 4 );
	} 
	else {
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(tc), rc, 4 );
	}
	fprintf(fl, "\t%s float[4] %#g %#g %#g %#g\n", ASM_CMNT, 
		TCON_R4(tc), TCON_R4(tc), TCON_R4(tc), TCON_R4(tc));
	rc = 0;
	break;
        }
      case MTYPE_V16F8: {
	/* Emit doubles as two words, to match how the constants are
           handled in the code. */
	if (CG_emit_non_gas_syntax) {
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, ".word", 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	}
	else {
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Lo(tc)), 1, 4 );
	  Emit_Repeated_Constant ( fl, 
		((loc % 4) == 0 ? AS_WORD : AS_WORD_UNALIGNED), 
		TCON_word0(Extract_Double_Hi(tc)), 1, 4 );
	}

	fprintf(fl, "\t%s double[2] %#g %#g\n", ASM_CMNT, 
		TCON_R8(tc), TCON_R8(tc) );
	--rc;
	break;
	}
      default:
	ErrMsg ( EC_Inv_Mtype, Mtype_Name(TCON_ty(tc)),
		"Targ_Emit_Const" );
    }
  }
} /* Targ_Emit_EH_Const */
#endif // KEY


#if defined(BACK_END) || defined(QIKKI_BE)
#if defined(BUILD_OS_DARWIN)
void Em_Targ_Emit_Const (void *, TCON, BOOL, INTSC) {}
#else /* defined(BUILD_OS_DARWIN) */
/* ====================================================================
 *
 * Em_Targ_Emit_Const
 *
 * Write out constant to the section.
 *
 * ====================================================================
 */

#include <elf.h>
#include "em_elf.h"

void
Em_Targ_Emit_Const (void *scn,	    /* Section to which to write */
		    TCON tc,	    /* Constant to be written */
		    BOOL add_null,  /* whether to add null to strings */
		    INTSC rc)	    /* Repeat count */
{
    INTSC count;
    pSCNINFO section = (pSCNINFO)scn;

    Is_True ( rc > 0,  ("Em_Targ_Emit_Const: repeat count is %d", rc ) );

    switch (TCON_ty(tc)) {
    case MTYPE_I1:
    case MTYPE_U1:
	for (count = 0; count < rc; count++) {
	    mINT8 value = TCON_v0(tc);
	    Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
	}
	break;

    case MTYPE_I2:
    case MTYPE_U2:
	for (count = 0; count < rc; count++) {
	    mINT16 value = TCON_v0(tc);
	    Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
	}
	break;

    case MTYPE_I4:
    case MTYPE_U4:
	for (count = 0; count < rc; count++) {
	    mINT32 value = TCON_v0(tc);
	    Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
	}
	break;

    case MTYPE_I8:
    case MTYPE_U8:
	for (count = 0; count < rc; count++) {
	    mUINT64 value = TCON_U8(tc);
	    Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
	}
	break;

    case MTYPE_F4:
	for (count = 0; count < rc; count++) {
	    float value = TCON_R4(tc);
	    Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
	}
	break;

    case MTYPE_C4:
	for (count = 0; count < rc; count++) {
	    float value = TCON_R4(tc);
	    Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
	    value = TCON_IR4(tc);
	    Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
	}
	break;

    case MTYPE_F8:
	for (count = 0; count < rc; count++) {
	    double value = TCON_R8(tc);
	    Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
	}
	break;

    case MTYPE_C8:
	for (count = 0; count < rc; count++) {
	    double value = TCON_R8(tc);
	    Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
	    value = TCON_IR8(tc);
	    Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
	}
	break;

    case MTYPE_F10:
        for (count = 0; count < rc; count++) {
            long double value = TCON_R16(tc);
            Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
        }
        break;

    case MTYPE_FQ:
	for (count = 0; count < rc; count++) {
	    double *pvalue = &(TCON_R8(tc));
	    Em_Add_Bytes_To_Scn (section, (char *) pvalue, sizeof(double), 1);
	    Em_Add_Bytes_To_Scn (section, (char *) (pvalue+1), sizeof(double), 1);
	}
	break;

    case MTYPE_C10:
	for (count = 0; count < rc; count++) {
	    long double value;
	    value = TCON_R16(tc);
	    Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
	    value = TCON_IR16(tc);
	    Em_Add_Bytes_To_Scn (section, (char *) &value, sizeof(value), 1);
	}
	break;

    case MTYPE_CQ:
	for (count = 0; count < rc; count++) {
	    double *pvalue = &(TCON_R8(tc));
	    Em_Add_Bytes_To_Scn (section, (char *) pvalue, sizeof(double), 1);
	    Em_Add_Bytes_To_Scn (section, (char *) (pvalue+1), sizeof(double), 1);
	    pvalue = &(TCON_IR8(tc));
	    Em_Add_Bytes_To_Scn (section, (char *) pvalue, sizeof(double), 1);
	    Em_Add_Bytes_To_Scn (section, (char *) (pvalue+1), sizeof(double), 1);
	}
	break;

    case MTYPE_STRING:
	for (count = 0; count < rc; count++) {
	    Em_Add_Bytes_To_Scn (section,
				 Index_to_char_array (TCON_cp(tc)),
		TCON_len(tc) + (add_null ? 1 : 0), 
		1);
	}
	break;

    default:
	Is_True ( FALSE, ( "Targ_Emit_Const can not handle type %s", 
			  Mtype_Name(TCON_ty(tc)) ) );
    }
} /* Em_Targ_Emit_Const */
#endif /* defined(BUILD_OS_DARWIN) */
#endif /* BACK_END */

#if !defined(MONGOOSE_BE) && !defined(QIKKI_BE)
void
Targ_Emit_Space( FILE *fl, INT len, INT loc)
{
    fprintf(fl, "\t%s %1d\t%s %1d\n", AS_SPACE, len, ASM_CMNT, loc);
}

void
Targ_Emit_Cmt(fl, str)
FILE *fl;
char *str;
{
    fprintf(fl, "\t%s %s\n", ASM_CMNT, str);
}

/*----------------------------------------------------------------------
 *	Print on the file 'fl' the length of the dimension described
 *	as going from 'tree_lower' to 'tree_upper'.  This can only be
 *	done correctly at compile-time when both 'tree_lower' and
 *	'tree_upper' are NDs for constants (maybe even integer
 *	constants?).  If they are not both integer constants, just print
 *	a default dimension of '1'.
 *--------------------------------------------------------------------*/
void
Targ_Emit_Dim (FILE *fl, TY *ty, INT dim)
{
#if TODO_MONGOOSE
    INT32 coff_dim = 1;		    /* default value */
    ND *tree_lower;
    ND *tree_upper;
  
    Is_True(TY_kind(ty) == KIND_ARRAY, ("Non-array in Targ_Emit_Dim"));
    Is_True(dim >= 0 && dim < TY_AR_ndims(ty),
	    ("Illegal dimension %d in Targ_Emit_Dim", dim));

    tree_lower = TY_AR_fbnd(ty,dim);
    tree_upper = TY_AR_tbnd(ty,dim);
    if ( (tree_upper != NULL) && (tree_lower != NULL) ) {
	TCON tc_upper, tc_lower;
	if ( (Is_Const(tree_upper,&tc_upper) == MTYPE_I4) &&
	    (Is_Const(tree_lower,&tc_lower) == MTYPE_I4) ) {
	    INT32 upper_bound = TCON_v0(tc_upper);
	    INT32 lower_bound = TCON_v0(tc_lower);
	    coff_dim = upper_bound - lower_bound + 1;
	}
    }

    fprintf ( fl, "%d", coff_dim );
#endif /* TODO_MONGOOSE */
} /* Targ_Emit_Dim */
#endif /* !defined(MONGOOSE_BE) && !defined(QIKKI_BE) */
