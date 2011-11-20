/*
 * libhugetlbfs - Easy use of Linux hugepages
 * Copyright (C) 2005-2006 David Gibson & Adam Litke, IBM Corporation.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "hugetlbfs.h"

#include "libhugetlbfs_internal.h"

int __hugetlbfs_verbose = 1;
int __hugetlbfs_debug = 0;
int __hugetlbfs_prefault = 1;
char __hugetlbfs_hostname[64];

static int initialized;

static void __hugetlbfs_init_debug(void)
{
	char *env;

	if (initialized)
		return;

	env = getenv("HUGETLB_VERBOSE");
	if (env)
		__hugetlbfs_verbose = atoi(env);

	env = getenv("HUGETLB_DEBUG");
	if (env)
		__hugetlbfs_debug = 1;

	env = getenv("HUGETLB_NO_PREFAULT");
	if (env)
		__hugetlbfs_prefault = 0;

	gethostname(__hugetlbfs_hostname, sizeof(__hugetlbfs_hostname)-1);

	initialized = 1;
}

void __hugetlbfs_setup_debug(void)
{
	__hugetlbfs_init_debug();
}
