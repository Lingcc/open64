/********************************************************************\
|*                                                                  *|   
|*  Copyright (c) 2006 by SimpLight Nanoelectronics.                *|
|*  All rights reserved                                             *|
|*                                                                  *|
|*  This program is free software; you can redistribute it and/or   *|
|*  modify it under the terms of the GNU General Public License as  *|
|*  published by the Free Software Foundation; either version 2,    *|
|*  or (at your option) any later version.                          *|
|*                                                                  *|
\********************************************************************/ 

/* ====================================================================
 *
 * Module: cgemit_targ.c
 * $Revision: 1.4 $
 * $Date: 2006/04/28 08:13:16 $
 * $Author: weitang $
 * $Source: /depot/CVSROOT/javi/src/sw/cmplr/be/cg/MIPS/cgemit_targ.cxx,v $
 *
 * Description:
 *
 * Target-specific cgemit code.
 *
 * ====================================================================
 * ====================================================================
 */


#include "elf_stuff.h"

#define	USE_STANDARD_TYPES 1
#include "defs.h"
#include "targ_const.h"
#include "targ_const_private.h"
#include "vstring.h"
#include "config_asm.h"
#include "em_elf.h"
#include "symtab.h"
#include "tn.h"
#include "cgemit.h"
#include "cgemit_targ.h"
#include "data_layout.h"
#include "bb.h"
#include "op.h"
#include "iface_scn.h"
#include "cg_flags.h"
#include "glob.h"
#include "sections.h"

static ST *current_pu = NULL;

static BOOL
Non_Default_Text_Section (ST *pu)
{
  if (!pu || !ST_base(pu))
    return FALSE;

  return ((ST_sclass(ST_base(pu)) == SCLASS_TEXT) && 
	  strcmp(ST_name(ST_base(pu)), ".text"));
}


void
CGEMIT_Targ_Initialize (ST *pu)
{
  current_pu = pu;
}


void
CGEMIT_Targ_Text_Initialize (ST *pu)
{
  if (Non_Default_Text_Section(pu))
    fprintf (Asm_File, "\t.begin\tliteral_prefix %s\n", ST_name(ST_base(pu)));
}


void
CGEMIT_Targ_Text_Finalize (ST *pu)
{
  if (Non_Default_Text_Section(pu))
    fprintf (Asm_File, "\t.end\tliteral_prefix\n");
}


BOOL
CGEMIT_Align_Section_Once (const char *scn_name)
{
  return strcmp(scn_name, ".literal") && strcmp(scn_name, ".text");
}

void
CGEMIT_Prn_File_Dir_In_Asm(USRCPOS usrcpos,
                        const char *pathname,
                        const char *filename)
{
  if (CG_emit_non_gas_syntax)
    fprintf (Asm_File, "\t%s\t%d\t\"%s/%s\"\n",
	     AS_FILE, USRCPOS_filenum(usrcpos)-1, pathname, filename);
#ifdef TARG_SL
  else {
    if (pathname == NULL)
	fprintf (Asm_File, "\t%s\t%d\t\"%s\"\n",
		 AS_FILE, USRCPOS_filenum(usrcpos), filename);
    else
	fprintf (Asm_File, "\t%s\t%d\t\"%s/%s\"\n",
		 AS_FILE, USRCPOS_filenum(usrcpos), pathname, filename);
  }
#else
  else fprintf (Asm_File, "\t%s\t%d\t\"%s/%s\"\n",
	   AS_FILE, USRCPOS_filenum(usrcpos), pathname, filename);
#endif
}

extern void
CGEMIT_Prn_Line_Dir_In_Asm (USRCPOS usrcpos)
{
  if(!CG_emit_asm_dwarf) { 
    fprintf (Asm_File, " # "); //turn the rest into comment
  }
  if (CG_emit_non_gas_syntax)
    fprintf (Asm_File, "\t.loc\t%d\t%d\t%d\n", 
	     USRCPOS_filenum(usrcpos)-1,
	     USRCPOS_linenum(usrcpos),
	     USRCPOS_column(usrcpos));
  else
    fprintf (Asm_File, "\t.loc\t%d\t%d\t%d\n", 
	     USRCPOS_filenum(usrcpos),
	     USRCPOS_linenum(usrcpos),
	     USRCPOS_column(usrcpos));    
  }


void
CGEMIT_Prn_Scn_In_Asm (ST *st, ST *cur_section)
{
  UINT32 tmp, power;
  power = 0;
  for (tmp = STB_align(st); tmp > 1; tmp >>= 1) power++;
  CGEMIT_Prn_Scn_In_Asm(Asm_File,
			ST_name(st),
			Get_Section_Elf_Type(STB_section_idx(st)),
			Get_Section_Elf_Flags(STB_section_idx(st)),
			Get_Section_Elf_Entsize(STB_section_idx(st)),
			power,
			(cur_section != NULL) ? ST_name(cur_section) : NULL);
}

void
CGEMIT_Prn_Scn_In_Asm (FILE       *asm_file,
		       const char *scn_name,
		       Elf64_Word  scn_type,
		       Elf64_Word  scn_flags,
		       Elf64_Xword scn_entsize,
		       Elf64_Word  scn_align,
		       const char *cur_scn_name)
{
  if ((cur_scn_name != NULL) && !strcmp(cur_scn_name, ".literal"))
  {

    /* If we added a prefix to the literal section, then end the
       prefix region */
    if (Non_Default_Text_Section(current_pu))
      fprintf (asm_file, "\t.end\tliteral_prefix\n");
  }
  
  /* Handle .text, .data, and .literal specially. */

  if (!strcmp(scn_name, ".data") || !strcmp(scn_name, ".text"))
  {
    fprintf (asm_file, "\n\t%s", scn_name);
  }
  else if (!strcmp(scn_name, ".literal"))
  {
    /* If we need to add a prefix to the literal section, then emit
       the correct cabbage for that to happen. */
    if (Non_Default_Text_Section(current_pu))
    {
      CGEMIT_Prn_Scn_In_Asm(ST_base(current_pu), NULL);
      fprintf (asm_file, "\t.begin\tliteral_prefix %s\n",
	       ST_name(ST_base(current_pu)));
    }
    else
    {
      fprintf (asm_file, "\n\t.text\n");
    }
    fprintf (asm_file, "\t.literal_position\n");
  }
  else
  {
    char scn_flags_string[5];
    char *p = &scn_flags_string[0];
    
    fprintf (asm_file, "\n\t%s %s", AS_SECTION, scn_name);
    if (CG_emit_non_gas_syntax && strcmp(scn_name, ".srdata") == 0) {
      static BOOL printed = FALSE;
      if (!printed) {
	fprintf(asm_file, ", %d, %#x, %lld, ", 
		scn_type, scn_flags, scn_entsize);
	int tmp1 = 1, tmp2 = scn_align;
	for (; tmp2 >= 1; tmp1 *= 2, tmp2 --);
	fprintf(asm_file, "%d", tmp1);
	printed = TRUE;
      }
    }
    if (! CG_emit_non_gas_syntax) {
      if (scn_flags & SHF_WRITE) *p++ = 'w';
      if (scn_flags & SHF_ALLOC) *p++ = 'a';
      if (scn_flags & SHF_EXECINSTR) *p++ = 'x';
      *p = '\0'; // null terminate the string.
      fprintf (asm_file, ", \"%s\"", scn_flags_string);
    }
  }

  fprintf (asm_file, "\n");

  /* For most sections, we only emit the alignment the first time we
     see it (in cgemit.cxx:Init_Section), because .org is used to
     place/align all data items relative to the start of the
     section. But some we always align. */

  if (!CGEMIT_Align_Section_Once(scn_name))
    fprintf (asm_file, "\t%s\t%d\n", AS_ALIGN, scn_align);
}

void
CGEMIT_Change_Origin_In_Asm (ST *st, INT64 offset)
{
  /* Make sure these match what is used in eh_region.cxx (with "t"
     changed to "e" or "h"). */
#define EH_REGION_LINKONCE_PREFIX ".gnu.linkonce.e."
#define EH_DESC_LINKONCE_PREFIX ".gnu.linkonce.h."
    
  /* We don't want to emit .org for literal sections, since the .org
     for these gets reset for every pu; and because we don't need them
     here.

     We don't want to emit .org for exception region or descriptors
     since the section contains both .xt_except_table/.xt_except_desc
     and .gnu.linkonce.e.* / .gnu.linkonce.h.* sections. We don't need
     the .org for these because there are no alignment issues since
     all INITVs in the section are 4 bytes, and the section start is 4
     byte aligned. */

  if (strcmp(ST_name(st), ".literal") &&
      strcmp(ST_name(st), ".xt_except_table") &&
      strcmp(ST_name(st), ".xt_desc_table") &&
      strncmp(ST_name(st), EH_REGION_LINKONCE_PREFIX,
	      strlen(EH_REGION_LINKONCE_PREFIX)) &&
      strncmp(ST_name(st), EH_DESC_LINKONCE_PREFIX,
	      strlen(EH_DESC_LINKONCE_PREFIX)))
  {
    if (CG_emit_non_gas_syntax)
      fprintf (Asm_File, "\t%s 0x%llx\n", ".origin", offset);
    else fprintf (Asm_File, "\t%s 0x%llx\n", AS_ORIGIN, offset);
    fprintf ( Asm_File, "\t%s\t0\n", AS_ALIGN );
  }
}


// whether to use the base st for the reloc
extern BOOL
CGEMIT_Use_Base_ST_For_Reloc (INT reloc, ST *st)
{
	if (reloc == TN_RELOC_IA_LTOFF_FPTR) 
		// gas doesn't like addends
		return FALSE;
	// to handle function pointers.
	// example: see gcc.c-torture/execute/func-ptr-1.c
	else if (ST_sclass(st) == SCLASS_TEXT)
	        return FALSE;
	else 
		return ST_is_export_local(st);
}

	  
extern INT
CGEMIT_Relocs_In_Asm (TN *t, ST *st, vstring *buf, INT64 *val)
{
	INT paren = 1;	// num parens
	// only add in GP_DISP if based on gprel section
	// not if based on ipa-generated extern.
	if (ST_class(st) == CLASS_BLOCK && STB_section(st)) {
		*val -= GP_DISP;
	}
	switch (TN_relocs(t)) {
	case TN_RELOC_GOT_DISP:
        	*buf = vstr_concat (*buf, "%got_disp");
		break;
	case TN_RELOC_GOT_PAGE:
        	*buf = vstr_concat (*buf, "%got_page");
		break;
	case TN_RELOC_GOT_OFST:
        	*buf = vstr_concat (*buf, "%got_ofst");
		break;
	case TN_RELOC_HI_GPSUB:
        	*buf = vstr_concat (*buf, "%hi(%neg(%gp_rel");
		paren += 2;
		break;
	case TN_RELOC_LO_GPSUB:
        	*buf = vstr_concat (*buf, "%lo(%neg(%gp_rel");
		paren += 2;
		break;
	case TN_RELOC_GPREL16:
        	*buf = vstr_concat (*buf, "%gp_rel");
		break;
	case TN_RELOC_HIGH16:
        	*buf = vstr_concat (*buf, "%hi");
		break;
	case TN_RELOC_LOW16:
        	*buf = vstr_concat (*buf, "%lo");
		break;
#ifdef TARG_SL
   case TN_RELOC_GPREL_V1:
        *buf = vstr_concat(*buf, "%secrel_v1");
        break;
   case TN_RELOC_GPREL_V2:
        *buf = vstr_concat(*buf, "%secrel_v2");
        break;
   case TN_RELOC_GPREL_V4:
        *buf = vstr_concat(*buf, "%secrel_v4");
        break;
   case TN_RELOC_GPREL_S:
        *buf = vstr_concat(*buf, "%secrel_s");
        break;
   case TN_RELOC_GPREL_V1_15:
        *buf = vstr_concat(*buf, "%secrel_v1_15");
        break;
   case TN_RELOC_GPREL_V2_15:
        *buf = vstr_concat(*buf, "%secrel_v2_15");
        break;
   case TN_RELOC_GPREL_V4_15:
        *buf = vstr_concat(*buf, "%secrel_v4_15");
        break;
#endif
#ifdef TARG_SL2
    case TN_RELOC_GPREL_SL2_V11:
        *buf = vstr_concat(*buf, "%secrel_sl2_v11");
	  break;
    case TN_RELOC_GPREL_SL2_V15:
        *buf = vstr_concat(*buf, "%secrel_sl2_v15");
	  break;
    case TN_RELOC_GPREL_SL2_S:
        *buf = vstr_concat(*buf, "%secrel_sl2_s");
	  break;
#endif
    	default:
		#pragma mips_frequency_hint NEVER
    		FmtAssert (FALSE, ("relocs_asm: illegal reloc TN"));
		/*NOTREACHED*/
	}
	*buf = vstr_concat (*buf, "(" );
	*buf = vstr_concat (*buf, ST_name(st));
	*buf = vstr_concat (*buf, Symbol_Name_Suffix);
	return paren;
}


extern void
CGEMIT_Relocs_In_Object (TN *t, ST *st, INT32 PC, pSCNINFO PU_section, INT64 *val)
{
  FmtAssert(FALSE, ("NYI"));
} 

// add events and relocs as needed for call
extern void 
CGEMIT_Add_Call_Information (OP *op, BB *bb, INT32 PC, pSCNINFO PU_section)
{
	ANNOTATION *ant = ANNOT_Get (BB_annotations(bb), ANNOT_CALLINFO);
	ST *call_sym = CALLINFO_call_st(ANNOT_callinfo(ant));
    	Elf_Event_Kind event_type;

	if (call_sym == NULL) return;
	if (ST_is_export_local(call_sym)) {
		event_type = EK_FCALL_LOCAL;
	}
	else {
		event_type = EK_FCALL_EXTERN;
      	}
	Em_Add_New_Event (event_type, PC, EMT_Put_Elf_Symbol(call_sym),
			0, 0, PU_section);
      
	// TODO: if indirect call add plt reloc

	// do pcrel relocation for all calls,
	// as even statics may be forward refs so don't know pc.
	// Ld will generate a stub if needed.
	Em_Add_New_Rela (EMT_Put_Elf_Symbol(call_sym), 
		R_IA_64_PCREL21B, PC, 0, PU_section);

      	if (EMIT_interface_section) {
		Interface_Scn_Add_Call( call_sym, 
			CALLINFO_call_wn(ANNOT_callinfo(ant)));
      	}
}


/* Generate the .frame, .mask and the .fmask directives for the assembler. */
void
CGEMIT_Gen_Asm_Frame (INT64 frame_len)
{
  if (CG_inhibit_size_directive)
    return;
  TN *tn = ((Current_PU_Stack_Model == SMODEL_SMALL) ? SP_TN : FP_TN);
  ISA_REGISTER_CLASS rc = TN_register_class(tn);
  REGISTER reg = TN_register(tn);
  fprintf ( Asm_File, "\t%s\t%s, %lld, %s\n",
	    AS_FRAME,
	    ABI_PROPERTY_Reg_Name(rc, REGISTER_machine_id(rc, reg)),
	    frame_len,
	    ABI_PROPERTY_Reg_Name(rc, REGISTER_machine_id(rc, TN_register(RA_TN))));
}


// Generate the entry (.proc) directive.
void 
CGEMIT_Prn_Ent_In_Asm (ST *pu)
{
  BB_LIST *ent_list;

  fprintf ( Asm_File, "\t%s\t", AS_ENT);
  EMT_Write_Qualified_Name(Asm_File, pu);

  if (CG_emit_non_gas_syntax)
  for (ent_list = Entry_BB_Head; ent_list; ent_list = BB_LIST_rest(ent_list)) {
    BB *bb = BB_LIST_first(ent_list);
    ANNOTATION *ant = ANNOT_Get (BB_annotations(bb), ANNOT_ENTRYINFO);
    ENTRYINFO *ent = ANNOT_entryinfo(ant);
    ST *entry_sym = ENTRYINFO_name(ent);

    if ( !ST_is_not_used(entry_sym)) {
      const char *entry_name = ST_name(entry_sym);
      if (strcmp( Cur_PU_Name, entry_name ) != 0) {
	fprintf (Asm_File, ", %s", entry_name);
      }
    }
  }

  fprintf ( Asm_File, "\n");
}
#ifdef TARG_SL
static void Gen_Register_Mask(REGISTER_SET *interrupt_saved, REGISTER_SET *ctrl_saved, 
                              REGISTER_SET *spe_saved) {
  BB *bb;
  OP *op;

  REGISTER_SET caller_saved = REGISTER_CLASS_caller_saves(ISA_REGISTER_CLASS_integer);
  REGISTER_SET used_gpr = REGISTER_SET_EMPTY_SET;
  REGISTER_SET used_spe_reg = REGISTER_SET_EMPTY_SET; // special register
  REGISTER_SET used_ctr_reg = REGISTER_SET_EMPTY_SET; // control register

  for(bb = REGION_First_BB; bb; bb = BB_next(bb))
  {
    FOR_ALL_BB_OPs(bb, op)
    {
      for(INT i = 0; i < OP_results(op); i++) {
        TN* tn = OP_result(op, i);
        if (TN_is_register(tn) && (TN_register_class(tn) == ISA_REGISTER_CLASS_integer)) {
           used_gpr =  REGISTER_SET_Union(used_gpr, (1 << (TN_register(tn)-1)));
        } else if (tn == JA_TN) {
           used_ctr_reg = REGISTER_SET_Union (used_ctr_reg, 1);
        } else if (tn == RA_TN) {
           used_ctr_reg = REGISTER_SET_Union (used_ctr_reg, 2);
        } else if (TN_is_LoopRegister(tn)) {
          // loop register
           used_ctr_reg = REGISTER_SET_Union(used_ctr_reg, (1 << (TN_number(tn)-TN_number(LC0_TN)+2))); 
        } else if (tn == HI_TN) {
          // HI register
           used_spe_reg = REGISTER_SET_Union(used_spe_reg, 21);
        } else if (TN_is_AddrRegister(tn)) {
           used_spe_reg = REGISTER_SET_Union(used_spe_reg, (1 << (TN_number(tn)-TN_number(Addr0_TN))));
        } else if (TN_is_AccRegister(tn)) {
           used_spe_reg = REGISTER_SET_Union(used_spe_reg, (1 << (TN_number(tn)-TN_number(Acc0_TN)+16)));
        } else if (TN_is_AddrSizeRegister(tn)) {
           used_spe_reg = REGISTER_SET_Union(used_spe_reg, (1 << (TN_number(tn)-TN_number(Addrsize0_TN)+8)));
        }
      }
      if (CG_ISR == 2) {
        for(INT i = 0; i < OP_opnds(op); i++) {
          TN* tn = OP_opnd(op, i);
          if (TN_is_register(tn) && (TN_register_class(tn) == ISA_REGISTER_CLASS_integer)) {
            used_gpr =  REGISTER_SET_Union(used_gpr, (1 << (TN_register(tn)-1)));
          } else if (tn == JA_TN) {
            used_ctr_reg = REGISTER_SET_Union (used_ctr_reg, 1);
          } else if (tn == RA_TN) {
            used_ctr_reg = REGISTER_SET_Union (used_ctr_reg, 2);
          } else if (TN_is_LoopRegister(tn)) {
            // loop register
            used_ctr_reg = REGISTER_SET_Union(used_ctr_reg, (1 << (TN_number(tn)-TN_number(LC0_TN)+2)));
          } else if (tn == HI_TN) {
            // HI register
            used_spe_reg = REGISTER_SET_Union(used_spe_reg, 21);
          } else if (TN_is_AddrRegister(tn)) {
            used_spe_reg = REGISTER_SET_Union(used_spe_reg, (1 << (TN_number(tn)-TN_number(Addr0_TN))));
          } else if (TN_is_AccRegister(tn)) {
            used_spe_reg = REGISTER_SET_Union(used_spe_reg, (1 << (TN_number(tn)-TN_number(Acc0_TN)+16)));
          } else if (TN_is_AddrSizeRegister(tn)) {
           used_spe_reg = REGISTER_SET_Union(used_spe_reg, (1 << (TN_number(tn)-TN_number(Addrsize0_TN)+8)));
          }
        }
      } // CG_ISR == 2
    }
  }
  *interrupt_saved = REGISTER_SET_Intersection(caller_saved, used_gpr);
  *ctrl_saved = used_ctr_reg;
  *spe_saved = used_spe_reg;

  if (0) {
    REGISTER_SET_Print(caller_saved, stdout);
    printf("caller_saved  = %x\n", caller_saved);
    REGISTER_SET_Print(used_gpr, stdout);
    REGISTER_SET_Print(*interrupt_saved, stdout);
    REGISTER_SET_Print(used_ctr_reg, stdout);
    REGISTER_SET_Print(used_spe_reg, stdout);
  }
}


// Generate used caller saved-register as # *****
void CGEMIT_Prn_Used_Callersaved_In_Asm (void)
{
  REGISTER_SET gpr_saved = REGISTER_SET_EMPTY_SET;
  REGISTER_SET ctrl_saved = REGISTER_SET_EMPTY_SET;
  REGISTER_SET spe_saved = REGISTER_SET_EMPTY_SET;
  Gen_Register_Mask(&gpr_saved, &ctrl_saved, &spe_saved);
  if (CG_ISR == 1) {
    // show defined caller-saved register
    fprintf (Asm_File, "\t# defined caller-saved GPR:  0x%x\n", gpr_saved);
    fprintf (Asm_File, "\t# defined ctrl-register:  0x%x\n", ctrl_saved);
    fprintf (Asm_File, "\t# defined special-register:  0x%x\n", spe_saved);
  } else if (CG_ISR == 2) {
    // show used caller-saved register
    fprintf (Asm_File, "\t# used caller-saved GPR:  0x%x\n", gpr_saved);
    fprintf (Asm_File, "\t# used ctrl-register:  0x%x\n", ctrl_saved);
    fprintf (Asm_File, "\t# used special-register:  0x%x\n", spe_saved);
  } 
  
}
#endif

// Preprocess FP registers before emit.  Needed only for IA-32.
void
STACK_FP_Fixup_PU()
{}

void
CGEMIT_Weak_Alias (ST *sym, ST *strongsym) 
{
        fprintf ( Asm_File, "\t%s\t%s\n", AS_WEAK, ST_name(sym));
        fprintf ( Asm_File, "\t%s = %s\n", ST_name(sym), ST_name(strongsym));
}

void CGEMIT_Write_Literal_TCON(ST *lit_st, TCON tcon)
{
  INT64 val;
  if (TCON_ty(tcon) == MTYPE_F4)
    val = TCON_word0(tcon);
  else if ((TCON_ty(tcon) == MTYPE_I4) || (TCON_ty(tcon) == MTYPE_U4))
    val = TCON_v0(tcon);
  else
    FmtAssert(FALSE, ("Invalid literal value"));
  fprintf ( Asm_File, "\t%s\t", ".literal");
  EMT_Write_Qualified_Name(Asm_File, lit_st);
  if ((val >= INT32_MIN) && (val <= INT32_MAX)) 
    fprintf(Asm_File, ", %lld\n", val);
  else
    fprintf(Asm_File, ", %#llx\n", val);
  
}

void CGEMIT_Write_Literal_Label (ST *lit_st, LABEL_IDX lab)
{
  fprintf ( Asm_File, "\t%s\t", ".literal");
  EMT_Write_Qualified_Name(Asm_File, lit_st);
  union {
    UINT64 u;
    void *p;
  } u;
  u.u = 0;
  u.p = LABEL_name(lab);
  fprintf(Asm_File, ", %lld\n", u.u);
}

void CGEMIT_Write_Literal_Symbol (ST *lit_st, ST *sym, 
				  Elf64_Sxword sym_ofst)
{
  ST *basesym;
  basesym = sym;
  INT64 base_ofst = 0;

  if (Has_Base_Block(sym) && ST_is_export_local(sym) && ST_class(sym) != CLASS_FUNC) {
    Base_Symbol_And_Offset (sym, &basesym, &base_ofst);
  }
  base_ofst += sym_ofst;

  fprintf ( Asm_File, "\t%s\t", ".literal");
  EMT_Write_Qualified_Name(Asm_File, lit_st);
  fprintf ( Asm_File, ", ");
  if (ST_class(sym) == CLASS_CONST) {
    EMT_Write_Qualified_Name (Asm_File, basesym);
    if (base_ofst == 0)
      fprintf (Asm_File, "\n");
    else
      fprintf (Asm_File, " %+lld\n", base_ofst);
  }
  else {
    EMT_Write_Qualified_Name (Asm_File, sym);
    if (sym_ofst == 0)
      fprintf (Asm_File, "\n");
    else
      fprintf (Asm_File, " %+lld\n", sym_ofst);
  }
}

void
CGEMIT_Alias (ST *sym, ST *strongsym) 
{
        fprintf ( Asm_File, "\t%s = %s\n", ST_name(sym), ST_name(strongsym));
}

