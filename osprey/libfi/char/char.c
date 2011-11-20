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


#pragma ident "@(#) libfi/char/char.c	92.1	07/08/99 10:41:51"
#include <fortran.h>

/*
 *	Duplicate names
 *
 *	_CHAR_		- for f90 intrinsic on MPP and PVP
 *	$CHAR		- for cf77 intrinsic
 *	_CHAR		- for f90 3.0? and previous
 */
#ifdef _UNICOS
#pragma	_CRI duplicate _CHAR_ as $CHAR
#pragma	_CRI duplicate _CHAR_ as _CHAR
#endif

void
_CHAR_(_fcd C, _f_int *I)
{
	long	len;
	char	*cpr;

	cpr	= _fcdtocp(C);
	len	= _fcdlen (C);

	if (len > 0)
		*cpr	= (char) *I;

	return;
}
