/*
 * Copyright 2005 PathScale, Inc.  All Rights Reserved.
 */

/*
rand.c - implementation of the elf_rand(3) function.
Copyright (C) 1995 - 1998 Michael Riepe <michael@stud.uni-hannover.de>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include <private.h>

#ifndef lint
static const char rcsid[] = "@(#) $Id: rand.c,v 1.1.1.1 2005/10/21 19:00:00 marcel Exp $";
#endif /* lint */

size_t
elf_rand(Elf *elf, size_t offset) {
    if (!elf) {
	return 0;
    }
    elf_assert(elf->e_magic == ELF_MAGIC);
    if (elf->e_kind != ELF_K_AR) {
	seterr(ERROR_NOTARCHIVE);
    }
    else if (offset <= 0 || offset > elf->e_size) {
	seterr(ERROR_BADOFF);
    }
    else {
	elf->e_off = offset;
	return offset;
    }
    return 0;
}
