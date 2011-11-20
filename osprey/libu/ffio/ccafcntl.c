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


#pragma ident "@(#) libu/ffio/ccafcntl.c	92.2	10/11/99 15:29:41"


#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ffio.h>
#include "ccaio.h"

/*
 * cache layer fcntl requests
 *
 *	Returns: -1 if error occurred
 *		  0 if OK
 */
_cca_fcntl(
struct fdinfo	*fio,		/* file descriptor */
int		cmd,		/* command code */
void		*arg,		/* command-specific parameter */
struct ffsw	*iostat)	/* pointer to status return word */
{
	struct fdinfo *llfio;
	struct ffc_info_s *ffcp, locinfo;
	struct cca_f *cca_info;
	int ret, llfd;

        struct ffsw *check_ffsw;
        struct cca_async_tracker *this_tracker;

	cca_info = (struct cca_f *) fio->lyr_info;
	llfio = fio->fioptr;

	if(CCA_SOFT_BYPASS) {
		int ret;
		ret = XRCALL(llfio,fcntlrtn) llfio, cmd, arg, iostat);
		if (cmd == FC_GETINFO) {
			ffcp = (struct ffc_info_s *)arg;
			ffcp->ffc_flags &= ~(FFC_CANLISTIO);
		}
		return(ret);
	}

	ret = 0;

	switch(cmd) {

	case FC_GETINFO:
		ffcp = (struct ffc_info_s *)arg;
/*
 *		Only do a call to the lower level if it has been opened
 */
		if (llfio != NULL) {
			ret = XRCALL(llfio,fcntlrtn)
					llfio, FC_GETINFO, &locinfo, iostat);
			llfd = locinfo.ffc_fd; /* fd from lower layer */
		}
		else {
			locinfo.ffc_flags = 0;
			llfd = -1;
		}

		ffcp->ffc_flags = 
				FFC_STRM |	/* stream */
				FFC_WEOD |	/* can write EOD */

				FFC_SEEKA |	/* seek abs */
				FFC_SEEKR |	/* seek relative */
				FFC_SEEKE |	/* seek end */
				FFC_RWND |	/* can rewind */

				FFC_BINARY |	/* can do binary */
				FFC_CODED |	/* can do chars */

				FFC_RDM |	/* can do random */
				FFC_SEQ |	/* can do seq */
#if	!defined(__mips) && !defined(_LITTLE_ENDIAN)
				FFC_CANLISTIO|	/* can do listio */
#endif
				0;

		/* no data transformation */
		ffcp->ffc_flags |= locinfo.ffc_flags & FFC_NOTRN;

		if (cca_info->optflags.sds)
			ffcp->ffc_gran = BITPBLOCK;	/* 1 block */
		else
#if	defined(__mips) || defined(_LITTLE_ENDIAN)
			ffcp->ffc_gran = 8;		/* 8 bits */
#else
			ffcp->ffc_gran = 1;		/* 1 bit */
#endif
		ffcp->ffc_reclen = 0;	/* no rec length */
		ffcp->ffc_fd = llfd;
		break;

#if	!defined(__mips) && !defined(_LITTLE_ENDIAN)
	case FC_DUMPSTATS:
/*
 *		Dump the diags if they are being gathered
 */
		ret = XRCALL(llfio,fcntlrtn) llfio, FC_DUMPSTATS, arg, iostat);
                if (cca_info->optflags.diags) {
                           _cca_close_diags( fio, cca_info, TRUE, FALSE );
                           if ( _GL_cca_logptr ) fflush( _GL_cca_logptr );
                }
                break;
#endif
#if	defined(__mips) || defined(_LITTLE_ENDIAN)
	case FC_DIOINFO:
		ret = XRCALL(llfio,fcntlrtn) llfio, FC_DIOINFO, arg, iostat);
		break;
#endif
	case FC_STAT:
/*
 *		Fill in most of the fields from the lower layer.  The
 *		st_size field is copied from fsize.
 */
		ret = XRCALL(llfio,fcntlrtn) llfio, FC_STAT, arg, iostat);
		((struct stat *)arg)->st_size = BITS2BYTES(cca_info->fsize);
		break;

	case FC_ASPOLL:
                       break;

	case FC_RECALL:
		check_ffsw = (struct ffsw *)arg;
		this_tracker = cca_info->async_tracker;
		if( check_ffsw->sw_flag ) {
			if (check_ffsw->sw_stat != FFERR)
				check_ffsw->sw_stat  = FFCNT;
		}
		else {
			int found_tracker;
			int err_ret;
			err_ret = 0;
			found_tracker = FALSE;
			/*
			 * Check all trackers.  There may be more than
			 * one cache page involved to satisfy one incoming
			 * async request.
			 */
			while( this_tracker ) {                        
                            if ( this_tracker->stat == check_ffsw ) {
				if ( this_tracker->mode==CCA_TRACKER_READA ||
				     this_tracker->mode==CCA_TRACKER_WRITEA ) {
				    int ret_value;
				    this_tracker->cubuf->pending_asyncs --;
				    _cca_complete_tracker( cca_info,
					this_tracker , &ret_value, NULL, 0, 0,
					(bitptr)0, 0, NULL);
				    if (ret_value == ERR)
				    	err_ret = 1;
                                }
				found_tracker ++;
				this_tracker->mode = CCA_TRACKER_FREE;
			    }
			    this_tracker = this_tracker->next_tracker;
			}
                        check_ffsw->sw_flag  = 1;
                        if (err_ret)
                        	check_ffsw->sw_stat  = FFERR;
                        else
                        	check_ffsw->sw_stat  = FFCNT;
                        if( found_tracker == FALSE )
			    cca_info->unknown_recalls++;
		}
                break;

	case FC_SCRATCH:
		{
		int sflgs;
		ret = XRCALL(llfio,fcntlrtn) llfio, cmd, &sflgs, iostat);

		if (ret == 0 &&
		    (sflgs & SCR_UNLINKED) && (sflgs & SCR_SINGLELINK)) {

			cca_info->optflags.scr = TRUE;
			sflgs |= SCR_NOFLUSH;
		}
		*(int*)arg = sflgs;
		break;	
		}

	default:
		if (IS_RESERVED_FC(cmd)) {
			ret = XRCALL(llfio,fcntlrtn) llfio, cmd, arg, iostat);
		}
		else {
		     	ERETURN(iostat, FDC_ERR_NOSUP, 0)
		}
		break;

	}
	return(ret);
}
