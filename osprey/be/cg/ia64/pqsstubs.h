/*

  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved.

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


typedef struct tn {
   TN_NUM num;
   PQS_TN_MAP_TYPE m;
} TN;

#define TN_number(x) ((x)->num)
   

typedef struct op {
   PQS_ITYPE itype;
   TN * qual, *p1,*p2;
   PQS_NODE_IDX pqs_idx;

   op() {
      itype = PQS_ITYPE_INVALID;
      qual = NULL;
      p1 = NULL;
      p2 = NULL;
      pqs_idx = PQS_IDX_INVALID ;
   }

   op(PQS_ITYPE ity, TN *q, TN * p1, TN *p2) : 
      itype(ity),qual(q),p1(p1),p2(p2) {}
} OP;
   


static PQS_NODE_IDX PQS_TN_get_last_definition(TN * t) {return t->m.last_def;}
static void PQS_TN_set_last_definition(TN *t, PQS_NODE_IDX p) {t->m.last_def = p;}
static BOOL PQS_TN_used_as_qual_pred(const TN *t){return t->m.used_as_qual_pred;};
static void PQS_TN_set_used_as_qual_pred(TN *t){t->m.used_as_qual_pred=TRUE;}
static void  PQS_TN_set_no_query(TN *t){t->m.no_query=TRUE;}
static BOOL  PQS_TN_no_query(const TN *t) {return t->m.no_query;}

static void PQS_OP_set_pqs_idx(OP *op, PQS_NODE_IDX p) {op->pqs_idx = p;}


static PQS_ITYPE 
PQS_classify_instruction (OP * inst, TN * &qual, TN * &p1, TN * &p2, PQS_NODE_FLAGS &f)
{
   qual = inst->qual;
   p1 = inst->p1;
   p2 = inst->p2;
   if (p1->num == 0) p1 = NULL;
   if (p2->num == 0) p2 = NULL;
   f = 0;
   return (inst->itype);
}



struct lt_tn {
   inline bool operator()(const PQS_TN t1, const PQS_TN t2) const {
    return TN_number(t1) < TN_number(t2);
   }
};

typedef PQS_SET<PQS_TN,lt_tn> PQS_TN_SET;
typedef PQS_SET<PQS_TN,lt_tn>::set_type PQS_TN_SET_TYPE;
