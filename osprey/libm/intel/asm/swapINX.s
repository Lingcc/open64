  //
  //
  //  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.
  //
  //  This program is free software; you can redistribute it and/or modify it
  //  under the terms of version 2.1 of the GNU Lesser General Public License 
  //  as published by the Free Software Foundation.
  //
  //  This program is distributed in the hope that it would be useful, but
  //  WITHOUT ANY WARRANTY; without even the implied warranty of
  //  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
  //
  //  Further, this software is distributed without any warranty that it is
  //  free of the rightful claim of any third person regarding infringement 
  //  or the like.  Any license provided herein, whether implied or 
  //  otherwise, applies only to this software file.  Patent licenses, if
  //  any, provided herein do not apply to combinations of this program with 
  //  other software, or any other product whatsoever.  
  //
  //  You should have received a copy of the GNU Lesser General Public 
  //  License along with this program; if not, write the Free Software 
  //  Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, 
  //  USA.
  //
  //  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  //  Mountain View, CA 94043, or:
  //
  //  http://www.sgi.com
  //
  //  For further information regarding this notice, see:
  //
  //  http://oss.sgi.com/projects/GenInfo/NoticeExplan
  //
  //


#include <asm/errno.h>

	.section .sdata, "a", "progbits"
	.align	8
	.text

	.proc	swapINX
	.global	swapINX

	// int swapINX(int x)


 // LEAF(swapINX)

swapINX:
	alloc	loc0=ar.pfs,1,1,0,0
	mov	r14=ar.fpsr	// fetch floating point status field
	;;
	extr.u	r8=r14,18,1	// copy out inexact flag bit
	;;
	dep	r16=in0,r8,18,1 // copy in new inexact flag bit
	;;
	mov	ar.fpsr=r16
	mov	ar.pfs=loc0
	br.ret.sptk  rp
	.endp

