/*
 * Copyright 2005-2008 NVIDIA Corporation.  All rights reserved.
 */

/*

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

*/

//
// Generate an ISA containing the instructions specified.
/////////////////////////////////////////////////////////
// The instructions are listed by category. The different categories of
// instructions are:
//
//   1. Integer instructions
//   2. FP instructions
//   3. Simulated instructions
//   4. Dummy instructions
//
// Within each category, the instructions are in alphabetical order.
// This arrangement of instructions matches the order in the ISA manual.
/////////////////////////////////////
//
//  $Revision: 1.25 $
//  $Date: 2001/03/10 01:16:13 $
//  $Author: mtibuild $
//  $Source: /osprey.src/osprey1.0/common/targ_info/isa/ia64/RCS/isa.cxx,v $

#include <stddef.h>
#include "isa_gen.h"

main ()
{
  // Normally would put type info in an enum on the base instruction,
  // but for nvisa the type info affects the operand sizes (cause multiple
  // register sizes), so need it in base instruction.
  // 
  // Will only define simple variants of instructions that we will use;
  // e.g. ignore predication except for branches.
  //
  // Note that some of the expansion routines rely on the order of the types 
  // within an opcode, so be careful to keep them grouped together.
  ISA_Create ("nvisa", 
	"add.s8",
	"add.s16",
	"add.s32",
	"add.s64",
	"add.u8",
	"add.u16",
	"add.u32",
	"add.u64",
	"add.f32",
	"add.f64",
	"add.s8_lit",
	"add.s16_lit",
	"add.s32_lit",
	"add.s64_lit",
	"add.u8_lit",
	"add.u16_lit",
	"add.u32_lit",
	"add.u64_lit",
	"add.rn.f32",
	"add.rz.f32",
	"add.rn.f64",
	"add.rz.f64",
	"add.rm.f64",
	"add.rp.f64",
	"sub.s8",
	"sub.s16",
	"sub.s32",
	"sub.s64",
	"sub.u8",
	"sub.u16",
	"sub.u32",
	"sub.u64",
	"sub.f32",
	"sub.f64",
	"sub.s8_lit",
	"sub.s16_lit",
	"sub.s32_lit",
	"sub.s64_lit",
	"sub.u8_lit",
	"sub.u16_lit",
	"sub.u32_lit",
	"sub.u64_lit",
    "sub.s32_p",      
    "sub.s64_p",
    "sub.s32_np",
    "sub.s64_np",
    "mul.lo.s8",
	"mul.lo.s16",
	"mul.lo.s32",
	"mul.lo.s64",
	"mul.lo.u8",
	"mul.lo.u16",
	"mul.lo.u32",
	"mul.lo.u64",
	"mul.hi.s8",
	"mul.hi.s16",
	"mul.hi.s32",
	"mul.hi.s64",
	"mul.hi.u8",
	"mul.hi.u16",
	"mul.hi.u32",
	"mul.hi.u64",
	"mul.lo.s8_lit",
	"mul.lo.s16_lit",
	"mul.lo.s32_lit",
	"mul.lo.s64_lit",
	"mul.lo.u8_lit",
	"mul.lo.u16_lit",
	"mul.lo.u32_lit",
	"mul.lo.u64_lit",
	"mul.wide.s16",
	"mul.wide.s32",
	"mul.wide.u16",
	"mul.wide.u32",
	"mul.wide.s16_lit",
	"mul.wide.s32_lit",
	"mul.wide.u16_lit",
	"mul.wide.u32_lit",
	"mul24.lo.s32",
	"mul24.lo.u32",
	"mul24.lo.s32_lit",
	"mul24.lo.u32_lit",
	"mul.f32",
	"mul.f64",
	"mul.rn.f32",
	"mul.rz.f32",
	"mul.rn.f64",
	"mul.rz.f64",
	"mul.rm.f64",
	"mul.rp.f64",
	"mad.lo.s8",
	"mad.lo.s16",
	"mad.lo.s32",
	"mad.lo.s64",
	"mad.lo.u8",
	"mad.lo.u16",
	"mad.lo.u32",
	"mad.lo.u64",
	"mad.hi.s8",
	"mad.hi.s16",
	"mad.hi.s32",
	"mad.hi.s64",
	"mad.hi.u8",
	"mad.hi.u16",
	"mad.hi.u32",
	"mad.hi.u64",
	"mad.wide.s16",
	"mad.wide.u16",
	"mad.wide.s32",
	"mad.wide.u32",
	"mad24.lo.s32",
	"mad24.lo.u32",
	"mad.f32",
	"mad.f64",
	"mad.rn.f64",
	"mad.rz.f64",
	"mad.rm.f64",
	"mad.rp.f64",
	"div.s8",
	"div.s16",
	"div.s32",
	"div.s64",
	"div.u8",
	"div.u16",
	"div.u32",
	"div.u64",
	"div.f32",
	"div.f64",
	"div.s8_lit",
	"div.s16_lit",
	"div.s32_lit",
	"div.s64_lit",
	"div.u8_lit",
	"div.u16_lit",
	"div.u32_lit",
	"div.u64_lit",
	"rem.s8",
	"rem.s16",
	"rem.s32",
	"rem.s64",
	"rem.u8",
	"rem.u16",
	"rem.u32",
	"rem.u64",
	"rem.s8_lit",
	"rem.s16_lit",
	"rem.s32_lit",
	"rem.s64_lit",
	"rem.u8_lit",
	"rem.u16_lit",
	"rem.u32_lit",
	"rem.u64_lit",
	"abs.s8",
	"abs.s16",
	"abs.s32",
	"abs.s64",
	"abs.u8",
	"abs.u16",
	"abs.u32",
	"abs.u64",
	"abs.f32",
	"abs.f64",
	"min.s8",
	"min.s16",
	"min.s32",
	"min.s64",
	"min.u8",
	"min.u16",
	"min.u32",
	"min.u64",
	"min.f32",
	"min.f64",
	"max.s8",
	"max.s16",
	"max.s32",
	"max.s64",
	"max.u8",
	"max.u16",
	"max.u32",
	"max.u64",
	"max.f32",
	"max.f64",
	"set.eq.u32.s8",
	"set.eq.u32.s16",
	"set.eq.u32.s32",
	"set.eq.u32.s64",
	"set.eq.u32.u8",
	"set.eq.u32.u16",
	"set.eq.u32.u32",
	"set.eq.u32.u64",
	"set.eq.u32.f32",
	"set.eq.u32.f64",
	"set.ne.u32.s8",
	"set.ne.u32.s16",
	"set.ne.u32.s32",
	"set.ne.u32.s64",
	"set.ne.u32.u8",
	"set.ne.u32.u16",
	"set.ne.u32.u32",
	"set.ne.u32.u64",
	"set.ne.u32.f32",
	"set.ne.u32.f64",
	"set.lt.u32.s8",
	"set.lt.u32.s16",
	"set.lt.u32.s32",
	"set.lt.u32.s64",
	"set.lt.u32.u8",
	"set.lt.u32.u16",
	"set.lt.u32.u32",
	"set.lt.u32.u64",
	"set.lt.u32.f32",
	"set.lt.u32.f64",
	"set.le.u32.s8",
	"set.le.u32.s16",
	"set.le.u32.s32",
	"set.le.u32.s64",
	"set.le.u32.u8",
	"set.le.u32.u16",
	"set.le.u32.u32",
	"set.le.u32.u64",
	"set.le.u32.f32",
	"set.le.u32.f64",
	"set.gt.u32.s8",
	"set.gt.u32.s16",
	"set.gt.u32.s32",
	"set.gt.u32.s64",
	"set.gt.u32.u8",
	"set.gt.u32.u16",
	"set.gt.u32.u32",
	"set.gt.u32.u64",
	"set.gt.u32.f32",
	"set.gt.u32.f64",
	"set.ge.u32.s8",
	"set.ge.u32.s16",
	"set.ge.u32.s32",
	"set.ge.u32.s64",
	"set.ge.u32.u8",
	"set.ge.u32.u16",
	"set.ge.u32.u32",
	"set.ge.u32.u64",
	"set.ge.u32.f32",
	"set.ge.u32.f64",
	"set.equ.u32.f32",
	"set.equ.u32.f64",
	"set.neu.u32.f32",
	"set.neu.u32.f64",
	"set.ltu.u32.f32",
	"set.ltu.u32.f64",
	"set.leu.u32.f32",
	"set.leu.u32.f64",
	"set.gtu.u32.f32",
	"set.gtu.u32.f64",
	"set.geu.u32.f32",
	"set.geu.u32.f64",
	"set.u.u32.f32",
	"set.u.u32.f64",
	"set.leg.u32.f32",
	"set.leg.u32.f64",
	"set.eq.u16.s8",
	"set.eq.u16.s16",
	"set.eq.u16.s32",
	"set.eq.u16.s64",
	"set.eq.u16.u8",
	"set.eq.u16.u16",
	"set.eq.u16.u32",
	"set.eq.u16.u64",
	"set.eq.u16.f32",
	"set.eq.u16.f64",
	"set.ne.u16.s8",
	"set.ne.u16.s16",
	"set.ne.u16.s32",
	"set.ne.u16.s64",
	"set.ne.u16.u8",
	"set.ne.u16.u16",
	"set.ne.u16.u32",
	"set.ne.u16.u64",
	"set.ne.u16.f32",
	"set.ne.u16.f64",
	"set.lt.u16.s8",
	"set.lt.u16.s16",
	"set.lt.u16.s32",
	"set.lt.u16.s64",
	"set.lt.u16.u8",
	"set.lt.u16.u16",
	"set.lt.u16.u32",
	"set.lt.u16.u64",
	"set.lt.u16.f32",
	"set.lt.u16.f64",
	"set.le.u16.s8",
	"set.le.u16.s16",
	"set.le.u16.s32",
	"set.le.u16.s64",
	"set.le.u16.u8",
	"set.le.u16.u16",
	"set.le.u16.u32",
	"set.le.u16.u64",
	"set.le.u16.f32",
	"set.le.u16.f64",
	"set.gt.u16.s8",
	"set.gt.u16.s16",
	"set.gt.u16.s32",
	"set.gt.u16.s64",
	"set.gt.u16.u8",
	"set.gt.u16.u16",
	"set.gt.u16.u32",
	"set.gt.u16.u64",
	"set.gt.u16.f32",
	"set.gt.u16.f64",
	"set.ge.u16.s8",
	"set.ge.u16.s16",
	"set.ge.u16.s32",
	"set.ge.u16.s64",
	"set.ge.u16.u8",
	"set.ge.u16.u16",
	"set.ge.u16.u32",
	"set.ge.u16.u64",
	"set.ge.u16.f32",
	"set.ge.u16.f64",
	"set.equ.u16.f32",
	"set.equ.u16.f64",
	"set.neu.u16.f32",
	"set.neu.u16.f64",
	"set.ltu.u16.f32",
	"set.ltu.u16.f64",
	"set.leu.u16.f32",
	"set.leu.u16.f64",
	"set.gtu.u16.f32",
	"set.gtu.u16.f64",
	"set.geu.u16.f32",
	"set.geu.u16.f64",
	"set.u.u16.f32",
	"set.u.u16.f64",
	"set.leg.u16.f32",
	"set.leg.u16.f64",
	// there are 18*3*11*11 possible combinations for set;
	// rather than list them all individually, 
	// use enums for cmp and bool operands.
	"set<cmpb>u16.s16_lit",
	"set<cmpb>u16.s32_lit",
	"set<cmpb>u16.u16_lit",
	"set<cmpb>u16.u32_lit",
	"set<cmpb>u32.s16_lit",
	"set<cmpb>u32.s32_lit",
	"set<cmpb>u32.u16_lit",
	"set<cmpb>u32.u32_lit",
	"setp.eq.s8",
	"setp.eq.s16",
	"setp.eq.s32",
	"setp.eq.s64",
	"setp.eq.u8",
	"setp.eq.u16",
	"setp.eq.u32",
	"setp.eq.u64",
	"setp.eq.f32",
	"setp.eq.f64",
	"setp.ne.s8",
	"setp.ne.s16",
	"setp.ne.s32",
	"setp.ne.s64",
	"setp.ne.u8",
	"setp.ne.u16",
	"setp.ne.u32",
	"setp.ne.u64",
	"setp.ne.f32",
	"setp.ne.f64",
	"setp.lt.s8",
	"setp.lt.s16",
	"setp.lt.s32",
	"setp.lt.s64",
	"setp.lt.u8",
	"setp.lt.u16",
	"setp.lt.u32",
	"setp.lt.u64",
	"setp.lt.f32",
	"setp.lt.f64",
	"setp.le.s8",
	"setp.le.s16",
	"setp.le.s32",
	"setp.le.s64",
	"setp.le.u8",
	"setp.le.u16",
	"setp.le.u32",
	"setp.le.u64",
	"setp.le.f32",
	"setp.le.f64",
	"setp.gt.s8",
	"setp.gt.s16",
	"setp.gt.s32",
	"setp.gt.s64",
	"setp.gt.u8",
	"setp.gt.u16",
	"setp.gt.u32",
	"setp.gt.u64",
	"setp.gt.f32",
	"setp.gt.f64",
	"setp.ge.s8",
	"setp.ge.s16",
	"setp.ge.s32",
	"setp.ge.s64",
	"setp.ge.u8",
	"setp.ge.u16",
	"setp.ge.u32",
	"setp.ge.u64",
	"setp.ge.f32",
	"setp.ge.f64",
	"setp.equ.f32",
	"setp.equ.f64",
	"setp.neu.f32",
	"setp.neu.f64",
	"setp.ltu.f32",
	"setp.ltu.f64",
	"setp.leu.f32",
	"setp.leu.f64",
	"setp.gtu.f32",
	"setp.gtu.f64",
	"setp.geu.f32",
	"setp.geu.f64",
	"setp.u.f32",
	"setp.u.f64",
	"setp.leg.f32",
	"setp.leg.f64",
	"setp.eq.u32_p",
	"setp.ne.u32_p",
	"setp<cmpb>u32_lit",
	"slct.s8.s32",
	"slct.s16.s32",
	"slct.s32.s32",
	"slct.s64.s32",
	"slct.u8.s32",
	"slct.u16.s32",
	"slct.u32.s32",
	"slct.u64.s32",
	"slct.f32.s32",
	"slct.f64.s32",
	"slct.s8.f32",
	"slct.s16.f32",
	"slct.s32.f32",
	"slct.s64.f32",
	"slct.u8.f32",
	"slct.u16.f32",
	"slct.u32.f32",
	"slct.u64.f32",
	"slct.f32.f32",
	"slct.f64.f32",
	"selp.s8",
	"selp.s16",
	"selp.s32",
	"selp.s64",
	"selp.u8",
	"selp.u16",
	"selp.u32",
	"selp.u64",
	"selp.f32",
	"selp.f64",
	"selp.s8_lit",
	"selp.s16_lit",
	"selp.s32_lit",
	"selp.s64_lit",
	"selp.u8_lit",
	"selp.u16_lit",
	"selp.u32_lit",
	"selp.u64_lit",
	"selp.f32_lit",
	"selp.f64_lit",
	"sin.f32",
	"sin.f64",
	"cos.f32",
	"cos.f64",
	"lg2.f32",
	"lg2.f64",
	"ex2.f32",
	"ex2.f64",
	"rcp.f32",
	"rcp.f64",
	"sqrt.f32",
	"sqrt.f64",
	"rsqrt.f32",
	"rsqrt.f64",
	"and.pred",
	"and.b8",
	"and.b16",
	"and.b32",
	"and.b64",
	"and.b8_lit",
	"and.b16_lit",
	"and.b32_lit",
	"and.b64_lit",
	"or.pred",
	"or.b8",
	"or.b16",
	"or.b32",
	"or.b64",
	"or.b8_lit",
	"or.b16_lit",
	"or.b32_lit",
	"or.b64_lit",
	"not.pred",
	"not.b8",
	"not.b16",
	"not.b32",
	"not.b64",
	"cnot.b8",
	"cnot.b16",
	"cnot.b32",
	"cnot.b64",
	"xor.pred",
	"xor.b8",
	"xor.b16",
	"xor.b32",
	"xor.b64",
	"xor.b8_lit",
	"xor.b16_lit",
	"xor.b32_lit",
	"xor.b64_lit",
	"neg.s8",
	"neg.s16",
	"neg.s32",
	"neg.s64",
	"neg.u8",
	"neg.u16",
	"neg.u32",
	"neg.u64",
	"neg.f32",
	"neg.f64",
	"shl.b8",
	"shl.b16",
	"shl.b32",
	"shl.b64",
	"shr.s8",
	"shr.s16",
	"shr.s32",
	"shr.s64",
	"shr.u8",
	"shr.u16",
	"shr.u32",
	"shr.u64",
	"shl.b8_lit",
	"shl.b16_lit",
	"shl.b32_lit",
	"shl.b64_lit",
	"shr.s8_lit",
	"shr.s16_lit",
	"shr.s32_lit",
	"shr.s64_lit",
	"shr.u8_lit",
	"shr.u16_lit",
	"shr.u32_lit",
	"shr.u64_lit",
	"shl.b8_lit1",
	"shl.b16_lit1",
	"shl.b32_lit1",
	"shl.b64_lit1",
	"shr.s8_lit1",
	"shr.s16_lit1",
	"shr.s32_lit1",
	"shr.s64_lit1",
	"shr.u8_lit1",
	"shr.u16_lit1",
	"shr.u32_lit1",
	"shr.u64_lit1",
	"mov.pred",
	"mov.s8",
	"mov.s16",
	"mov.s32",
	"mov.s64",
	"mov.u8",
	"mov.u16",
	"mov.u32",
	"mov.u64",
	"mov.f32",
	"mov.f64",
	"mov.b32_i2f",
	"mov.b32_f2i",
	"mov.b64_i2f",
	"mov.b64_f2i",
	"mov.s8_lit",
	"mov.s16_lit",
	"mov.s32_lit",
	"mov.s64_lit",
	"mov.u8_lit",
	"mov.u16_lit",
	"mov.u32_lit",
	"mov.u64_lit",
	"mov.f32_lit",
	"mov.f64_lit",
	"mov.u32_a",
	"mov.u32_ao",
	"mov.u64_a",
	"mov.u64_ao",
	"mov.b64_i22f",
	"mov.b64_f2i2",
	// ld sym
	"ld<qualifier><space>s8",
	"ld<qualifier><space>s16",
	"ld<qualifier><space>s32",
	"ld<qualifier><space>s64",
	"ld<qualifier><space>u8",
	"ld<qualifier><space>u16",
	"ld<qualifier><space>u32",
	"ld<qualifier><space>u64",
	"ld<qualifier><space>f32",
	"ld<qualifier><space>f64",
	// ld sym[offset]
	"ld<qualifier><space>s8_o",
	"ld<qualifier><space>s16_o",
	"ld<qualifier><space>s32_o",
	"ld<qualifier><space>s64_o",
	"ld<qualifier><space>u8_o",
	"ld<qualifier><space>u16_o",
	"ld<qualifier><space>u32_o",
	"ld<qualifier><space>u64_o",
	"ld<qualifier><space>f32_o",
	"ld<qualifier><space>f64_o",
	// ld [reg+offset]
	"ld<qualifier><space>s8_r",
	"ld<qualifier><space>s16_r",
	"ld<qualifier><space>s32_r",
	"ld<qualifier><space>s64_r",
	"ld<qualifier><space>u8_r",
	"ld<qualifier><space>u16_r",
	"ld<qualifier><space>u32_r",
	"ld<qualifier><space>u64_r",
	"ld<qualifier><space>f32_r",
	"ld<qualifier><space>f64_r",
	// ld small value into 32bit reg
	"ld<qualifier><space>s8_b32",
	"ld<qualifier><space>s16_b32",
	"ld<qualifier><space>u8_b32",
	"ld<qualifier><space>u16_b32",
	"ld<qualifier><space>s8_b32_o",
	"ld<qualifier><space>s16_b32_o",
	"ld<qualifier><space>u8_b32_o",
	"ld<qualifier><space>u16_b32_o",
	"ld<qualifier><space>s8_b32_r",
	"ld<qualifier><space>s16_b32_r",
	"ld<qualifier><space>u8_b32_r",
	"ld<qualifier><space>u16_b32_r",
	// 64bit address versions
	"ld<qualifier><space>s8_a64",
	"ld<qualifier><space>s16_a64",
	"ld<qualifier><space>s32_a64",
	"ld<qualifier><space>s64_a64",
	"ld<qualifier><space>u8_a64",
	"ld<qualifier><space>u16_a64",
	"ld<qualifier><space>u32_a64",
	"ld<qualifier><space>u64_a64",
	"ld<qualifier><space>f32_a64",
	"ld<qualifier><space>f64_a64",
	"ld<qualifier><space>s8_a64_o",
	"ld<qualifier><space>s16_a64_o",
	"ld<qualifier><space>s32_a64_o",
	"ld<qualifier><space>s64_a64_o",
	"ld<qualifier><space>u8_a64_o",
	"ld<qualifier><space>u16_a64_o",
	"ld<qualifier><space>u32_a64_o",
	"ld<qualifier><space>u64_a64_o",
	"ld<qualifier><space>f32_a64_o",
	"ld<qualifier><space>f64_a64_o",
	"ld<qualifier><space>s8_a64_r",
	"ld<qualifier><space>s16_a64_r",
	"ld<qualifier><space>s32_a64_r",
	"ld<qualifier><space>s64_a64_r",
	"ld<qualifier><space>u8_a64_r",
	"ld<qualifier><space>u16_a64_r",
	"ld<qualifier><space>u32_a64_r",
	"ld<qualifier><space>u64_a64_r",
	"ld<qualifier><space>f32_a64_r",
	"ld<qualifier><space>f64_a64_r",
	"ld<qualifier><space>s8_b32_a64",
	"ld<qualifier><space>s16_b32_a64",
	"ld<qualifier><space>u8_b32_a64",
	"ld<qualifier><space>u16_b32_a64",
	"ld<qualifier><space>s8_b32_a64_o",
	"ld<qualifier><space>s16_b32_a64_o",
	"ld<qualifier><space>u8_b32_a64_o",
	"ld<qualifier><space>u16_b32_a64_o",
	"ld<qualifier><space>s8_b32_a64_r",
	"ld<qualifier><space>s16_b32_a64_r",
	"ld<qualifier><space>u8_b32_a64_r",
	"ld<qualifier><space>u16_b32_a64_r",
	// for vector loads (only to global so give explicit space)
	"ld<qualifier>global.v2.s8_r",
	"ld<qualifier>global.v4.s8_r",
	"ld<qualifier>global.v2.s8_b32_r",
	"ld<qualifier>global.v4.s8_b32_r",
	"ld<qualifier>global.v2.s16_r",
	"ld<qualifier>global.v4.s16_r",
	"ld<qualifier>global.v2.s16_b32_r",
	"ld<qualifier>global.v4.s16_b32_r",
	"ld<qualifier>global.v2.s32_r",
	"ld<qualifier>global.v4.s32_r",
	"ld<qualifier>global.v2.s64_r",
	"ld<qualifier>global.v2.u8_r",
	"ld<qualifier>global.v4.u8_r",
	"ld<qualifier>global.v2.u8_b32_r",
	"ld<qualifier>global.v4.u8_b32_r",
	"ld<qualifier>global.v2.u16_r",
	"ld<qualifier>global.v4.u16_r",
	"ld<qualifier>global.v2.u16_b32_r",
	"ld<qualifier>global.v4.u16_b32_r",
	"ld<qualifier>global.v2.u32_r",
	"ld<qualifier>global.v4.u32_r",
	"ld<qualifier>global.v2.u64_r",
	"ld<qualifier>global.v2.f32_r",
	"ld<qualifier>global.v4.f32_r",
	"ld<qualifier>global.v2.f64_r",
	"ld<qualifier>global.v2.s8_a64_r",
	"ld<qualifier>global.v4.s8_a64_r",
	"ld<qualifier>global.v2.s8_b32_a64_r",
	"ld<qualifier>global.v4.s8_b32_a64_r",
	"ld<qualifier>global.v2.s16_a64_r",
	"ld<qualifier>global.v4.s16_a64_r",
	"ld<qualifier>global.v2.s16_b32_a64_r",
	"ld<qualifier>global.v4.s16_b32_a64_r",
	"ld<qualifier>global.v2.s32_a64_r",
	"ld<qualifier>global.v4.s32_a64_r",
	"ld<qualifier>global.v2.s64_a64_r",
	"ld<qualifier>global.v2.u8_a64_r",
	"ld<qualifier>global.v4.u8_a64_r",
	"ld<qualifier>global.v2.u8_b32_a64_r",
	"ld<qualifier>global.v4.u8_b32_a64_r",
	"ld<qualifier>global.v2.u16_a64_r",
	"ld<qualifier>global.v4.u16_a64_r",
	"ld<qualifier>global.v2.u16_b32_a64_r",
	"ld<qualifier>global.v4.u16_b32_a64_r",
	"ld<qualifier>global.v2.u32_a64_r",
	"ld<qualifier>global.v4.u32_a64_r",
	"ld<qualifier>global.v2.u64_a64_r",
	"ld<qualifier>global.v2.f32_a64_r",
	"ld<qualifier>global.v4.f32_a64_r",
	"ld<qualifier>global.v2.f64_a64_r",
	"ld<qualifier>global.v2.s8_o",
	"ld<qualifier>global.v4.s8_o",
	"ld<qualifier>global.v2.s8_b32_o",
	"ld<qualifier>global.v4.s8_b32_o",
	"ld<qualifier>global.v2.s16_o",
	"ld<qualifier>global.v4.s16_o",
	"ld<qualifier>global.v2.s16_b32_o",
	"ld<qualifier>global.v4.s16_b32_o",
	"ld<qualifier>global.v2.s32_o",
	"ld<qualifier>global.v4.s32_o",
	"ld<qualifier>global.v2.s64_o",
	"ld<qualifier>global.v2.u8_o",
	"ld<qualifier>global.v4.u8_o",
	"ld<qualifier>global.v2.u8_b32_o",
	"ld<qualifier>global.v4.u8_b32_o",
	"ld<qualifier>global.v2.u16_o",
	"ld<qualifier>global.v4.u16_o",
	"ld<qualifier>global.v2.u16_b32_o",
	"ld<qualifier>global.v4.u16_b32_o",
	"ld<qualifier>global.v2.u32_o",
	"ld<qualifier>global.v4.u32_o",
	"ld<qualifier>global.v2.u64_o",
	"ld<qualifier>global.v2.f32_o",
	"ld<qualifier>global.v4.f32_o",
	"ld<qualifier>global.v2.f64_o",
	"ld<qualifier>global.v2.s8_a64_o",
	"ld<qualifier>global.v4.s8_a64_o",
	"ld<qualifier>global.v2.s8_b32_a64_o",
	"ld<qualifier>global.v4.s8_b32_a64_o",
	"ld<qualifier>global.v2.s16_a64_o",
	"ld<qualifier>global.v4.s16_a64_o",
	"ld<qualifier>global.v2.s16_b32_a64_o",
	"ld<qualifier>global.v4.s16_b32_a64_o",
	"ld<qualifier>global.v2.s32_a64_o",
	"ld<qualifier>global.v4.s32_a64_o",
	"ld<qualifier>global.v2.s64_a64_o",
	"ld<qualifier>global.v2.u8_a64_o",
	"ld<qualifier>global.v4.u8_a64_o",
	"ld<qualifier>global.v2.u8_b32_a64_o",
	"ld<qualifier>global.v4.u8_b32_a64_o",
	"ld<qualifier>global.v2.u16_a64_o",
	"ld<qualifier>global.v4.u16_a64_o",
	"ld<qualifier>global.v2.u16_b32_a64_o",
	"ld<qualifier>global.v4.u16_b32_a64_o",
	"ld<qualifier>global.v2.u32_a64_o",
	"ld<qualifier>global.v4.u32_a64_o",
	"ld<qualifier>global.v2.u64_a64_o",
	"ld<qualifier>global.v2.f32_a64_o",
	"ld<qualifier>global.v4.f32_a64_o",
	"ld<qualifier>global.v2.f64_a64_o",

	// st sym
	"st<qualifier><space>s8",
	"st<qualifier><space>s16",
	"st<qualifier><space>s32",
	"st<qualifier><space>s64",
	"st<qualifier><space>u8",
	"st<qualifier><space>u16",
	"st<qualifier><space>u32",
	"st<qualifier><space>u64",
	"st<qualifier><space>f32",
	"st<qualifier><space>f64",
	// st sym[offset]
	"st<qualifier><space>s8_o",
	"st<qualifier><space>s16_o",
	"st<qualifier><space>s32_o",
	"st<qualifier><space>s64_o",
	"st<qualifier><space>u8_o",
	"st<qualifier><space>u16_o",
	"st<qualifier><space>u32_o",
	"st<qualifier><space>u64_o",
	"st<qualifier><space>f32_o",
	"st<qualifier><space>f64_o",
	// st [reg+offset]
	"st<qualifier><space>s8_r",
	"st<qualifier><space>s16_r",
	"st<qualifier><space>s32_r",
	"st<qualifier><space>s64_r",
	"st<qualifier><space>u8_r",
	"st<qualifier><space>u16_r",
	"st<qualifier><space>u32_r",
	"st<qualifier><space>u64_r",
	"st<qualifier><space>f32_r",
	"st<qualifier><space>f64_r",
	// st small value into 32bit reg
	"st<qualifier><space>s8_b32",
	"st<qualifier><space>s16_b32",
	"st<qualifier><space>u8_b32",
	"st<qualifier><space>u16_b32",
	"st<qualifier><space>s8_b32_o",
	"st<qualifier><space>s16_b32_o",
	"st<qualifier><space>u8_b32_o",
	"st<qualifier><space>u16_b32_o",
	"st<qualifier><space>s8_b32_r",
	"st<qualifier><space>s16_b32_r",
	"st<qualifier><space>u8_b32_r",
	"st<qualifier><space>u16_b32_r",
	// 64bit address versions
	"st<qualifier><space>s8_a64",
	"st<qualifier><space>s16_a64",
	"st<qualifier><space>s32_a64",
	"st<qualifier><space>s64_a64",
	"st<qualifier><space>u8_a64",
	"st<qualifier><space>u16_a64",
	"st<qualifier><space>u32_a64",
	"st<qualifier><space>u64_a64",
	"st<qualifier><space>f32_a64",
	"st<qualifier><space>f64_a64",
	"st<qualifier><space>s8_a64_o",
	"st<qualifier><space>s16_a64_o",
	"st<qualifier><space>s32_a64_o",
	"st<qualifier><space>s64_a64_o",
	"st<qualifier><space>u8_a64_o",
	"st<qualifier><space>u16_a64_o",
	"st<qualifier><space>u32_a64_o",
	"st<qualifier><space>u64_a64_o",
	"st<qualifier><space>f32_a64_o",
	"st<qualifier><space>f64_a64_o",
	"st<qualifier><space>s8_a64_r",
	"st<qualifier><space>s16_a64_r",
	"st<qualifier><space>s32_a64_r",
	"st<qualifier><space>s64_a64_r",
	"st<qualifier><space>u8_a64_r",
	"st<qualifier><space>u16_a64_r",
	"st<qualifier><space>u32_a64_r",
	"st<qualifier><space>u64_a64_r",
	"st<qualifier><space>f32_a64_r",
	"st<qualifier><space>f64_a64_r",
	"st<qualifier><space>s8_b32_a64",
	"st<qualifier><space>s16_b32_a64",
	"st<qualifier><space>u8_b32_a64",
	"st<qualifier><space>u16_b32_a64",
	"st<qualifier><space>s8_b32_a64_o",
	"st<qualifier><space>s16_b32_a64_o",
	"st<qualifier><space>u8_b32_a64_o",
	"st<qualifier><space>u16_b32_a64_o",
	"st<qualifier><space>s8_b32_a64_r",
	"st<qualifier><space>s16_b32_a64_r",
	"st<qualifier><space>u8_b32_a64_r",
	"st<qualifier><space>u16_b32_a64_r",
	// for vector stores
	"st<qualifier>global.v2.s8_r",
	"st<qualifier>global.v4.s8_r",
	"st<qualifier>global.v2.s8_b32_r",
	"st<qualifier>global.v4.s8_b32_r",
	"st<qualifier>global.v2.s16_r",
	"st<qualifier>global.v4.s16_r",
	"st<qualifier>global.v2.s16_b32_r",
	"st<qualifier>global.v4.s16_b32_r",
	"st<qualifier>global.v2.s32_r",
	"st<qualifier>global.v4.s32_r",
	"st<qualifier>global.v2.s64_r",
	"st<qualifier>global.v2.u8_r",
	"st<qualifier>global.v4.u8_r",
	"st<qualifier>global.v2.u8_b32_r",
	"st<qualifier>global.v4.u8_b32_r",
	"st<qualifier>global.v2.u16_r",
	"st<qualifier>global.v4.u16_r",
	"st<qualifier>global.v2.u16_b32_r",
	"st<qualifier>global.v4.u16_b32_r",
	"st<qualifier>global.v2.u32_r",
	"st<qualifier>global.v4.u32_r",
	"st<qualifier>global.v2.u64_r",
	"st<qualifier>global.v2.f32_r",
	"st<qualifier>global.v4.f32_r",
	"st<qualifier>global.v2.f64_r",
	"st<qualifier>global.v2.s8_a64_r",
	"st<qualifier>global.v4.s8_a64_r",
	"st<qualifier>global.v2.s8_b32_a64_r",
	"st<qualifier>global.v4.s8_b32_a64_r",
	"st<qualifier>global.v2.s16_a64_r",
	"st<qualifier>global.v4.s16_a64_r",
	"st<qualifier>global.v2.s16_b32_a64_r",
	"st<qualifier>global.v4.s16_b32_a64_r",
	"st<qualifier>global.v2.s32_a64_r",
	"st<qualifier>global.v4.s32_a64_r",
	"st<qualifier>global.v2.s64_a64_r",
	"st<qualifier>global.v2.u8_a64_r",
	"st<qualifier>global.v4.u8_a64_r",
	"st<qualifier>global.v2.u8_b32_a64_r",
	"st<qualifier>global.v4.u8_b32_a64_r",
	"st<qualifier>global.v2.u16_a64_r",
	"st<qualifier>global.v4.u16_a64_r",
	"st<qualifier>global.v2.u16_b32_a64_r",
	"st<qualifier>global.v4.u16_b32_a64_r",
	"st<qualifier>global.v2.u32_a64_r",
	"st<qualifier>global.v4.u32_a64_r",
	"st<qualifier>global.v2.u64_a64_r",
	"st<qualifier>global.v2.f32_a64_r",
	"st<qualifier>global.v4.f32_a64_r",
	"st<qualifier>global.v2.f64_a64_r",
	"st<qualifier>global.v2.s8_o",
	"st<qualifier>global.v4.s8_o",
	"st<qualifier>global.v2.s8_b32_o",
	"st<qualifier>global.v4.s8_b32_o",
	"st<qualifier>global.v2.s16_o",
	"st<qualifier>global.v4.s16_o",
	"st<qualifier>global.v2.s16_b32_o",
	"st<qualifier>global.v4.s16_b32_o",
	"st<qualifier>global.v2.s32_o",
	"st<qualifier>global.v4.s32_o",
	"st<qualifier>global.v2.s64_o",
	"st<qualifier>global.v2.u8_o",
	"st<qualifier>global.v4.u8_o",
	"st<qualifier>global.v2.u8_b32_o",
	"st<qualifier>global.v4.u8_b32_o",
	"st<qualifier>global.v2.u16_o",
	"st<qualifier>global.v4.u16_o",
	"st<qualifier>global.v2.u16_b32_o",
	"st<qualifier>global.v4.u16_b32_o",
	"st<qualifier>global.v2.u32_o",
	"st<qualifier>global.v4.u32_o",
	"st<qualifier>global.v2.u64_o",
	"st<qualifier>global.v2.f32_o",
	"st<qualifier>global.v4.f32_o",
	"st<qualifier>global.v2.f64_o",
	"st<qualifier>global.v2.s8_a64_o",
	"st<qualifier>global.v4.s8_a64_o",
	"st<qualifier>global.v2.s8_b32_a64_o",
	"st<qualifier>global.v4.s8_b32_a64_o",
	"st<qualifier>global.v2.s16_a64_o",
	"st<qualifier>global.v4.s16_a64_o",
	"st<qualifier>global.v2.s16_b32_a64_o",
	"st<qualifier>global.v4.s16_b32_a64_o",
	"st<qualifier>global.v2.s32_a64_o",
	"st<qualifier>global.v4.s32_a64_o",
	"st<qualifier>global.v2.s64_a64_o",
	"st<qualifier>global.v2.u8_a64_o",
	"st<qualifier>global.v4.u8_a64_o",
	"st<qualifier>global.v2.u8_b32_a64_o",
	"st<qualifier>global.v4.u8_b32_a64_o",
	"st<qualifier>global.v2.u16_a64_o",
	"st<qualifier>global.v4.u16_a64_o",
	"st<qualifier>global.v2.u16_b32_a64_o",
	"st<qualifier>global.v4.u16_b32_a64_o",
	"st<qualifier>global.v2.u32_a64_o",
	"st<qualifier>global.v4.u32_a64_o",
	"st<qualifier>global.v2.u64_a64_o",
	"st<qualifier>global.v2.f32_a64_o",
	"st<qualifier>global.v4.f32_a64_o",
	"st<qualifier>global.v2.f64_a64_o",

	"cvt.s8.s16",
	"cvt.s8.s32",
	"cvt.s8.s64",
	"cvt.s8.u8",
	"cvt.s8.u16",
	"cvt.s8.u32",
	"cvt.s8.u64",
	"cvt.s8.f32",
	"cvt.s8.f64",
	"cvt.s16.s8",
	"cvt.s16.s32",
	"cvt.s16.s64",
	"cvt.s16.u8",
	"cvt.s16.u16",
	"cvt.s16.u32",
	"cvt.s16.u64",
	"cvt.s16.f32",
	"cvt.s16.f64",
	"cvt.s32.s8",
	"cvt.s32.s16",
	"cvt.s32.s64",
	"cvt.s32.u8",
	"cvt.s32.u16",
	"cvt.s32.u32",
	"cvt.s32.u64",
	"cvt.s32.f32",
	"cvt.s32.f64",
	"cvt.s64.s8",
	"cvt.s64.s16",
	"cvt.s64.s32",
	"cvt.s64.u8",
	"cvt.s64.u16",
	"cvt.s64.u32",
	"cvt.s64.u64",
	"cvt.s64.f32",
	"cvt.s64.f64",
	"cvt.u8.s8",
	"cvt.u8.s16",
	"cvt.u8.s32",
	"cvt.u8.s64",
	"cvt.u8.u16",
	"cvt.u8.u32",
	"cvt.u8.u64",
	"cvt.u8.f32",
	"cvt.u8.f64",
	"cvt.u16.s8",
	"cvt.u16.s16",
	"cvt.u16.s32",
	"cvt.u16.s64",
	"cvt.u16.u8",
	"cvt.u16.u32",
	"cvt.u16.u64",
	"cvt.u16.f32",
	"cvt.u16.f64",
	"cvt.u32.s8",
	"cvt.u32.s16",
	"cvt.u32.s32",
	"cvt.u32.s64",
	"cvt.u32.u8",
	"cvt.u32.u16",
	"cvt.u32.u64",
	"cvt.u32.f32",
	"cvt.u32.f64",
	"cvt.u64.s8",
	"cvt.u64.s16",
	"cvt.u64.s32",
	"cvt.u64.s64",
	"cvt.u64.u8",
	"cvt.u64.u16",
	"cvt.u64.u32",
	"cvt.u64.f32",
	"cvt.u64.f64",
	"cvt.f32.s8",
	"cvt.f32.s16",
	"cvt.f32.s32",
	"cvt.f32.s64",
	"cvt.f32.u8",
	"cvt.f32.u16",
	"cvt.f32.u32",
	"cvt.f32.u64",
	"cvt.f32.f64",
	"cvt.f64.s8",
	"cvt.f64.s16",
	"cvt.f64.s32",
	"cvt.f64.s64",
	"cvt.f64.u8",
	"cvt.f64.u16",
	"cvt.f64.u32",
	"cvt.f64.u64",
	"cvt.f64.f32",
	// cvts in 32-bit dest reg
	"cvt.s8.s16_b32",
	"cvt.s8.s32_b32",
	"cvt.s8.u8_b32",
	"cvt.s8.u16_b32",
	"cvt.s8.u32_b32",
	"cvt.s16.s8_b32",
	"cvt.s16.s32_b32",
	"cvt.s16.u8_b32",
	"cvt.s16.u16_b32",
	"cvt.s16.u32_b32",
	"cvt.u8.s8_b32",
	"cvt.u8.s16_b32",
	"cvt.u8.s32_b32",
	"cvt.u8.u16_b32",
	"cvt.u8.u32_b32",
	"cvt.u16.s8_b32",
	"cvt.u16.s16_b32",
	"cvt.u16.s32_b32",
	"cvt.u16.u8_b32",
	"cvt.u16.u32_b32",
	// cvts in 64-bit dest reg
	"cvt.s8.s16_b64",
	"cvt.s8.s32_b64",
	"cvt.s8.s64_b64",
	"cvt.s8.u8_b64",
	"cvt.s8.u16_b64",
	"cvt.s8.u32_b64",
	"cvt.s8.u64_b64",
	"cvt.s16.s8_b64",
	"cvt.s16.s32_b64",
	"cvt.s16.s64_b64",
	"cvt.s16.u8_b64",
	"cvt.s16.u16_b64",
	"cvt.s16.u32_b64",
	"cvt.s16.u64_b64",
	"cvt.s32.s8_b64",
	"cvt.s32.s16_b64",
	"cvt.s32.s64_b64",
	"cvt.s32.u8_b64",
	"cvt.s32.u16_b64",
	"cvt.s32.u32_b64",
	"cvt.s32.u64_b64",
	"cvt.u8.s8_b64",
	"cvt.u8.s16_b64",
	"cvt.u8.s32_b64",
	"cvt.u8.s64_b64",
	"cvt.u8.u16_b64",
	"cvt.u8.u32_b64",
	"cvt.u8.u64_b64",
	"cvt.u16.s8_b64",
	"cvt.u16.s16_b64",
	"cvt.u16.s32_b64",
	"cvt.u16.s64_b64",
	"cvt.u16.u8_b64",
	"cvt.u16.u32_b64",
	"cvt.u16.u64_b64",
	"cvt.u32.s8_b64",
	"cvt.u32.s16_b64",
	"cvt.u32.s32_b64",
	"cvt.u32.s64_b64",
	"cvt.u32.u8_b64",
	"cvt.u32.u16_b64",
	"cvt.u32.u64_b64",
	"cvt.rni.s8.f32",
	"cvt.rni.s8.f64",
	"cvt.rni.s16.f32",
	"cvt.rni.s16.f64",
	"cvt.rni.s32.f32",
	"cvt.rni.s32.f64",
	"cvt.rni.s64.f32",
	"cvt.rni.s64.f64",
	"cvt.rni.u8.f32",
	"cvt.rni.u8.f64",
	"cvt.rni.u16.f32",
	"cvt.rni.u16.f64",
	"cvt.rni.u32.f32",
	"cvt.rni.u32.f64",
	"cvt.rni.u64.f32",
	"cvt.rni.u64.f64",
	"cvt.rn.f32.s8",
	"cvt.rn.f32.s16",
	"cvt.rn.f32.s32",
	"cvt.rn.f32.s64",
	"cvt.rn.f32.u8",
	"cvt.rn.f32.u16",
	"cvt.rn.f32.u32",
	"cvt.rn.f32.u64",
	"cvt.rn.f32.f64",
	"cvt.rn.f64.s8",
	"cvt.rn.f64.s16",
	"cvt.rn.f64.s32",
	"cvt.rn.f64.s64",
	"cvt.rn.f64.u8",
	"cvt.rn.f64.u16",
	"cvt.rn.f64.u32",
	"cvt.rn.f64.u64",
	"cvt.rzi.s8.f32",
	"cvt.rzi.s8.f64",
	"cvt.rzi.s16.f32",
	"cvt.rzi.s16.f64",
	"cvt.rzi.s32.f32",
	"cvt.rzi.s32.f64",
	"cvt.rzi.s64.f32",
	"cvt.rzi.s64.f64",
	"cvt.rzi.u8.f32",
	"cvt.rzi.u8.f64",
	"cvt.rzi.u16.f32",
	"cvt.rzi.u16.f64",
	"cvt.rzi.u32.f32",
	"cvt.rzi.u32.f64",
	"cvt.rzi.u64.f32",
	"cvt.rzi.u64.f64",
	// cvts in 32bit reg
	"cvt.rzi.s8.f32_b32",
	"cvt.rzi.s8.f64_b32",
	"cvt.rzi.s16.f32_b32",
	"cvt.rzi.s16.f64_b32",
	"cvt.rzi.u8.f32_b32",
	"cvt.rzi.u8.f64_b32",
	"cvt.rzi.u16.f32_b32",
	"cvt.rzi.u16.f64_b32",
	// cvts in 64bit reg
	"cvt.rzi.s8.f32_b64",
	"cvt.rzi.s8.f64_b64",
	"cvt.rzi.s16.f32_b64",
	"cvt.rzi.s16.f64_b64",
	"cvt.rzi.s32.f32_b64",
	"cvt.rzi.s32.f64_b64",
	"cvt.rzi.u8.f32_b64",
	"cvt.rzi.u8.f64_b64",
	"cvt.rzi.u16.f32_b64",
	"cvt.rzi.u16.f64_b64",
	"cvt.rzi.u32.f32_b64",
	"cvt.rzi.u32.f64_b64",
	"cvt.rz.f32.s8",
	"cvt.rz.f32.s16",
	"cvt.rz.f32.s32",
	"cvt.rz.f32.s64",
	"cvt.rz.f32.u8",
	"cvt.rz.f32.u16",
	"cvt.rz.f32.u32",
	"cvt.rz.f32.u64",
	"cvt.rz.f32.f64",
	"cvt.rz.f64.s8",
	"cvt.rz.f64.s16",
	"cvt.rz.f64.s32",
	"cvt.rz.f64.s64",
	"cvt.rz.f64.u8",
	"cvt.rz.f64.u16",
	"cvt.rz.f64.u32",
	"cvt.rz.f64.u64",
	"cvt.rmi.s8.f32",
	"cvt.rmi.s8.f64",
	"cvt.rmi.s16.f32",
	"cvt.rmi.s16.f64",
	"cvt.rmi.s32.f32",
	"cvt.rmi.s32.f64",
	"cvt.rmi.s64.f32",
	"cvt.rmi.s64.f64",
	"cvt.rmi.u8.f32",
	"cvt.rmi.u8.f64",
	"cvt.rmi.u16.f32",
	"cvt.rmi.u16.f64",
	"cvt.rmi.u32.f32",
	"cvt.rmi.u32.f64",
	"cvt.rmi.u64.f32",
	"cvt.rmi.u64.f64",
	"cvt.rm.f32.f64",
	"cvt.rm.f32.s8",
	"cvt.rm.f32.s16",
	"cvt.rm.f32.s32",
	"cvt.rm.f32.s64",
	"cvt.rm.f32.u8",
	"cvt.rm.f32.u16",
	"cvt.rm.f32.u32",
	"cvt.rm.f32.u64",
	"cvt.rm.f64.s8",
	"cvt.rm.f64.s16",
	"cvt.rm.f64.s32",
	"cvt.rm.f64.s64",
	"cvt.rm.f64.u8",
	"cvt.rm.f64.u16",
	"cvt.rm.f64.u32",
	"cvt.rm.f64.u64",
	"cvt.rpi.s8.f32",
	"cvt.rpi.s8.f64",
	"cvt.rpi.s16.f32",
	"cvt.rpi.s16.f64",
	"cvt.rpi.s32.f32",
	"cvt.rpi.s32.f64",
	"cvt.rpi.s64.f32",
	"cvt.rpi.s64.f64",
	"cvt.rpi.u8.f32",
	"cvt.rpi.u8.f64",
	"cvt.rpi.u16.f32",
	"cvt.rpi.u16.f64",
	"cvt.rpi.u32.f32",
	"cvt.rpi.u32.f64",
	"cvt.rpi.u64.f32",
	"cvt.rpi.u64.f64",
	"cvt.rp.f32.f64",
	"cvt.rp.f32.s8",
	"cvt.rp.f32.s16",
	"cvt.rp.f32.s32",
	"cvt.rp.f32.s64",
	"cvt.rp.f32.u8",
	"cvt.rp.f32.u16",
	"cvt.rp.f32.u32",
	"cvt.rp.f32.u64",
	"cvt.rp.f64.s8",
	"cvt.rp.f64.s16",
	"cvt.rp.f64.s32",
	"cvt.rp.f64.s64",
	"cvt.rp.f64.u8",
	"cvt.rp.f64.u16",
	"cvt.rp.f64.u32",
	"cvt.rp.f64.u64",
	"cvt.rni.f32.f32",
	"cvt.rni.f64.f64",
	"cvt.rzi.f32.f32",
	"cvt.rzi.f64.f64",
	"cvt.rmi.f32.f32",
	"cvt.rmi.f64.f64",
	"cvt.rpi.f32.f32",
	"cvt.rpi.f64.f64",
	"cvt.sat.f32.f32",
	"cvt.sat.f64.f64",
	"sad.s32",
	"sad.u32",
	"call",
	"call.uni",
	"bra",
	"bra.uni",
	"bra_p",
	"bra.uni_p",
	// !p form
	"bra_np", 
	"bra.uni_np",
	"exit",
	"ret",
	"nop",
	"bar.sync",
	"trap",
	"brkpt",
	// initially no intrinsics for 16 or 64-bit int,
	// but ptx supports them and may add them as intrinsics later
	"atom.global.add.s32",
	"atom.global.add.s64",
	"atom.global.add.u32",
	"atom.global.add.u64",
	"atom.global.add.f32",
	"atom.global.add.f64",
	"atom.shared.add.s32",
	"atom.shared.add.s64",
	"atom.shared.add.u32",
	"atom.shared.add.u64",
	"atom.shared.add.f32",
	"atom.shared.add.f64",
	"atom.global.min.s32",
	"atom.global.min.u32",
	"atom.global.min.f32",
	"atom.shared.min.s32",
	"atom.shared.min.u32",
	"atom.shared.min.f32",
	"atom.global.max.s32",
	"atom.global.max.u32",
	"atom.global.max.f32",
	"atom.shared.max.s32",
	"atom.shared.max.u32",
	"atom.shared.max.f32",
	"atom.global.exch.b32",
	"atom.global.exch.b64",
	"atom.shared.exch.b32",
	"atom.shared.exch.b64",
	"atom.global.exch.b32_f",
	"atom.global.exch.b64_f",
	"atom.shared.exch.b32_f",
	"atom.shared.exch.b64_f",
	"atom.global.and.b32",
	"atom.shared.and.b32",
	"atom.global.or.b32",
	"atom.shared.or.b32",
	"atom.global.xor.b32",
	"atom.shared.xor.b32",
	"atom.global.inc.u32",
	"atom.shared.inc.u32",
	"atom.global.dec.u32",
	"atom.shared.dec.u32",
	"atom.global.cas.b32",
	"atom.global.cas.b64",
	"atom.shared.cas.b32",
	"atom.shared.cas.b64",
	"atom.global.cas.b32_f",
	"atom.global.cas.b64_f",
	"atom.shared.cas.b32_f",
	"atom.shared.cas.b64_f",
	"atom.global.add.s32_a64",
	"atom.global.add.s64_a64",
	"atom.global.add.u32_a64",
	"atom.global.add.u64_a64",
	"atom.global.add.f32_a64",
	"atom.global.add.f64_a64",
	"atom.shared.add.s32_a64",
	"atom.shared.add.s64_a64",
	"atom.shared.add.u32_a64",
	"atom.shared.add.u64_a64",
	"atom.shared.add.f32_a64",
	"atom.shared.add.f64_a64",
	"atom.global.min.s32_a64",
	"atom.global.min.u32_a64",
	"atom.global.min.f32_a64",
	"atom.shared.min.s32_a64",
	"atom.shared.min.u32_a64",
	"atom.shared.min.f32_a64",
	"atom.global.max.s32_a64",
	"atom.global.max.u32_a64",
	"atom.global.max.f32_a64",
	"atom.shared.max.s32_a64",
	"atom.shared.max.u32_a64",
	"atom.shared.max.f32_a64",
	"atom.global.exch.b32_a64",
	"atom.global.exch.b64_a64",
	"atom.shared.exch.b32_a64",
	"atom.shared.exch.b64_a64",
	"atom.global.exch.b32_a64_f",
	"atom.global.exch.b64_a64_f",
	"atom.shared.exch.b32_a64_f",
	"atom.shared.exch.b64_a64_f",
	"atom.global.and.b32_a64",
	"atom.shared.and.b32_a64",
	"atom.global.or.b32_a64",
	"atom.shared.or.b32_a64",
	"atom.global.xor.b32_a64",
	"atom.shared.xor.b32_a64",
	"atom.global.inc.u32_a64",
	"atom.shared.inc.u32_a64",
	"atom.global.dec.u32_a64",
	"atom.shared.dec.u32_a64",
	"atom.global.cas.b32_a64",
	"atom.global.cas.b64_a64",
	"atom.shared.cas.b32_a64",
	"atom.shared.cas.b64_a64",
	"atom.global.cas.b32_a64_f",
	"atom.global.cas.b64_a64_f",
	"atom.shared.cas.b32_a64_f",
	"atom.shared.cas.b64_a64_f",
	// VOTE
	"vote.all.pred",
	"vote.any.pred",
	"vote.uni.pred",
	"vote.all.pred_not",
	"vote.any.pred_not",

	// ops used internally by compiler:
	"noop",
	"asm",
	"intrncall",
	"spadjust",
	"begin_pregtn",
	"end_pregtn",
      NULL);
}
