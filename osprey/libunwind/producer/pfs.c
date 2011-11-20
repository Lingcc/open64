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



#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <sys/unwindP.h>
#include "unwind_producer.h"



/* producer function to add a prologue pfs_when descriptor */
__unw_error_t unwind_info_add_prologue_pfs_when_info(__unw_info_t *info,
								__uint64_t when) {
	__unw_error_t ret = __UNW_OK;
	__unw_format_p7_t *desc;
	__uint64_t rsize, esize;
	char encoded[1+__UNW_ENCODING_SIZE];

	/* check valid info argument */
	if (NULL == info) {
		return __UNW_NULL_ERROR;
	} else if (_unwind_info + _unwind_info_size != info) {
		return __UNW_INV_ARG_ERROR;
	}

	/* check valid time argument */
	if (when >= _current_region_total_size) {
		return __UNW_INV_SIZE_ERROR;
	}

	/* construct and add the pfs_when descriptor */
	/* format P7 */
	/* 7 6 5 4 3 2 1 0           */ 
	/* 1 1 1 0 0 1 1 0 t(LEB128) */
	encoded[0] = 0xe6;
	if ((esize = __leb128_encode((char *)&encoded[1],
			(__uint64_t)__UNW_ENCODING_SIZE,
			when)) == 0) {
		return __UNW_INTERNAL_ERROR;
	}

	desc = (__unw_format_p7_t *)&encoded;
	rsize = 1 + esize;

	/* add descriptor */
	ret = unwind_info_add_desc(rsize, (char *)desc);

	return ret;
}



/* producer function to add a prologue pfs_gr descriptor */
__unw_error_t unwind_info_add_prologue_pfs_gr_info(__unw_info_t *info, __uint32_t gr) {
	__unw_error_t ret = __UNW_OK;
	__unw_format_p3_t desc;
	__uint64_t rsize;

	/* check valid info argument */
	if (NULL == info) {
		return __UNW_NULL_ERROR;
	} else if (_unwind_info + _unwind_info_size != info) {
		return __UNW_INV_ARG_ERROR;
	}

	/* construct and add the pfs_gr descriptor */
	/* format P3 */
	/* 7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0 */ 
	/* 1 0 1 1 0 0 0 1 0 gr            */
	if (gr >= 128) {
		return __UNW_INV_ARG_ERROR;
	}
	desc._fix[0] = 0xb1;
	desc._fix[1] = 0x00;
	desc._fix[1] |= gr;
	rsize = 2;

	/* add descriptor */
	ret = unwind_info_add_desc(rsize, (char *)&desc);

	return ret;
}



/* producer function to add a prologue pfs_psprel descriptor */
__unw_error_t unwind_info_add_prologue_pfs_psprel_info(__unw_info_t *info,
								__uint64_t offset) {
	__unw_error_t ret = __UNW_OK;
	__unw_format_p7_t *desc;
	__uint64_t rsize, esize;
	char encoded[1+__UNW_ENCODING_SIZE];

	/* check valid info argument */
	if (NULL == info) {
		return __UNW_NULL_ERROR;
	} else if (_unwind_info + _unwind_info_size != info) {
		return __UNW_INV_ARG_ERROR;
	}

	/* construct and add the pfs_psprel descriptor */
	/* format P7 */
	/* 7 6 5 4 3 2 1 0                */ 
	/* 1 1 1 0 0 1 1 1 pspoff(LEB128) */
	encoded[0] = 0xe7;
	if ((esize = __leb128_encode((char *)&encoded[1],
			(__uint64_t)__UNW_ENCODING_SIZE,
			offset)) == 0) {
		return __UNW_INTERNAL_ERROR;
	}

	desc = (__unw_format_p7_t *)&encoded;
	rsize = 1 + esize;

	/* add descriptor */
	ret = unwind_info_add_desc(rsize, (char *)desc);

	return ret;
}



/* producer function to add a prologue pfs_sprel descriptor */
__unw_error_t unwind_info_add_prologue_pfs_sprel_info(__unw_info_t *info,
								__uint64_t offset) {
	__unw_error_t ret = __UNW_OK;
	__unw_format_p8_t *desc;
	__uint64_t rsize, esize;
	char encoded[2+__UNW_ENCODING_SIZE];

	/* check valid info argument */
	if (NULL == info) {
		return __UNW_NULL_ERROR;
	} else if (_unwind_info + _unwind_info_size != info) {
		return __UNW_INV_ARG_ERROR;
	}

	/* construct and add the pfs_sprel descriptor */
	/* format P8 */
	/* 7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0               */ 
	/* 1 1 1 1 0 0 0 0 0 0 0 0 0 0 1 0 spoff(LEB128) */
	encoded[0] = 0xf0;
	encoded[1] = 0x02;
	if ((esize = __leb128_encode((char *)&encoded[2],
			(__uint64_t)__UNW_ENCODING_SIZE,
			offset)) == 0) {
		return __UNW_INTERNAL_ERROR;
	}

	desc = (__unw_format_p8_t *)&encoded;
	rsize = 2 + esize;

	/* add descriptor */
	ret = unwind_info_add_desc(rsize, (char *)desc);

	return ret;
}
