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


       INTEGER FUNCTION ISRCHMNE(N,ARRAY,INC,TARGET,MASK,RIGHT)
       INTEGER N, INC, MASK, RIGHT, TARGET
       INTEGER ARRAY(N)

*      LOCAL VARIABLES
         INTEGER I, J

*      BEGIN
*
*     -------------
*     USM What Line
*     -------------
CDIR$ ID "@(#) libu/sci/c2/isrchmne.f	92.0	10/08/98 14:57:41"
         J = 1
         IF(INC .LT. 0) J = 1 - INC*( N-1 )
         IF( RIGHT .EQ. 0 ) THEN
           DO I = 1, N
             IF(AND(ARRAY(J),MASK) .NE. TARGET) GOTO 10
             J = J + INC
           END DO
10         ISRCHMNE = I
         ELSE
           DO I = 1, N
             IF(AND(SHIFTR(ARRAY(J),RIGHT),MASK) .NE. TARGET) GOTO 20
             J = J + INC
           END DO
20         ISRCHMNE = I
         ENDIF
       RETURN
       END
