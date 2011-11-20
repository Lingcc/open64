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


#pragma ident "@(#) libfi/mpp_scan/scanmin_jp_7.c	92.1	07/13/99 10:21:33"

#include <stdlib.h>
#include <liberrno.h>
#include <fmath.h>
#include <cray/dopevec.h>
#include "f90_macros.h"

#define RANK		7

/*
 *	Compiler generated call: CALL _SCANMIN_JP7(RES, SRC, STOP, DIM, MASK)
 *
 *	Purpose: Determine the maximum value of the elements of SRC
 *	         along dimension DIM corresponding to the true elements
 *	         of MASK. This particular routine handles source arrays
 *	         of rank 7 with a data type of 64-bit integer.
 *
 *	Arguments:
 *	        RES    - Dope vector for temporary result array
 *		SRC    - Dope vector for user source array
 *		STOP   - Dope vector for stop array
 *	        DIM    - Dimension to operate along
 *	        MASK   - Dope vector for logical mask array
 *
 *      Description:
 *		This is the MPP version of SCANMIN. This particular
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
 *		Include file segmented_scan_p.h contains the rank independent
 *		source code for this routine.
 */

void
_SCANMIN_JP7 (	DopeVectorType	*result,
		DopeVectorType	*source,
		DopeVectorType	*stop,
		long		*dim,
		DopeVectorType	*mask)
{
	
#include "segmented_scan_p.h"

	if (stop_flag > 0) {
	    if (mask_flag == 1) {
		SCANMIN_MASK_JP7@ (result_sdd_ptr, source_sdd_ptr,
			stop_sdd_ptr, &dim_val, mask_sdd_ptr, src_extents,
			blkcnts);
	    } else {
		SCANMIN_NOMASK_JP7@ (result_sdd_ptr, source_sdd_ptr,
			stop_sdd_ptr, &dim_val, src_extents, blkcnts);
	    }
	}
}
