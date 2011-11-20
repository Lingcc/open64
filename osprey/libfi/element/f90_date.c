/*
 * Copyright 2005, 2006 PathScale, Inc.  All Rights Reserved.
 */

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


#pragma ident "@(#) libfi/element/f90_date.c	92.1	06/16/99 15:47:23"

#include <fortran.h>

#ifdef KEY /* Bug 8290 */
#  include "element.h"
#else /* KEY Bug 8290 */
extern void _DATE_( void *dayofyear, int  iffcd );
#endif /* KEY Bug 8290 */

/*	
 *      Duplicate names
 *
 *      _F90_DATE_	- for f90 intrinsic on non-UNICOS systems
 *      date_		- when called as a subroutine on non-UNICOS systems
 */

void
_F90_DATE_( char *ptr, int len )
{
    _DATE_(ptr, len);
}

void date_( char *ptr, int len)		{ _F90_DATE_(ptr, len); }
