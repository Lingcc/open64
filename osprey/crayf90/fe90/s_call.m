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


/* USMID:  "\n@(#)5.0_pl/macros/s_call.m	5.1	04/29/99 21:22:31\n" */


/*****************\
|* MISCELLANEOUS *|
\*****************/


# define MAX_NUM_ACT_TYPES		23
# define MAX_NUM_DUMMY_TYPES		9

# define ERROR_ASSOC			0
# define PASS_ADDRESS			1
# define PASS_ADDRESS_FROM_DV		2
# define PASS_DV			3
# define PASS_DV_COPY			4
# define COPY_IN			5
# define COPY_IN_COPY_OUT		6
# define MAKE_DV			7
# define COPY_IN_MAKE_DV		8
# define MAKE_NEW_DV			9
# define PASS_SECTION_ADDRESS		10
# define CHECK_CONTIG_FLAG		11
# define COPY_INOUT_MAKE_DV             12

/********************\
|* SIZES AND LIMITS *|
\********************/

# define ARGCHCK_SIZE_IDX		3
# define ARGCHCK_CHAR_LEN_IDX		4

#ifdef _TARGET64
# define NUM_TARGET_ARGCHCK_DESC_WORDS	12
# define ARGCHCK_STRUCT_TBL_IDX		12
# else
# define NUM_TARGET_ARGCHCK_DESC_WORDS	16
# define ARGCHCK_STRUCT_TBL_IDX		16
# endif

/******************************\
|* OBJECT REPLACEMENT STRINGS *|
\******************************/



/***********************************\
|* CONDITIONAL REPLACEMENT STRINGS *|
\***********************************/



/***********************************************\
|* STATEMENT/FUNCTION-LIKE REPLACEMENT STRINGS *|
\***********************************************/
