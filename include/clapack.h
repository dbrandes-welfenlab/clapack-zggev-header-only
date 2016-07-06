/* header file for clapack 3.2.1 */

#ifndef __CLAPACK_H
#define __CLAPACK_H

#ifdef __cplusplus 	
extern "C" {	
#endif		

typedef int integer_fortran;
typedef double doublereal_fortran;
typedef struct { doublereal_fortran r, i; } doublecomplex_fortran;

/* Subroutine */ int zggev_(char *jobvl, char *jobvr, integer_fortran *n,
        doublecomplex_fortran *a, integer_fortran *lda, doublecomplex_fortran *b, integer_fortran *ldb,
        doublecomplex_fortran *alpha, doublecomplex_fortran *beta, doublecomplex_fortran *vl, integer_fortran
        *ldvl, doublecomplex_fortran *vr, integer_fortran *ldvr, doublecomplex_fortran *work, integer_fortran
        *lwork, doublereal_fortran *rwork, integer_fortran *info);



#ifdef __cplusplus
}
#endif


#endif /* __CLAPACK_H */
