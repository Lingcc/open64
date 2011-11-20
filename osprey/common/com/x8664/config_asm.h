/*
 * Copyright (C) 2009 Advanced Micro Devices, Inc.  All Rights Reserved.
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


#ifndef config_asm_INCLUDED
#define config_asm_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

/* ====================================================================
 * ====================================================================
 *
 * Module: config_asm.h
 * $Revision$
 * $Date$
 * $Author$
 * $Source$
 *
 * Revision history:
 *
 * Description:
 *
 * This file contains #defines which configure assembly code emission
 * to the current host assembler.  The intent is to isolate all
 * dependencies on the host's assembly language format and directives
 * here.
 *
 * ====================================================================
 * ====================================================================
 */


#ifdef _KEEP_RCS_ID
static char *config_asm_rcs_id = "$Source$ $Revision$";
#endif /* _KEEP_RCS_ID */

#define LABEL_PREFIX ".L"
#define Label_Name_Separator "_"
#define Temp_Symbol_Prefix Label_Name_Separator "temp" Label_Name_Separator

/* to distinguish from register names: */
#define Symbol_Name_Suffix ""

/* The following sprintf format is used to create a basic block label
 * from the BB id and the PU name:
 * Add prefix .L so that gdb does not print out the labels.
 */
#define BB_Label_Format	".LBB%d_%s"
#define END_Label_Format ".LDWend_%s"

/* The following sprintf format is used to create a basic block label
 * from a user label name and the PU name:
 */
#define User_Label_Format	".L_%s_%s"
#define User_Label_Number_Format	".L_%d_%d_%s"

/* The following sprintf format is used to create the magic label for
 * the common return point (if Only_1_Exit_Point is TRUE).
 */
#define Ret_Block_Label_Format	".RET_%s"

/* The following sprintf format to ensure correct alignment of
 * entry points:
 */
#define Entry_Point_Alignment_Format	"\t.align\t4\n"

/* The following sprintf formats define the mapping of objects in
 * various storage classes to the assembly code and symbol table
 * (naming) conventions of the target:
 *	Fortran:
 *		INTEGER X, Y
 *		COMMON /CBLOCK/ X, Y
 *		    =>	loadd	_cblock$,f0		-- load X
 *			loadd	_cblock$+8,f1		-- load Y
 *
 *		CALL SUB()
 *		    =>	call	sp,_sub_
 *
 * The Intrnisic_Proc_Format describes a modification to intrinsic
 * procedure names, allowing an easy way of describing intrinsic
 * naming conventions.  Our convention: Intrinsic functions have
 * an underscore, '_', prepended to their names, so this format is
 * "_%s".  Note that the processing by Intrinsic_Proc_Format is done
 * at compiler-build time (by the program "mkintr.x").
 *
 * Note also that the Ftn_Extern_Proc_Format is *not* applied to
 * intrinsic functions, even though they are external procedures.
 *
 * There are some language-specific things here.  For example, the
 * naming convention for Fortran functions is not the same as the
 * naming convention for C functions.  Consequently, there are two
 * formats for external procedure names:
 *	Ftn_Extern_Proc_Format
 *	C_Extern_Proc_Format
 */
#define Intrinsic_Proc_Format	"%s"	   /* eg: "_exp"              */
#define Ftn_Extern_Data_Format	"%s_"	   /* eg: "cblock_"          */
#define C_Extern_Data_Format	"%s"	   /* eg: "extrn"	      */
#define Ftn_Extern_Proc_Format	"%s_"	   /* eg: "sub_"             */
#define C_Extern_Proc_Format	"%s"	   /* eg: "sub"              */
#define C_Global_Static_Format	"GS.%s"	   /* statics in global scope */
#define C_Local_Static_Format	"LS.%1d.%s"/* statics in local scope  */
#define Deferred_Ref_Format	"%s"	   /* eg: "name"              */
#define Deferred_Ref_Ofst_Format "%s%c%d"  /* eg: "name" '-' offset   */
#define Local_Ret_Buf_Format	"%s.RBUF"  /* eg: "func.RBUF"         */

#define DFLT_FTN_MAIN		"MAIN"
#define DFLT_FTN_LOWMAIN	"main"
#define BLANK_COM_NAME		"_BLNK__"
#define RDATA_RAW_NAME		".rdata"
#define SDATA_RAW_NAME		".sdata"
#define DATA_RAW_NAME		".data"
#define GOT_RAW_NAME		".got"
#define BSS_RAW_NAME		".bss"
#define LIT4_RAW_NAME		".lit4"
#define LIT8_RAW_NAME		".lit8"
#define LIT16_RAW_NAME		".lit16"

#define ASM_CMNT_LINE		" #"	/* use for whole line comments */
#define ASM_CMNT		"#"	/* other than whole line comments */

#define AS_STOP_BIT		NULL

/* Defines for assembly directives */
#define AS_ALIGN 	".align"
#define AS_BYTE		".byte"
#define AS_COM		".comm"
#define AS_DATA		".data"
#define AS_DOUBLE 	".double"
#define AS_DWORD	".quad"
#define AS_DWORD_UNALIGNED ".quad"
#define AS_DYNSYM	NULL
#define AS_END		NULL
#define AS_ENT		NULL
#define AS_AENT		"# .aproc"
#define AS_FLOAT 	".float"
#define AS_FILE		".file"
#define AS_FMASK	".fmask"
#define AS_FRAME	"# .frame"
#define AS_GLOBAL 	".globl"
#define AS_GPVALUE	".gpvalue"
#define AS_HALF		".short"
#define AS_HALF_UNALIGNED ".short"
#define AS_BSS		".lcomm"
#define AS_MASK		"//.mask"
#define AS_ORIGIN	".org"
#define AS_RDATA	".rdata"
#define AS_SDATA	".sdata"
#define AS_SECTION	".section"
#define AS_SIZE         ".size"
#if defined(BUILD_OS_DARWIN)
#define AS_SPACE	".space"
#define AS_STRING	".asciz"
#else /* defined(BUILD_OS_DARWIN) */
#define AS_SPACE	".skip"
#define AS_STRING	".string"
#endif /* defined(BUILD_OS_DARWIN) */
#define AS_TEXT 	".text"
#define AS_TYPE         ".type"
#define AS_TYPE_FUNC	"@function"
#define AS_TYPE_OBJECT	"@object"
#define AS_WEAK		".weak"
#if defined(BUILD_OS_DARWIN)
#define AS_WORD		".long"
#define AS_WORD_UNALIGNED ".long" 
#else /* defined(BUILD_OS_DARWIN) */
#define AS_WORD		".4byte"
#define AS_WORD_UNALIGNED ".4byte" 
#endif /* defined(BUILD_OS_DARWIN) */
#define AS_IDENT	"#ident" /* Make this ASM_CMNT_START if no ident */
#define AS_HIDDEN	".hidden"
#define AS_INTERNAL     ".internal"
#define AS_PROTECTED    ".protected"

extern BOOL CG_emit_non_gas_syntax;

/* The directive for emitting an address depends on the target pointer
 * size.  The following is defined and initialized in config_targ.c:
 */
extern const char *AS_ADDRESS;
extern const char *AS_ADDRESS_UNALIGNED;

/* Defines for emission of special relocations */
#define AS_GPREL	NULL
#define AS_LTOFF	NULL
#define AS_FPTR		NULL
#define AS_GP_REL	NULL
#define AS_NEGATE	NULL

/* A printf format for emitting a function of an external name, where
 * the function is typically given by one of the above kind symbols:
 */
#define ASM_NAME_FUNC(kind,name)	"%s(%s)", kind, name
#define ASM_DIR_NOTRANSFORM()           ; /* no equivalent */
#define ASM_DIR_TRANSFORM()             ; /* no equivalent */
#define ASM_DIR_NOREORDER()             ; /* no equivalent */
#define ASM_DIR_NOAT()                  ; /* no equivalent */
#define ASM_DIR_STOINTERNAL(n)          ; /* no equivalent */
#define ASM_DIR_GPVALUE()         	; /* no equivalent */
#define ASM_DIR_FILE(count, file, name) \
  fprintf(Asm_File, "\t%s\t\"%s/%s\"\n",  AS_FILE, incl_table[DST_FILE_NAME_dir(file)], name);
#define ASM_DIR_ALIGN(p, s)    \
  fprintf(Asm_File, "\t%s %lld\n", AS_ALIGN,(INT64)STB_align(s));

/* gas .skip fills with zeroes */
#define ASM_DIR_ZERO(fl, l)	fprintf(fl, "\t%s %lld\n", AS_SPACE, (INT64)l) 
#define ASM_DIR_SKIP(fl, l) 	fprintf(fl, "\t%s %lld\n", AS_SPACE, (INT64)l)
  
#ifdef __cplusplus
}
#endif
#endif /* config_asm_INCLUDED */
