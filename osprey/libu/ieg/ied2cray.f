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


      INTEGER FUNCTION
     +IED2CRAY@(TYPE, NUM, FORN, BITOFF, CRAY, STRIDE, CRAYCH)

C     The IED2CRAY@ function converts from a generic 32-bit platform with IEEE 
C     floating-point representation to CRAY Fortran data types.  The REAL and 
C     DOUBLE PRECISION data representations are both 64 bits.   This function 
C     is a close variant of IEG2CRAY.
C
C     The returned function value is as follows:
C
C         <0  Parameter error; no translation performed
C          0  Translation complete; no errors
C         >0  Translation complete; return value is the number of
C             values that completely overflowed or completely under-
C             flowed.

      IMPLICIT NONE

      INTEGER TYPE
      INTEGER NUM
      INTEGER FORN(0:0)
      INTEGER BITOFF
      INTEGER CRAY(0:0)
      INTEGER STRIDE
      CHARACTER * (*) CRAYCH(0:0)

      INTEGER DTREAL
      PARAMETER (DTREAL       = 2)
      INTEGER DTSPECREAL
      PARAMETER (DTSPECREAL   = 8)

      INTEGER IEG2CRAY
      EXTERNAL IEG2CRAY
      INTEGER INC
      INTEGER NTYPE

      IF (NUMARG() .EQ. 5) THEN
        INC = 1
      ELSE IF (NUMARG() .GE. 6) THEN
        INC = STRIDE
      ELSE
        GOTO 9000 
      ENDIF

      NTYPE = TYPE
      IF (TYPE.EQ.DTREAL) NTYPE = DTSPECREAL

      IED2CRAY@ = IEG2CRAY(NTYPE, NUM, FORN, BITOFF, CRAY, INC, CRAYCH)
      RETURN

 9000 CONTINUE
      IED2CRAY@ = -1                !  Some parameter error
      RETURN
CDIR$ ID "@(#) libu/ieg/ied2cray.f	92.0	10/08/98 14:57:41"
      END
