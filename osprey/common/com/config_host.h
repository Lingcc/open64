/*

  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if 
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan

*/


#ifndef config_host_INCLUDED
#define config_host_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

/* ====================================================================
 * ====================================================================
 *
 * Module: config_host.h
 * $Revision: 1.1.1.1 $
 * $Date: 2005/10/21 19:00:00 $
 * $Author: marcel $
 * $Source: /proj/osprey/CVS/open64/osprey1.0/common/com/config_host.h,v $
 *
 * Revision history:
 *  15-Jun-91 - Original Version
 *
 * Description:
 *
 * This file defines general configuration parameters which are
 * specific to the compiler's host machine and system.
 *
 * See com/config.h for a detailed description of configuration
 * parameters, where they are declared, and how they are processed.
 *
 * See also:
 *	TARGET/com/defs.h -- Ubiquitous configuration parameters, e.g.
 *		basic type definitions appropriate to the host system.
 *	TARGET/com/targ_const.h -- Manipulation of target constants, as
 *		appropriate on the host system.
 *
 * ====================================================================
 * ====================================================================
 */


#ifdef _KEEP_RCS_ID
static char *config_host_rcs_id = "$Source$ $Revision$";
#endif /* _KEEP_RCS_ID */

/* What is the byte sex of the host?  Note that the variable
 * Host_Byte_Sex is set based on this definition in config_host.c.
 */
#ifdef __MINGW32__
/* windows doesn't have endian.h, assume is running little-endian on x86 */
#define HOST_IS_BIG_ENDIAN	0
#define HOST_IS_LITTLE_ENDIAN	1

#else 
/* unix systems should have endian.h */
#ifdef __APPLE__
#include <machine/endian.h>
#else
#include <endian.h>
#endif

#if defined(__BYTE_ORDER) && (__BYTE_ORDER == __BIG_ENDIAN)
#define HOST_IS_BIG_ENDIAN	1
#define HOST_IS_LITTLE_ENDIAN	0
#else
/* default to little-endian */
#define HOST_IS_BIG_ENDIAN	0
#define HOST_IS_LITTLE_ENDIAN	1
#endif
#endif

/* Does the host (compiler) support quad-precision floating point? */
#if !defined(HOST_SUPPORTS_QUAD_FLOAT)
#if defined(_COMPILER_VERSION) && (_COMPILER_VERSION >= 400) && _SGIAPI
#define HOST_SUPPORTS_QUAD_FLOAT 1
#else
#define HOST_SUPPORTS_QUAD_FLOAT 0
#endif
#endif

/* Configuration prior to flag processing: */
extern void Preconfigure_Host (void);

/* Configuration after flag processing: */
extern void Configure_Host (void);

/* Reconfiguration for each source file: */
extern void Configure_Source_Host ( char *filename );

#ifdef __cplusplus
}
#endif
#endif /* config_host_INCLUDED */
