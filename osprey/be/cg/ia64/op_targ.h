/*

  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved.

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
 *  CGIR operation structure (OP) and utility routines which include target
 *  dependencies.
 *
 *  THIS FILE IS ONLY TO BE INCLUDE BY ../op.h!!!!
 *
 * ====================================================================
 * ====================================================================
 */

#ifndef op_targ_INCLUDED
#define op_targ_INCLUDED

#define OP_COPY_OPND 1
#define OP_PREDICATE_OPND 0

/* -----------------------------------------------------------------------
 * See be/cg/op.h for interface
 * -----------------------------------------------------------------------
 */
inline BOOL 
OP_same_res(OP *op)
{
  return TOP_is_same_res(OP_code(op));
}

/* -----------------------------------------------------------------------
 * check if an operation that saves all the predicate registers
 * -----------------------------------------------------------------------
 */
inline BOOL
OP_save_predicates(OP *op)
{
  return OP_code(op) == TOP_mov_f_pr;
}

/* -----------------------------------------------------------------------
 * check if an operation that restores all the predicate registers
 * -----------------------------------------------------------------------
 */
inline BOOL
OP_restore_predicates(OP *op)
{
  return OP_code(op) == TOP_mov_t_pr;
}

#endif /* op_targ_INCLUDED */
