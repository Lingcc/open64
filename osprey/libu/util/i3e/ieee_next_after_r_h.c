/*
 * Copyright 2004 PathScale, Inc.  All Rights Reserved.
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


static const char USMID[] = "@(#) libu/util/i3e/ieee_next_after_r_h.c	92.0	10/08/98 14:57:41";

#include <fenv.h>
#include <float.h>
#include <fp.h>
#include "i3eintrin.h"

extern double _IEEE_NEXT_AFTER_R_H(double x, float y);

/* NEXT_AFTER - return the nearest different machine representable number
 * 	        in a given direction y for 64-bit values.
 *	INPUT:  64-bit float x
 *	        32-bit float y
 * 	RETURN:
 * 	        the argument x if x = y.
 * 	        the argument x if X = NaN.
 * 	        the argument y if y = NaN.
 * 	        Raise inexact for overflow or underflow and return
 *
 */
#pragma _CRI duplicate _IEEE_NEXT_AFTER_R_H as _IEEE_NEXT_AFTER_8_4
double
_IEEE_NEXT_AFTER_R_H(double x, float y)
{
	/* Union defined to work with IEEE 64-bit floating point. */
	union _ieee_double {
		double	dword;
		long long lword;
		struct {
#if __BYTE_ORDER == __LITTLE_ENDIAN
			unsigned int mantissa : IEEE_64_MANT_BITS;
			unsigned int exponent : IEEE_64_EXPO_BITS;
			unsigned int sign     : 1;
#else
			unsigned int sign     : 1;
			unsigned int exponent : IEEE_64_EXPO_BITS;
			unsigned int mantissa : IEEE_64_MANT_BITS;
#endif
		} parts;
	};

	int xfpclas	= _fpclassify(x);
	int yfpclas	= _fpclassifyf(y);
	if (xfpclas == FP_NAN) {
		return x;
	} else if (yfpclas == FP_NAN) {
		union _ieee_double x_val;
		x_val.dword	= _SGL_NaN;
		return(x_val.dword);
	} else if (xfpclas == FP_ZERO && yfpclas == FP_ZERO) {
		return x;
	} else if (xfpclas == FP_INFINITE) {
		return x;
	} else if (x == (double) y) {
		return x;
	} else if (xfpclas == FP_ZERO) {
		union _ieee_double x_val;
		x_val.dword = DBL_MIN;
		x_val.parts.sign	 = x > (double) y;

		/* return smallest normal number */
		return(x_val.dword);
	} else {  /* first argument is normal or denormal */
		union _ieee_double x_val;
		int j;
		int resfpclas;

		x_val.dword	 = x;

		/* move one bit in the correct direction.
		 ** Because of the way the implicit bit works,
		 ** the exponent field is handled correctly.
		 */
		if (x > 0) {
			x_val.lword += (x > (double) y) ? -1 : 1;
		} else {
			x_val.lword += (x > (double) y) ? 1 : -1;
		}

		/* test for underflow or overflow */
		if (_isnormal(x_val.dword))
			return(x_val.dword);

		/*
		 * Raise overflow exception for infinite result and
		 * underflow exception for too small result.  Raise
		 * inexact exception for both cases. Allow subnormal
		 * values to return without exception.
		 */
		resfpclas	= _fpclassify(x_val.dword);
		if (resfpclas == FP_INFINITE) {
			j	= FE_OVERFLOW;
			feraiseexcept(j);
		} else if (resfpclas == FP_ZERO) {
			j	= FE_UNDERFLOW;
			feraiseexcept(j);
		} else {
			return(x_val.dword);
		}
		j	= FE_INEXACT;
		feraiseexcept(j);
		return(x_val.dword);
	}
}
