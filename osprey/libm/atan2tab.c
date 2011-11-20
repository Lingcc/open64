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



/* ====================================================================
 * ====================================================================
 *
 * Module: atan2tab.c
 * $Revision: 1.1.1.1 $
 * $Date: 2005/10/21 19:00:00 $
 * $Author: marcel $
 * $Source: /proj/osprey/CVS/open64/osprey1.0/libm/atan2tab.c,v $
 *
 * Revision history:
 *  09-Jun-93 - Original Version
 *
 * Description:	error tables for atan2 function
 *
 * ====================================================================
 * ====================================================================
 */

static char *rcs_id = "$Source: /proj/osprey/CVS/open64/osprey1.0/libm/atan2tab.c,v $ $Revision: 1.1.1.1 $";

#include "libm.h"

const du	_atan2res0[] =
{
{D(0x00000000, 0x00000000)},
{D(0x80000000, 0x00000000)},
{D(0x400921fb, 0x54442d18)},
{D(0xc00921fb, 0x54442d18)},
};

const du	_atan2res1[] =
{
{D(0x3ff921fb, 0x54442d18)},
{D(0xbff921fb, 0x54442d18)},
{D(0x3ff921fb, 0x54442d18)},
{D(0xbff921fb, 0x54442d18)},
};

const du	_atan2res2[] =
{
{D(0x00000000, 0x00000000)},
{D(0x80000000, 0x00000000)},
{D(0x400921fb, 0x54442d18)},
{D(0xc00921fb, 0x54442d18)},
};

const du	_atan2res4[] =
{
{D(0x00000000, 0x00000000)},
{D(0x00000000, 0x00000000)},
{D(0x3ff921fb, 0x54442d18)},
{D(0xbff921fb, 0x54442d18)},
{D(0x00000000, 0x00000000)},
{D(0x00000000, 0x00000000)},
{D(0x3ff921fb, 0x54442d18)},
{D(0xbff921fb, 0x54442d18)},
{D(0x00000000, 0x00000000)},
{D(0x80000000, 0x00000000)},
{D(0x3fe921fb, 0x54442d18)},
{D(0xbfe921fb, 0x54442d18)},
{D(0x400921fb, 0x54442d18)},
{D(0xc00921fb, 0x54442d18)},
{D(0x4002d97c, 0x7f3321d2)},
{D(0xc002d97c, 0x7f3321d2)},
};

