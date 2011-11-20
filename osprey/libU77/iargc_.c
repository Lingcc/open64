/*
 * Copyright 2004, 2005, 2006 PathScale, Inc.  All Rights Reserved.
 */

/*

  Copyright (C) 1999-2001, Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2.1 of the GNU Lesser General Public License
  as published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  Further, any
  license provided herein, whether implied or otherwise, is limited to 
  this program in accordance with the express provisions of the 
  GNU Lesser General Public License.  

  Patent licenses, if any, provided herein do not apply to combinations 
  of this program with other product or programs, or any other product 
  whatsoever.  This program is distributed without any warranty that the 
  program is delivered free of the rightful claim of any third person by 
  way of infringement or the like.  

  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

*/

/* $Header: /proj/osprey/CVS/open64/osprey1.0/libU77/iargc_.c,v 1.1.1.1 2005/10/21 19:00:00 marcel Exp $ */
 /* 
   return the number of args on the command line following the command name
  
   calling sequence:
  	nargs = iargc()
   where:
  	nargs will be set to the number of args

 */
#include "externals.h"

#ifdef KEY /* Bug 1683 */

#include "pathf90_libU_intrin.h"

pathf90_i4
pathf90_iargc(void) {
  return ARGC - 1;
  }

#else

extern int
iargc_(void)
{
   return ARGC - 1;
}
#endif /* KEY Bug 1683 */
