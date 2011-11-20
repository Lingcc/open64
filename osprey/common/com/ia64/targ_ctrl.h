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


#ifndef targ_ctrl_INCLUDED
#define targ_ctrl_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

/* ====================================================================
 * ====================================================================
 *
 * Module: targ_ctrl.h
 * $Revision: 1.1.1.1 $
 * $Date: 2005/10/21 19:00:00 $
 * $Author: marcel $
 * $Source: /proj/osprey/CVS/open64/osprey1.0/common/com/ia64/targ_ctrl.h,v $
 *
 * Description:
 *
 * This file contains target-specific control information.  It is
 * included in controls.c and should not be visible elsewhere.
 *
 * ====================================================================
 * ====================================================================
 */


#ifdef _KEEP_RCS_ID
static char *targ_ctrl_rcs_id = "$Source: /proj/osprey/CVS/open64/osprey1.0/common/com/ia64/targ_ctrl.h,v $ $Revision: 1.1.1.1 $";
#endif /* _KEEP_RCS_ID */

static STR_LIST Targ_1 = {"IA64", NULL};

#define Possible_Targets Targ_1
#define TARG_FIRST_DEF 0
#define TARG_SECOND_DEF 0

#ifdef __cplusplus
}
#endif
#endif /* targ_ctrl_INCLUDED */
