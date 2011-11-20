/* config.h.  Generated from config.h.in by configure.  */
#if !defined __ASSEMBLER__ && !defined _ISOMAC && !defined __OPTIMIZE__
# error "glibc cannot be compiled without optimization"
#endif

/* Another evil option when it comes to compiling the C library is
   --ffast-math since it alters the ABI.  */
#if defined __FAST_MATH__ && !defined TEST_FAST_MATH
# error "glibc must not be compiled with -ffast-math"
#endif

/* Define if using ELF, which supports weak symbols.
   This implies HAVE_ASM_WEAK_DIRECTIVE and NO_UNDERSCORES; set by
   --with-elf.  */
#define	HAVE_ELF 1

/* Define if building with SELinux support.  Set by --with-selinux.  */
/* #undef	HAVE_SELINUX */

/* Defined if building with SELinux support & audit libs are detected. */
/* #undef	HAVE_LIBAUDIT */

/* Defined if building with SELinux support & libcap libs are detected.  */
/* #undef  HAVE_LIBCAP */

/* Define if using XCOFF. Set by --with-xcoff.  */
/* #undef	HAVE_XCOFF */

/* Define if C symbols are asm symbols.  Don't define if C symbols
   have a `_' prepended to make the asm symbol.  */
#define	NO_UNDERSCORES 1

/* Define if weak symbols are available via the `.weak' directive.  */
#define	HAVE_ASM_WEAK_DIRECTIVE 1

/* Define if weak symbols are available via the `.weakext' directive.  */
/* #undef	HAVE_ASM_WEAKEXT_DIRECTIVE */

/* Define if CFI directives are available.  */
#define	HAVE_ASM_CFI_DIRECTIVES 1

/* Define to the assembler line separator character for multiple
   assembler instructions per line.  Default is `;'  */
/* #undef ASM_LINE_SEP */

/* Define if not using ELF, but `.init' and `.fini' sections are available.  */
/* #undef	HAVE_INITFINI */

/* Define if __attribute__((section("foo"))) puts quotes around foo.  */
/* #undef  HAVE_SECTION_QUOTES */

/* Define if the assembler supports the `.set' directive.  */
#define	HAVE_ASM_SET_DIRECTIVE 1

/* Define to the name of the assembler's directive for
   declaring a symbol global (default `.globl').  */
#define	ASM_GLOBAL_DIRECTIVE .globl

/* Define to the prefix before `object' or `function' in the
   assembler's `.type' directive, if it has one.  */
#define	ASM_TYPE_DIRECTIVE_PREFIX @

/* Define a symbol_name as a global .symbol_name for ld.  */
/* #undef	HAVE_ASM_GLOBAL_DOT_NAME */

/* On powerpc64, use overlapping .opd entries.  */
/* #undef  USE_PPC64_OVERLAPPING_OPD */

/* Define if the assembler generates debugging information directly.  */
#define	HAVE_CPP_ASM_DEBUGINFO 1

/* Define if _Unwind_Find_FDE should be exported from glibc.  */
/* #undef  EXPORT_UNWIND_FIND_FDE */

/* Define to use GNU libio instead of GNU stdio.
   This is defined by configure under --enable-libio.  */
#define	USE_IN_LIBIO 1

/* Define if using ELF and the assembler supports the `.previous'
   directive.  */
#define	HAVE_ASM_PREVIOUS_DIRECTIVE 1

/* Define if using ELF and the assembler supports the `.popsection'
   directive.  */
/* #undef	HAVE_ASM_POPSECTION_DIRECTIVE */

/* Define if versioning of the library is wanted.  */
#define	DO_VERSIONING 1

/* Defined to the oldest ABI we support, like 2.1.  */
/* #undef GLIBC_OLDEST_ABI */

/* Define if static NSS modules are wanted.  */
/* #undef	DO_STATIC_NSS */

/* Define if the compiler supports __builtin_expect.  */
#define	HAVE_BUILTIN_EXPECT 1

/* Define if the compiler supports __builtin_memset.  */
/* #undef	HAVE_BUILTIN_MEMSET */

/* Define if __asm () on built-in function's prototype causes redirection of
   the builtin.  */
#define	HAVE_BUILTIN_REDIRECTION 1

/* Define if the __thread keyword is supported.  */
#define HAVE___THREAD 1

/* Define if the compiler supports __attribute__((tls_model(""))).  */
#define HAVE_TLS_MODEL_ATTRIBUTE 1

/* Define if the regparm attribute shall be used for local functions
   (gcc on ix86 only).  */
/* #undef	USE_REGPARMS */

/* Defined on PowerPC if the GCC being used has a problem with clobbering
   certain registers (CR0, MQ, CTR, LR) in asm statements.  */
/* #undef	BROKEN_PPC_ASM_CR0 */

/* Defined on SPARC if ld doesn't handle R_SPARC_WDISP22 against .hidden
   symbol.  sysdeps/sparc/sparc32/elf/configure.  */
/* #undef	BROKEN_SPARC_WDISP22 */

/* Define if the linker supports the -z combreloc option.  */
#define	HAVE_Z_COMBRELOC 1

/* Define if _rtld_local structure should be forced into .sdata section.  */
/* #undef	HAVE_SDATA_SECTION */

/* Define if binutils support TLS handling.  */
#define	HAVE_TLS_SUPPORT 1

/* Define if the compiler's exception support is based on libunwind.  */
/* #undef	HAVE_CC_WITH_LIBUNWIND */

/* Define if the access to static and hidden variables is position independent
   and does not need relocations.  */
#define	PI_STATIC_AND_HIDDEN 1

/* Define this to disable the `hidden_proto' et al macros in
   include/libc-symbols.h that avoid PLT slots in the shared objects.  */
/* #undef	NO_HIDDEN */


/* Defined to some form of __attribute__ ((...)) if the compiler supports
   a different, more efficient calling convention.  */
#if defined USE_REGPARMS && !defined PROF && !defined __BOUNDED_POINTERS__
# define internal_function __attribute__ ((regparm (3), stdcall))
#endif

/* Linux specific: minimum supported kernel version.  */
#define	__LINUX_KERNEL_VERSION (2 * 65536 + 4 * 256 + 0)

/* Override abi-tags ABI version if necessary.  */
#define  __ABI_TAG_VERSION 2,4,0

/* bash 2.0 introduced the _XXX_GNU_nonoption_argv_flags_ variable to help
   getopt determine whether a parameter is a flag or not.  This features
   was disabled later since it caused trouble.  We are by default therefore
   disabling the support as well.  */
/* #undef USE_NONOPTION_FLAGS */

/* Mach/Hurd specific: define if mig supports the `retcode' keyword.  */
/* #undef	HAVE_MIG_RETCODE */

/* Mach specific: define if the `host_page_size' RPC is available.  */
/* #undef	HAVE_HOST_PAGE_SIZE */

/* Mach/i386 specific: define if the `i386_io_perm_*' RPCs are available.  */
/* #undef	HAVE_I386_IO_PERM_MODIFY */

/* Mach/i386 specific: define if the `i386_set_gdt' RPC is available.  */
/* #undef	HAVE_I386_SET_GDT */

/* Defined if forced unwind support is available.  */
#define	HAVE_FORCED_UNWIND 1

/* Defined of libidn is available.  */
#define HAVE_LIBIDN 1

/* Define if inlined system calls are available.  */
#define HAVE_INLINED_SYSCALLS 1

/* Define if your assembler and linker support R_PPC_REL16* relocs.  */
/* #undef HAVE_ASM_PPC_REL16 */

/* Define if your compiler defaults to -msecure-plt mode on ppc.  */
/* #undef HAVE_PPC_SECURE_PLT */

/* Define if __stack_chk_guard canary should be randomized at program startup.  */
/* #undef ENABLE_STACKGUARD_RANDOMIZE */

/*
 */

#ifndef	_LIBC

/* These symbols might be defined by some sysdeps configures.
   They are used only in miscellaneous generator programs, not
   in compiling libc itself.   */

/* sysdeps/generic/configure.in */
/* #undef	HAVE_PSIGNAL */

/* sysdeps/unix/configure.in */
/* #undef	HAVE_STRERROR */

/* sysdeps/unix/common/configure.in */
/* #undef	HAVE_SYS_SIGLIST */
/* #undef	HAVE__SYS_SIGLIST */
/* #undef	HAVE__CTYPE_ */
/* #undef	HAVE___CTYPE_ */
/* #undef	HAVE___CTYPE */
/* #undef	HAVE__CTYPE__ */
/* #undef	HAVE__CTYPE */
/* #undef	HAVE__LOCP */

#endif

/*
 */

#ifdef	_LIBC

/* The zic and zdump programs need these definitions.  */

#define	HAVE_STRERROR	1

/* The locale code needs these definitions.  */

#define HAVE_REGEX 1

#endif
