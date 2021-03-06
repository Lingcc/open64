C
C
C  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.
C
C  This program is free software; you can redistribute it and/or modify it
C  under the terms of version 2.1 of the GNU Lesser General Public License 
C  as published by the Free Software Foundation.
C
C  This program is distributed in the hope that it would be useful, but
C  WITHOUT ANY WARRANTY; without even the implied warranty of
C  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
C
C  Further, this software is distributed without any warranty that it is
C  free of the rightful claim of any third person regarding infringement 
C  or the like.  Any license provided herein, whether implied or 
C  otherwise, applies only to this software file.  Patent licenses, if
C  any, provided herein do not apply to combinations of this program with 
C  other software, or any other product whatsoever.  
C
C  You should have received a copy of the GNU Lesser General Public 
C  License along with this program; if not, write the Free Software 
C  Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, 
C  USA.
C
C  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
C  Mountain View, CA 94043, or:
C
C  http://www.sgi.com
C
C  For further information regarding this notice, see:
C
C  http://oss.sgi.com/projects/GenInfo/NoticeExplan
C
C


	subroutine eoshift_spec_wd1_p2@(result, source, dim, sext, shftval,
     &		bndval)
*
CDIR$ ID "@(#) libfi/mpp_shift/eoshift_p_spec_2@.f	92.0	"
CDIR$ ID "10/08/98 14:37:14"
*
**************************************************************************
*
* Purpose:	Perform a circular shift of an array in argument SOURCE
*		by SHIFT elements.  This routine handles
*		integer source arrays of rank 2.  This routine is called
*		from the C routine _CSHIFT_JP2.
*
* Arguments:	result	- integer array of rank 2.
*		source	- integer array of rank 2.
*		dim	- integer scalar: dimension to shift over
*		sext	- integer array of rank 1.
*		shftval	- integer scalar: scalar shift value.
*		bndval	- integer scalar: boundary value
*		bndval	- integer scalar: boundary value.
*
* Variables:	mype	- integer scalar: logical PE number.
*		blksize	- integer array of rank 1: PE block sizes
*		pe_low	- integer scalar: PE receiving data on +1 shift
*		pe_hi	- integer scalar: PE receiving data on -1 shift
*		low	- integer array of rank 1: low indices
*		hi	- integer array of rank 1: high indices
*
* Intrinsic functions called:
*		my_pe()
*		blkct()
*		lowidx()
*		hiidx()
*		home()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
	implicit	none
	intrinsic	my_pe, blkct, lowidx, hiidx, home
	integer		sext(2)
	integer		result(sext(1),sext(2))
	integer		source(sext(1),sext(2))
	integer		dim
	integer		shftval
	integer		bndval
	integer		blksize(2), mype
	integer		pe_low, pe_hi
	integer		low(2), hi(2)
*
cdir$	unknown_shared	source, result
*
	mype = my_pe()
	if (blkct (source,1,mype) .gt. 0 .AND.
     &	    blkct (source,2,mype) .gt. 0) then
	    low(1) = lowidx(source,1,mype,1)
	    low(2) = lowidx(source,2,mype,1)
	    hi(1) = hiidx (source,1,mype,1)
	    hi(2) = hiidx (source,2,mype,1)
	    blksize(1) = hi(1) - low(1) + 1
	    blksize(2) = hi(2) - low(2) + 1
	    if (dim .eq. 1) then
		if (low(1) .gt. 1) then
		    pe_low = home (source(low(1)-1,low(2)))
		else
		    pe_low = -1
		endif
		if (hi(1) .lt. sext(1)) then
		    pe_hi = home (source(hi(1)+1,low(2)))
		else
		    pe_hi = -1
		endif
	    else
		if (low(2) .gt. 1) then
		    pe_low = home (source(low(1),low(2)-1))
		else
		    pe_low = -1
		endif
		if (hi(2) .lt. sext(2)) then
		    pe_hi = home (source(low(1),hi(2)+1))
		else
		    pe_hi = -1
		endif
	    endif
*
	    call eoshift_spec_i_wd1_p2@ (result, source, dim, sext, shftval,
     &		bndval, blksize, pe_low, pe_hi)
	endif
*
cdir$	barrier
	call shmem_udcflush()
*
	return
	end


	subroutine eoshift_spec_i_wd1_p2@ (result, source, dim, sext, shftval, 
     &		bndval, blksize, pe_low, pe_hi)
*
**************************************************************************
*
* Purpose:	Coerce a shared array to private, and call a work routine
*		which will perform a eoshift on the private arrays.
*
* Arguments:	result	- integer array of rank 2.
*		source	- integer array of rank 2.
*		dim	- integer scalar: dimension to shift over
*		sext	- integer array of rank 1.
*		shftval	- integer scalar: scalar shift value
*		bndval	- integer scalar: boundary value.
*		blksize	- integer array of rank 1: block sizes of array
*		pe_low	- integer scalar: PE receiving data on +1 shift
*		pe_hi	- integer scalar: PE receiving data on -1 shift
*
* Variables:	None
*
* Intrinsic functions called:
*		my_pe()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
*
	implicit	none
	integer		sext(2)
	integer		dim
	integer		result(sext(1),sext(2))
	integer		source(sext(1),sext(2))
	integer		shftval
	integer		bndval
	integer		blksize(2)
	integer		pe_low, pe_hi
*
cdir$	unknown_shared	source, result
cdir$	pe_resident	source, result
*
	call eoshift_spec_w_wd1_p2@ (result(1,1), source(1,1), dim, blksize,
     &		shftval, bndval, pe_low, pe_hi)
*
	return
	end


	subroutine eoshift_spec_w_wd1_p2@ (result, source, dim, sext, shftval,
     &		bndval, pe_low, pe_hi)
*
**************************************************************************
*
* Purpose:	Perform a eoshift on a coerced shared to private section
*		of a rank 2 array.  This routine will only be called for
*		scalar shift counts of -1, 0, or 1.  The PE number of the
*		PE which will receive the data passed out of this block
*		is found in pe_low for shifts of 1, and pe_hi for shifts
*		of -1.  Data will be transferred to the other PE's via
*		shmem_iputs.
*
*		This routine is divided into three main sections: shift
*		counts of -1, 1, and 0.  Within those sections are two
*		major divisions: Entire extent of dimension being eoshifted
*		over on 1 PE, and extent being spread over 2 or more PEs.
*		Lastly, these divisions have two parts: dim 1 and dim 2.
*
* Arguments:	result	- integer array of rank 2.
*		source	- integer array of rank 2.
*		dim	- integer scalar: dimension to shift over
*		sext	- integer array of rank 1.
*		shftval	- integer scalar: scalar shift value
*		bndval	- integer scalar: boundary value
*		blksize	- integer array of rank 1: block sizes of array
*		pe_low	- integer scalar: PE receiving data on +1 shift
*		pe_hi	- integer scalar: PE receiving data on -1 shift
*
* Variables:	mype	- integer scalar: PE on which we are working
*		totsx1	- integer scalar: number of words in extent 1
*		totsx2	- integer scalar: number of words in extent 2
*		str1	- integer scalar: number of words in 1 element
*
* Intrinsic functions called:
*		my_pe()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
*
	implicit	none
	intrinsic	my_pe
	integer		sext(2)
	integer		dim
	integer		result(sext(1),sext(2))
	integer		source(sext(1),sext(2))
	integer		shftval
	integer		bndval
	integer		pe_low, pe_hi
	integer		i, j
	integer		totsx1, totsx2, str1
	integer		mype
*
cdir$	pe_private	source, result
*
	mype = my_pe()
*
	totsx1 = sext(1)
	totsx2 = sext(2)
	str1 = 1
	include "eoshift_spec_2@.fh"
*
	return
	end


	subroutine eoshift_spec_wd2_p2@(result, source, dim, sext, shftval,
     &		bndval)
*
**************************************************************************
*
* Purpose:	Perform a circular shift of an array in argument SOURCE
*		by SHIFT elements.  This routine handles
*		complex source arrays of rank 2.  This routine is called
*		from the C routine _CSHIFT_JP2.
*
* Arguments:	result	- complex array of rank 2.
*		source	- complex array of rank 2.
*		dim	- integer scalar: dimension to shift over
*		sext	- integer array of rank 1.
*		shftval	- integer scalar: scalar shift value
*		bndval	- complex scalar: boundary value.
*
* Variables:	mype	- integer scalar: logical PE number.
*		blksize	- integer array of rank 1: PE block sizes
*		pe_low	- integer scalar: PE receiving data on +1 shift
*		pe_hi	- integer scalar: PE receiving data on -1 shift
*		low	- integer array of rank 1: low indices
*		hi	- integer array of rank 1: high indices
*
* Intrinsic functions called:
*		my_pe()
*		blkct()
*		lowidx()
*		hiidx()
*		home()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
	implicit	none
	intrinsic	my_pe, blkct, lowidx, hiidx, home
	integer		sext(2)
	complex		result(sext(1),sext(2))
	complex		source(sext(1),sext(2))
	integer		dim
	integer		shftval
	complex		bndval
	integer		blksize(2), mype
	integer		pe_low, pe_hi
	integer		low(2), hi(2)
*
cdir$	unknown_shared	source, result
*
	mype = my_pe()
	if (blkct (source,1,mype) .gt. 0 .AND.
     &	    blkct (source,2,mype) .gt. 0) then
	    low(1) = lowidx(source,1,mype,1)
	    low(2) = lowidx(source,2,mype,1)
	    hi(1) = hiidx (source,1,mype,1)
	    hi(2) = hiidx (source,2,mype,1)
	    blksize(1) = hi(1) - low(1) + 1
	    blksize(2) = hi(2) - low(2) + 1
	    if (dim .eq. 1) then
		if (low(1) .gt. 1) then
		    pe_low = home (source(low(1)-1,low(2)))
		else
		    pe_low = -1
		endif
		if (hi(1) .lt. sext(1)) then
		    pe_hi = home (source(hi(1)+1,low(2)))
		else
		    pe_hi = -1
		endif
	    else
		if (low(2) .gt. 1) then
		    pe_low = home (source(low(1),low(2)-1))
		else
		    pe_low = -1
		endif
		if (hi(2) .lt. sext(2)) then
		    pe_hi = home (source(low(1),hi(2)+1))
		else
		    pe_hi = -1
		endif
	    endif
*
	    call eoshift_spec_i_wd2_p2@ (result, source, dim, sext, shftval,
     &		bndval, blksize, pe_low, pe_hi)
	endif
*
cdir$	barrier
	call shmem_udcflush()
*
	return
	end


	subroutine eoshift_spec_i_wd2_p2@ (result, source, dim, sext, shftval, 
     &		bndval, blksize, pe_low, pe_hi)
*
**************************************************************************
*
* Purpose:	Coerce a shared array to private, and call a work routine
*		which will perform a eoshift on the private arrays.
*
* Arguments:	result	- complex array of rank 2.
*		source	- complex array of rank 2.
*		dim	- integer scalar: dimension to shift over
*		sext	- integer array of rank 1.
*		shftval	- integer scalar: scalar shift value
*		bndval	- complex scalar: boundary value.
*		blksize	- integer array of rank 1: block sizes of array
*		pe_low	- integer scalar: PE receiving data on +1 shift
*		pe_hi	- integer scalar: PE receiving data on -1 shift
*
* Variables:	None
*
* Intrinsic functions called:
*		my_pe()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
*
	implicit	none
	integer		sext(2)
	integer		dim
	complex		result(sext(1),sext(2))
	complex		source(sext(1),sext(2))
	integer		shftval
	complex		bndval
	integer		blksize(2)
	integer		pe_low, pe_hi
*
cdir$	unknown_shared	source, result
cdir$	pe_resident	source, result
*
	call eoshift_spec_w_wd2_p2@ (result(1,1), source(1,1), dim, blksize,
     &		shftval, bndval, pe_low, pe_hi)
*
	return
	end


	subroutine eoshift_spec_w_wd2_p2@ (result, source, dim, sext, shftval,
     &		bndval, pe_low, pe_hi)
*
**************************************************************************
*
* Purpose:	Perform a eoshift on a coerced shared to private section
*		of a rank 2 array.  This routine will only be called for
*		scalar shift counts of -1, 0, or 1.  The PE number of the
*		PE which will receive the data passed out of this block
*		is found in pe_low for shifts of 1, and pe_hi for shifts
*		of -1.  Data will be transferred to the other PE's via
*		shmem_iputs.
*
*		This routine is divided into three main sections: shift
*		counts of -1, 1, and 0.  Within those sections are two
*		major divisions: Entire extent of dimension being eoshifted
*		over on 1 PE, and extent being spread over 2 or more PEs.
*		Lastly, these divisions have two parts: dim 1 and dim 2.
*
* Arguments:	result	- complex array of rank 2.
*		source	- complex array of rank 2.
*		dim	- integer scalar: dimension to shift over
*		sext	- integer array of rank 1.
*		shftval	- integer scalar: scalar shift value
*		bndval	- complex scalar: boundary value
*		blksize	- integer array of rank 1: block sizes of array
*		pe_low	- integer scalar: PE receiving data on +1 shift
*		pe_hi	- integer scalar: PE receiving data on -1 shift
*
* Variables:    mype	- integer scalar: PE on which we are working
*		totsx1	- integer scalar: number of words in extent 1
*		totsx2	- integer scalar: number of words in extent 2
*		str1	- integer scalar: number of words in 1 element
*
* Intrinsic functions called:
*		my_pe()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
*
	implicit	none
	intrinsic	my_pe
	integer		sext(2)
	integer		dim
	complex		result(sext(1),sext(2))
	complex		source(sext(1),sext(2))
	integer		shftval
	complex		bndval
	integer		pe_low, pe_hi
	integer		i, j
	integer		totsx1, totsx2, str1
	integer		mype
*
cdir$	pe_private	source, result
*
	mype = my_pe()
*
	totsx1 = sext(1) * 2
	totsx2 = sext(2) * 2
	str1 = 2
	include "eoshift_spec_2@.fh"
*
	return
	end
