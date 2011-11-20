#define TARGET_CPU_DEFAULT (MASK_GAS)
#ifndef TARGET_ENDIAN_DEFAULT
# define TARGET_ENDIAN_DEFAULT 0
#endif
#include "auto-host.h"
#ifdef IN_GCC
/* Provide three core typedefs used by everything, if we are compiling
   GCC.  These used to be found in rtl.h and tree.h, but this is no
   longer practical.  Providing these here rather that system.h allows
   the typedefs to be used everywhere within GCC. */
struct rtx_def;
typedef struct rtx_def *rtx;
struct rtvec_def;
typedef struct rtvec_def *rtvec;
union tree_node;
typedef union tree_node *tree;
#endif
#define GTY(x)
#ifdef IN_GCC
# include "ansidecl.h"
# include "dbxelf.h"
# include "elfos.h"
# include "svr4.h"
# include "linux.h"
#if defined(TARG_MIPS) && !defined(TARG_SL)
# include "MIPS/mips.h"
# include "MIPS/linux.h"
#endif
#if defined(TARG_SL)
# include "SL/sl.h"
# include "SL/linux.h"
#endif
# include "defaults.h"
#endif
#ifndef POSIX
# define POSIX
#endif
