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


#define USE_STANDARD_TYPES
#include "defs.h"
#include "errors.h"
#include "tracing.h"
#include "matrix.h"
#include "mempool_allocator.h"
#include "cg.h"
#include "cg_swp.h"
#include "cg_swp_options.h"
#include "cg_swp_target.h"
#include "cgprep.h"
#include "glob.h"    // for Cur_PU_Name
#include "op.h"
#include "cg_loop.h"
#include "cgtarget.h"
#include "ti_si.h"
#include "cg_grouping.h"  // Defines INT32_VECTOR and CG_GROUPING


void 
SWP_Bundle(SWP_OP_vector& op_state, bool trace)
{
} // SWP_Bundle


void 
SWP_Dont_Bundle(SWP_OP_vector& op_state)
{
} // SWP_Dont_Bundle


void
SWP_Undo_Bundle(SWP_OP_vector& op_state, BB *body)
{
}

