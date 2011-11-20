/*
 * Copyright 2004, 2005 PathScale, Inc.  All Rights Reserved.
 */

/* Copyright (C) 1996 Free Software Foundation, Inc.
This file is part of GNU Fortran libU77 library.

This library is free software; you can redistribute it and/or modify it
under the terms of the GNU Library General Public License as published
by the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

GNU Fortran is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with GNU Fortran; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include "config.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "f2c.h"

integer
G77_umask_0 (integer * mask)
{
  return umask ((mode_t) * mask);
}

#ifdef KEY /* Bug 1683 */
/* Provide subroutine interface too */
void
pathf90_umask(integer *mask, integer *old)
{
  integer junk;
  old = (0 == old) ? (&junk) : old;
  *old = umask((mode_t) *mask);
}
#endif /* KEY Bug 1683 */
