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


	subroutine eoshift_wd1_s7@(result, source, shift, bound, dim,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
CDIR$ ID "@(#) libfi/mpp_shift/eoshift_s_7@.f	92.0	10/08/98 14:37:14"
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		integer source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_JP7.
*
* Arguments:	result	- integer array of rank 7.
*		source	- integer array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- integer array of rank 6.
*		dim	- integer scalar: dimension to shift over.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- integer scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	integer		dim
	integer		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	integer		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	integer		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	if (dim .eq. 1) then
	    call eoshift_wd1_s7_dim1@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	else if (dim .eq. 2) then
	    call eoshift_wd1_s7_dim2@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	else if (dim .eq. 3) then
	    call eoshift_wd1_s7_dim3@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	else if (dim .eq. 4) then
	    call eoshift_wd1_s7_dim4@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	else if (dim .eq. 5) then
	    call eoshift_wd1_s7_dim5@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	else if (dim .eq. 6) then
	    call eoshift_wd1_s7_dim6@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	else
	    call eoshift_wd1_s7_dim7@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	endif
*
	return
	end


	subroutine eoshift_wd1_s7_dim1@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		integer source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_JP7.
*
* Arguments:	result	- integer array of rank 7.
*		source	- integer array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- integer array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- integer scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	integer		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	integer		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	integer		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim1@.fh"
*
	return
	end


	subroutine eoshift_wd1_s7_dim2@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		integer source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_JP7.
*
* Arguments:	result	- integer array of rank 7.
*		source	- integer array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- integer array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- integer scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	integer		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	integer		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	integer		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim2@.fh"
*
	return
	end


	subroutine eoshift_wd1_s7_dim3@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		integer source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_JP7.
*
* Arguments:	result	- integer array of rank 7.
*		source	- integer array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- integer array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- integer scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	integer		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	integer		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	integer		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim3@.fh"
*
	return
	end


	subroutine eoshift_wd1_s7_dim4@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		integer source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_JP7.
*
* Arguments:	result	- integer array of rank 7.
*		source	- integer array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- integer array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- integer scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	integer		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	integer		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	integer		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim4@.fh"
*
	return
	end


	subroutine eoshift_wd1_s7_dim5@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		integer source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_JP7.
*
* Arguments:	result	- integer array of rank 7.
*		source	- integer array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- integer array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- integer scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	integer		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	integer		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	integer		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim5@.fh"
*
	return
	end


	subroutine eoshift_wd1_s7_dim6@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		integer source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_JP7.
*
* Arguments:	result	- integer array of rank 7.
*		source	- integer array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- integer array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- integer scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	integer		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	integer		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	integer		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim6@.fh"
*
	return
	end


	subroutine eoshift_wd1_s7_dim7@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		integer source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_JP7.
*
* Arguments:	result	- integer array of rank 7.
*		source	- integer array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- integer array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- integer scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	integer		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	integer		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	integer		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim7@.fh"
*
	return
	end


	subroutine eoshift_wd2_s7@(result, source, shift, bound, dim,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		complex source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_CP7.
*
* Arguments:	result	- complex array of rank 7.
*		source	- complex array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- complex array of rank 6.
*		dim	- integer scalar: dimension to shift over.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- complex scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	integer		dim
	complex		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	complex		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	complex		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	complex		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	if (dim .eq. 1) then
	    call eoshift_wd2_s7_dim1@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	else if (dim .eq. 2) then
	    call eoshift_wd2_s7_dim2@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	else if (dim .eq. 3) then
	    call eoshift_wd2_s7_dim3@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	else if (dim .eq. 4) then
	    call eoshift_wd2_s7_dim4@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	else if (dim .eq. 5) then
	    call eoshift_wd2_s7_dim5@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	else if (dim .eq. 6) then
	    call eoshift_wd2_s7_dim6@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	else
	    call eoshift_wd2_s7_dim7@ (result, source, shift, bound,
     &		sx, shx, bx, shflag, shftval, bndflag, bndval)
	endif
*
	return
	end


	subroutine eoshift_wd2_s7_dim1@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		complex source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_CP7.
*
* Arguments:	result	- complex array of rank 7.
*		source	- complex array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- complex array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- complex scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	complex		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	complex		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	complex		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	complex		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim1@.fh"
*
	return
	end


	subroutine eoshift_wd2_s7_dim2@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		complex source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_CP7.
*
* Arguments:	result	- complex array of rank 7.
*		source	- complex array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- complex array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- complex scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	complex		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	complex		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	complex		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	complex		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim2@.fh"
*
	return
	end


	subroutine eoshift_wd2_s7_dim3@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		complex source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_CP7.
*
* Arguments:	result	- complex array of rank 7.
*		source	- complex array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- complex array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- complex scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	complex		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	complex		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	complex		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	complex		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim3@.fh"
*
	return
	end


	subroutine eoshift_wd2_s7_dim4@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		complex source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_CP7.
*
* Arguments:	result	- complex array of rank 7.
*		source	- complex array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- complex array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- complex scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	complex		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	complex		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	complex		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	complex		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim4@.fh"
*
	return
	end


	subroutine eoshift_wd2_s7_dim5@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		complex source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_CP7.
*
* Arguments:	result	- complex array of rank 7.
*		source	- complex array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- complex array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- complex scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	complex		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	complex		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	complex		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	complex		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim5@.fh"
*
	return
	end


	subroutine eoshift_wd2_s7_dim6@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		complex source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_CP7.
*
* Arguments:	result	- complex array of rank 7.
*		source	- complex array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- complex array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- complex scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	complex		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	complex		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	complex		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	complex		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim6@.fh"
*
	return
	end


	subroutine eoshift_wd2_s7_dim7@(result, source, shift, bound,
     *		sx, shx, bx, shflag, shftval, bndflag, bndval)
*
**************************************************************************
*
* Purpose:	Perform a end-of shift of an array in argument SOURCE
*		by SHIFT elements along dimension DIM.  This routine handles
*		complex source arrays of rank 7.  This routine is called
*		from the C routine _EOSHIFT_CP7.
*
* Arguments:	result	- complex array of rank 7.
*		source	- complex array of rank 7.
*		shift	- integer array of rank 6.
*		bound	- complex array of rank 6.
*		sx	- integer array of rank 1: xent of source array.
*		shx	- integer array of rank 1: xent of shift array.
*		bx	- integer array of rank 1: xent of bound array.
*		shflag	- logical scalar: shift scalar flag
*		shftval	- integer scalar: shift value if scalar
*		bndflag	- logical scalar: bound scalar flag
*		bndval	- complex scalar: bound value if scalar
*
* Variables:	mype	- integer scalar: logical PE number.
*
* Intrinsic functions called:
*		my_pe()
*		in_parallel()
*
* Documentation:
*		T3D Fortran 90 Array Intrinsics Interface Description
*		T3D Fortran 90 Array Intrinsics Design Description
*************************************************************************
c	parameter	(n$pes = 8)
	implicit	none
	intrinsic	my_pe, in_parallel, home
	integer		mype
	integer		sx(7), shx(6), bx(6)
	integer		shift(shx(1),shx(2),shx(3),shx(4),shx(5),shx(6))
	complex		bound(bx(1),bx(2),bx(3),bx(4),bx(5),bx(6))
	complex		result(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	complex		source(sx(1),sx(2),sx(3),sx(4),sx(5),sx(6),sx(7))
	integer		s_i1, s_i2, s_i3, s_i4, s_i5, s_i6, s_i7
	integer		r_i1, r_i2, r_i3, r_i4, r_i5, r_i6, r_i7
	integer		shftval
	logical		shflag, bndflag
	complex		bndval
	integer		i1, i2, i3, i4, i5, i6, i7
*
cdir$	unknown_shared	source, shift, bound
*
	include "eoshift_s7_dim7@.fh"
*
	return
	end
