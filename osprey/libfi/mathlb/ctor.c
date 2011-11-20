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


#pragma ident "@(#) libfi/mathlb/ctor.c	92.1	07/09/99 11:00:36"


#include <fortran.h>
#include <fp.h>
#include <math.h>
#include "mathdefs.h"

extern void _CTOR(c_complex_t *ret_val, c_complex_t x, _f_real8 *r);

/*
 *      complex(kind=8) raised to a real(kind=8) = _CTOR
 *
 *	x = a+b*i
 *
 *	if ((x == 0+0*i) && (y == 0)) then return(NAN)
 *	if (x == 0+0*i) then return(0+0*i)
 *	if (y == 0) then return(1+0*i)
 */
void
_CTOR(c_complex_t *ret_val,
	c_complex_t x,
	_f_real8 *r)
{
	_f_real8 __atan2(_f_real8 x, _f_real8 y);
	_f_real8 __cos(_f_real8 x);
	_f_real8 __exp(_f_real8 x);
	_f_real8 __log(_f_real8 x);
	_f_real8 __sin(_f_real8 x);
	_f_real8 _CABS(c_complex_t z);
	_f_real8 y = *r;
	_f_real8 one;
	_f_real8 two;
	if (x.real == (_f_real8) 0.0 && x.imag == (_f_real8) 0.0) {
		if (y == (_f_real8) 0.0) {
			ret_val->real = _SGL_NaN;
			ret_val->imag = _SGL_NaN;
		}
		else {
			ret_val->real = (_f_real8) 0.0;
			ret_val->imag = (_f_real8) 0.0;
		}
		return;
	}
	one = y * __atan2(x.imag, x.real);
	two = y * __log(_CABS(x));
	ret_val->real = __exp(two) * __cos(one);
	ret_val->imag = __exp(two) * __sin(one);
}
