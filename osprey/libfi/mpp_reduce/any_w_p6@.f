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



      subroutine ANY_W_LP6@(result,source,dim,rext,sext,blkcnts,
     +                      npes,hi1,low1,hi2,low2,hi3,low3,hi4,
     +                      low4,hi5,low5,lmext,dist_cnt)
CDIR$ ID "@(#) libfi/mpp_reduce/any_w_p6@.f	92.0	10/08/98 14:37:14"
************************************************************************
*
* Purpose:   Determine whether any value is true in source along
*            dimension dim. This routine handles source arrays of
*            rank 6. It returns an array result. This routine is
*            called by the Fortran routine ANY_I_LP6@.
*
* Arguments: result  - logical array of rank 5.
*            source  - logical array of rank 6.
*            dim     - integer scalar: dimension to search along.
*            rext    - integer array of rank 1:
*                      extents of the result array.
*            sext    - integer array of rank 1:
*                      local extents of the source array.
*            blkcnts - integer array of rank 1:
*                      number of blocks for each dimension of the source
*                      array except for dimension dim.
*            npes    - integer scalar:
*                      number of PEs in dimension dim.
*            hix     - integer array of rank 1:
*                      the high index for each distributed block in each
*                      dimension except for dimension dim.
*            lowx    - integer array of rank 1:
*                      the low index for each distributed block in each
*                      dimension except for dimension dim.
*            lmext   - integer array of rank 1:
*                      extents of the local_any array if called within
*                      a parallel region, else it is the same as rext.
*            dist_cnt- the number of dimensions that are distributed over
*                      more than one processor between dimension 1 and
*                      dimension dim.
*
* Variables: local_any - logical array of rank 5: array of local any values.
*            length  - integer scalar: length of block subgroups for
*                      global update of result array.
*            offset  - integer scalar: offset into result array when
*                      (blkcnt < npes) or offset into local_any when
*                      (blkcnt > npes).
*            j_offset - integer scalar: offset within a block when
*                      (blkcnt < npes).
*            pe_offset - integer scalar: offset for each processor used
*                      when computing offset.
*            j_block - integer scalar: used to compute next block during
*                      the global update.
*
* Intrinsic functions called:
*            my_pe()
*            in_parallel()
*
* Documentation:
*            T3D Fortran 90 Array Intrinsics Interface Description
*            T3D Fortran 90 Array Intrinsics Design Description
*
* Author:    Ray Barriuso
*            System Libraries Section
*            Cray Research, Inc.
*
************************************************************************
      intrinsic my_pe, in_parallel
      integer blkcnts(5), length, npes, mype, dim
      integer sext(6), rext(5), lmext(5), dist_cnt
      integer offset, j_offset, pe_offset, j_block
      integer hi1(blkcnts(1)), low1(blkcnts(1))
      integer hi2(blkcnts(2)), low2(blkcnts(2))
      integer hi3(blkcnts(3)), low3(blkcnts(3))
      integer hi4(blkcnts(4)), low4(blkcnts(4))
      integer hi5(blkcnts(5)), low5(blkcnts(5))
      logical in_parallel
      logical source(sext(1),sext(2),sext(3),sext(4),sext(5),sext(6))
      logical result(rext(1),rext(2),rext(3),rext(4),rext(5))
      logical local_any(lmext(1),lmext(2),lmext(3),lmext(4),lmext(5))
*
cdir$ parallel_only
cdir$ shared result(:block,:block,:block,:block,:block)
*
*     Initialize the local and global result arrays
*
cdir$ doshared (i5,i4,i3,i2,i1) on result(i1,i2,i3,i4,i5)
      do i5 = 1, rext(5)
      do i4 = 1, rext(4)
      do i3 = 1, rext(3)
      do i2 = 1, rext(2)
      do i1 = 1, rext(1)
          result(i1,i2,i3,i4,i5) = .false.
      enddo
      enddo
      enddo
      enddo
      enddo

      do i5 = 1, lmext(5)
      do i4 = 1, lmext(4)
      do i3 = 1, lmext(3)
      do i2 = 1, lmext(2)
      do i1 = 1, lmext(1)
          local_any(i1,i2,i3,i4,i5) = .false.
      enddo
      enddo
      enddo
      enddo
      enddo
*
      include "any_w_6@.fh"
*
      return
      end
