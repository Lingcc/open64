/*
 * Test heap overflow for libhugetlbfs.
 * Copyright 2008 Cray Inc.  All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, 5th Floor, Boston, MA 02110-1301, USA.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <hugetlbfs.h>
#include "hugetests.h"

int main(int argc, char **argv)
{
	long hpagesize;
	int freepages;
	long size1, size2;
	void *p1, *p2;
	int st, pid, rv;

	test_init(argc, argv);

	if (!getenv("HUGETLB_MORECORE"))
		CONFIG("Must have HUGETLB_MORECORE=yes");

	hpagesize = check_hugepagesize();

	freepages = read_meminfo("HugePages_Free:");
	if (freepages < 3)
		CONFIG("Must have at least 3 free hugepages");

	/*
	 * Allocation 1: one hugepage.  Due to malloc overhead, morecore
	 * will probably mmap two hugepages.
	 */
	size1 = hpagesize;
	p1 = malloc(size1);
	if (!p1)
		FAIL("Couldn't malloc %ld bytes", size1);
	if (!test_addr_huge(p1))
		FAIL("First allocation %p not on hugepages", p1);

	/*
	 * Allocation 2: all free hugepages to ensure we exhaust the free pool.
	 */
	size2 = freepages * hpagesize;
	p2 = malloc(size2);
	if (!p2)
		FAIL("Couldn't malloc %ld bytes", size2);
	st = test_addr_huge(p2);
	verbose_printf("Second allocation %p huge?  %s\n", p2, st < 0 ? "??" :
		       (st ? "yes" : "no"));

	/*
	 * Touch the pages in a child process.  Kernel sends a SIGKILL if
	 * we run out of hugepages.
	 */
	pid = fork();
	if (pid < 0)
		FAIL("fork: %s", strerror(errno));

	if (pid == 0) {
		memset(p1, 0, size1);
		memset(p2, 0, size2);
		exit(0);
	}

	rv = waitpid(pid, &st, 0);
	if (rv < 0)
		FAIL("waitpid: %s\n", strerror(errno));
	if (WIFSIGNALED(st))
		FAIL("Child killed by signal %d touching malloc'ed memory",
		     WTERMSIG(st));

	PASS();
}
