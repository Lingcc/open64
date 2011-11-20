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
 * MECHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef _HUGETESTS_H
#define _HUGETESTS_H

#include <errno.h>
#include <string.h>
#define DEBUG

/* Test return codes */
#define RC_PASS 	0
#define RC_CONFIG 	1
#define RC_FAIL		2
#define RC_BUG		99

#define FOURGB (1UL << 32)

extern int verbose_test;
extern char *test_name;
void check_free_huge_pages(int nr_pages_needed);
void check_must_be_root(void);
void check_hugetlb_shm_group(void);
void test_init(int argc, char *argv[]);
int test_addr_huge(void *p);
long read_meminfo(const char *tag);
ino_t get_addr_inode(void *p);

#define ALIGN(x, a)	(((x) + (a) - 1) & ~((a) - 1))
#define PALIGN(p, a)	((void *)ALIGN((unsigned long)(p), (a)))

#ifndef barrier
# ifdef mb
#   define barrier() mb()
# else
#   define barrier() __asm__ __volatile__ ("" : : : "memory")
# endif
#endif

/* Each test case must define this function */
void cleanup(void);

#define verbose_printf(...) \
	if (verbose_test) { \
		printf(__VA_ARGS__); \
		fflush(stdout); \
	}
#define ERR	"ERR: "
#define ERROR(fmt, args...)	fprintf(stderr, ERR fmt, ## args)


#define	PASS()						\
	do {						\
		cleanup();				\
		printf("PASS\n");			\
		exit(RC_PASS);				\
	} while (0)

#define	PASS_INCONCLUSIVE()				\
	do {						\
		cleanup();				\
		printf("PASS (inconclusive)\n");	\
		exit(RC_PASS);				\
	} while (0)

#define IRRELEVANT()					\
	do {						\
		cleanup();				\
		printf("PASS (irrelevant)\n");		\
		exit(RC_PASS);				\
	} while (0)

/* Look out, gcc extension below... */
#define FAIL(fmt, ...)					\
	do {						\
		cleanup();				\
		printf("FAIL\t" fmt "\n", ##__VA_ARGS__);	\
		exit(RC_FAIL);				\
	} while (0)

#define CONFIG(fmt, ...)				\
	do {						\
		cleanup();				\
		printf("Bad configuration: " fmt "\n", ##__VA_ARGS__);	\
		exit(RC_CONFIG);			\
	} while (0)

#define TEST_BUG(fmt, ...)				\
	do {						\
		cleanup();				\
		printf("BUG in testsuite: " fmt "\n", ##__VA_ARGS__);	\
		exit(RC_BUG);				\
	} while (0)

/* stressutils.c stuff */
int remove_shmid(int shmid);

extern long gethugepagesize (void) __attribute__ ((weak));

static inline long check_hugepagesize()
{
	long hpage_size = gethugepagesize();
	if (hpage_size < 0) {
		if (errno == ENOSYS)
			CONFIG("No hugepage kernel support\n");
		else if (errno == EOVERFLOW)
			CONFIG("Hugepage size too large");
		else
			CONFIG("Hugepage size (%s)", strerror(errno));
	}
	return hpage_size;
}

#endif /* _HUGETESTS_H */
