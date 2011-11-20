C
C
C  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.
C
C  This program is free software; you can redistribute it and/or modify it
C  under the terms of version 2.1 of the GNU Lesser General Public License 
C  as published by the Free Software Foundation.
C
C  This program is distributed in the hope that it would be useful, but
C  WITHOUT ANY WARRANTY; without even the implied warranty of
C  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
C
C  Further, this software is distributed without any warranty that it is
C  free of the rightful claim of any third person regarding infringement 
C  or the like.  Any license provided herein, whether implied or 
C  otherwise, applies only to this software file.  Patent licenses, if
C  any, provided herein do not apply to combinations of this program with 
C  other software, or any other product whatsoever.  
C
C  You should have received a copy of the GNU Lesser General Public 
C  License along with this program; if not, write the Free Software 
C  Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, 
C  USA.
C
C  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
C  Mountain View, CA 94043, or:
C
C  http://www.sgi.com
C
C  For further information regarding this notice, see:
C
C  http://oss.sgi.com/projects/GenInfo/NoticeExplan
C
C


      INTEGER FUNCTION TMADW(TABNUM, TABENT)
      IMPLICIT INTEGER (A-Z)
C
CDIR$ ID "@(#) libu/tblmgr/tmadw.f	92.0	10/08/98 14:57:41"
C
C     TMADW   Add a word to a table
C
C     Call:   INDEX = TMADW(TABNUM, TABENT)
C
C     Entry:  TABNUM contains the table number.
C             TABENT contains the actual entry for the table.
C
C     Exit:   INDEX contains the zero-based index of the word in the table.

      INCLUDE 'tblmgr.fh'

      POINTER (PTR, TABLE(0:0))

C     Validate number of arguments, NTAB, and TABNUM.

      IF (NUMARG() .NE. 2) THEN
        CALL TMERR('TMADW', FETBARGS)
      ENDIF

      IF ((NTAB .LT. 1) .OR. (NTAB .GT. 64)) THEN
        CALL TMERR('TMADW', FETBNTAB)
      ENDIF

      IF ((TABNUM .LT. 1) .OR. (TABNUM .GT. NTAB)) THEN
        CALL TMERR('TMADW', FETBTNUM)
      ENDIF

C     Set INDEX and increase the table length by one.

      INDEX = LTAB(TABNUM)
      LTAB(TABNUM) = LTAB(TABNUM) + 1

C     See if the increment can be satisfied from the pad area, or if
C     we need the heap manager's help.

      ACTPAD = ALEN(TABNUM) - LTAB(TABNUM)

      IF ((ACTPAD .GT. PAD(TABNUM)) .OR. (ACTPAD .LT. 0)) THEN
        CALL TMPTC
      ENDIF

C     Put TABENT into the table.

      PTR = BTAB(TABNUM)
      TABLE(INDEX) = TABENT

C     Set return value.

      TMADW = INDEX

      RETURN
      END
