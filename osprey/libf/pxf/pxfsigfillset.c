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


#pragma ident "@(#) libf/pxf/pxfsigfillset.c	92.1	06/29/99 11:36:06"


/*
 *  PXFSIGFILLSET -- Initialize signal set pointed to by
 *                    jsigset such that all signals defined in
 *                    POSIX.1 standard are included.  This is
 *                    one of the sigsetops primitives.
 *  (section 3.3.3 of Posix 1003.9-1992)
 *
 *  Synopsis:
 *
 *     SUBROUTINE PXFSIGFILLSET(jsigset, ierror)
 *     INTEGER jsigset, ierror
 *
 *  Where:
 *
 *	jsigset -  default integer input variable containing a
 *	           handle created by PXFSTRUCTCREATE('sigset',...)
 *	ierror  -  default integer output variable containing
 *	           status:
 *
 *           zero	- PXFSIGFILLSET was successful.
 *
 *           nonzero	- PXFSIGFILLSET was not successful.
 *
 *   PXFSIGFILLSET may return one of the following error values:
 *
 *	EFAULT     The jsigset argument points outside the
 *                 allocated space.
 *
 *	EBADHANDLE The jsigset argument is invalid.
 *
 *  DESCRIPTION:
 *
 *  Subroutine procedure PXFSIGFILLSET uses sigfillset() function
 *  to initialize the signal set pointed to by handle jsigset
 *  such that all signals defined in POSIX.1 are included.
 *
 */

#include <errno.h>
#include <fortran.h>
#include <liberrno.h>
#include <string.h>
#include <sys/signal.h>
#include "pxfstruct.h"
#include "pxfstructtable.h"
#include "table.h"

#ifdef _UNICOS
void
PXFSIGFILLSET(
#else	/* _UNICOS */
void
_PXFSIGFILLSET(
#endif	/* _UNICOS */
	_f_int *jsigset,
	_f_int *ierror
)
{
	int	stat;
	sigset_t mask;
	struct	pxfhandle pxfhand;
	*ierror = 0;
	pxfhand = _pxfhandle_table_lookup(&_pxfhandle_table, *jsigset);
	if (pxfhand.pxfstructptr == NULL || pxfhand.pxftype != PXF_SIGSET) {
		*ierror = EBADHANDLE;
		return;
	}
	mask = ((struct sig_set *)(pxfhand.pxfstructptr))->samask;
	if ((stat = (_f_int) sigfillset(&mask)) == -1)
		*ierror = errno;
	else
		((struct sig_set *)(pxfhand.pxfstructptr))->samask = mask;
	return;
}

#ifndef _UNICOS
void
pxfsigfillset_(
	_f_int *jsigset,
	_f_int *ierror
)
{
	_PXFSIGFILLSET(jsigset, ierror);
}
#endif	/* not _UNICOS */
