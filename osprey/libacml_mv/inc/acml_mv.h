
/*
*  Copyright (C) 2008-2009 Advanced Micro Devices, Inc. All Rights Reserved.
*
*  This file is part of libacml_mv.
*
*  libacml_mv is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  libacml_mv is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with libacml_mv.  If not, see
*  <http://www.gnu.org/licenses/>.
*
*/



/* 
** A header file defining the C prototypes for the fast/vector libm functions
*/


#ifdef __cplusplus
extern "C" {
#endif


/*
** The scalar routines.
*/
double fastexp(double);
double fastlog(double);
double fastlog10(double);
double fastlog2(double);
double fastpow(double,double);
double fastsin(double);
double fastcos(double);
void fastsincos(double , double *, double *);

float fastexpf(float );
float fastlogf(float );
float fastlog10f(float );
float fastlog2f(float );
float fastpowf(float,float);
float fastcosf(float );
float fastsinf(float );
void fastsincosf(float, float *,float *);


/*
** The array routines.
*/
void vrda_exp(int, double *, double *);
void vrda_log(int, double *, double *);
void vrda_log10(int, double *, double *);
void vrda_log2(int, double *, double *);
void vrda_sin(int, double *, double *);
void vrda_cos(int, double *, double *);
void vrda_sincos(int, double *, double *, double *);

void vrsa_expf(int, float *, float *);
void vrsa_logf(int, float *, float *);
void vrsa_log10f(int, float *, float *);
void vrsa_log2f(int, float *, float *);
void vrsa_powf(int n, float *x, float *y, float *z);
void vrsa_powxf(int n, float *x, float y, float *z);
void vrsa_sinf(int, float *, float *);
void vrsa_cosf(int, float *, float *);
void vrsa_sincosf(int, float *, float *, float *);


#ifdef __cplusplus
}
#endif
