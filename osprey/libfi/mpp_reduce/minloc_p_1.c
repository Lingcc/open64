/*

  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2.1 of the GNU Lesser General Public License 
  as published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU Lesser General Public 
  License along with this program; if not, write the Free Software 
  Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, 
  USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan

*/


#pragma ident "@(#) libfi/mpp_reduce/minloc_p_1.c	92.1	07/09/99 17:05:42"


#include <stdlib.h>
#include <liberrno.h>
#include <fmath.h>
#include <cray/dopevec.h>
#include "f90_macros.h"

#define SIGN_BIT	(1 << 63)
#define RANK		1

/*
 *	Compiler generated call: CALL _MINLOC_JP1(RESULT, SOURCE, MASK)
 *
 *	Purpose: Determine the location of the first element of SOURCE
 *	         having the minimum value of the elements identified
 *	         by MASK. This particular routine handles source arrays
 *	         of rank 1 with a data type of 64-bit integer or
 *	         64-bit floating point.
 *
 *	Arguments:
 *	        RESULT - Dope vector for result temporary array
 *	        SOURCE - Dope vector for user source array
 *	        MASK   - Dope vector for logical mask array
 *
 *      Description:
 *		This is the MPP version of MINLOC. This particular
 *		file contains the the intermediate type-specific
 *		routines. These routines parse and update the dope
 *		vectors, allocate either shared or private space for
 *		the result temporary, and possibly update the shared
 *		data desriptor (sdd) for the result temporary. Once
 *		this set-up work is complete, a Fortran subroutine
 *		is called which uses features from the Fortran
 *		Programming Model to distribute the word across all
 *		processors.
 *
 *		Include file minloc_p.h contains the rank independent
 *		source code for this routine.
 */

#include "minloc_p.h"
