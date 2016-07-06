/* header file for clapack 3.2.1 */

#ifndef __CLAPACK_H
#define __CLAPACK_H

#include "../f2c.h"

#ifdef __cplusplus 	
extern "C" {	
#endif		

/* Subroutine */ int zggev_(char *jobvl, char *jobvr, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *alpha, doublecomplex *beta, doublecomplex *vl, integer 
	*ldvl, doublecomplex *vr, integer *ldvr, doublecomplex *work, integer 
	*lwork, doublereal *rwork, integer *info);


#ifdef __cplusplus
}
#endif


#endif /* __CLAPACK_H */
