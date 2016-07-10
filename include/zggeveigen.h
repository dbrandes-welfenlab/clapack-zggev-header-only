#ifndef ZGGEVEIGEN_INLCUDE
#define ZGGEVEIGEN_INLCUDE

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <Eigen/Dense>
#pragma GCC diagnostic pop

#include "clapack.h"

/* values from zggev info return:
 *
 * copy from zggev.f:
 *
 *  = 0:  successful exit
 *  < 0:  if INFO = -i, the i-th argument had an illegal value.
 *  =1,...,N:
 *          The QZ iteration failed.  No eigenvectors have been
 *          calculated, but ALPHA(j) and BETA(j) should be
 *          correct for j=INFO+1,...,N.
 *  > N:  =N+1: other then QZ iteration failed in DHGEQZ,
 *        =N+2: error return from DTGEVC.
 *
 * and additionally:
 *
 * = -18:  A not square
 * = -19:  B not square
 * = -20:  A.rows != B.rows
 *
 *
 */

typedef std::complex<double> compdouble;

inline int solveZGGEV(const Eigen::MatrixXcd& A, const Eigen::MatrixXcd& B, Eigen::VectorXcd& eigenvals)
{
    //some ideas and naming convention taken from octave source code
    int n = A.rows();
    if (n != A.cols()) return -18;
    if (B.rows() != B.cols()) return -19;
    if (n != B.rows()) return -20;

    const char* noconst = "N";
    char no[2];
    strcpy(no,noconst);

    //lapack needs column-major and eigen stores default in column-major, so no changes should be needed.
    //storage order for complex should be the same:
    //http://stackoverflow.com/questions/5020076/passing-a-c-complex-array-to-c
    static_assert((sizeof(compdouble)) == sizeof(doublecomplex_fortran),"Size of std::complex<double> does not equal size of doublecomplex!");

    doublecomplex_fortran* Atmp = new doublecomplex_fortran[n * n];
    memcpy(Atmp,A.data(),sizeof(std::complex<double>) * n * n);

    doublecomplex_fortran* Btmp = new doublecomplex_fortran[n * n];
    memcpy(Btmp,B.data(),sizeof(std::complex<double>) * n * n);

    doublecomplex_fortran* alpha = new doublecomplex_fortran[n];
    doublecomplex_fortran* beta = new doublecomplex_fortran[n];

    doublecomplex_fortran* dummy = 0;
    int idummy = 1;

    int lwork = -1;
    doublecomplex_fortran dummywork;

    int lrwork = 8 * n;
    double* rwork = new double[lrwork];

    int info = 0;

    zggev_(no,no,&n,Atmp,&n,Btmp,&n,alpha,beta,dummy,&idummy,dummy,&idummy,&dummywork,&lwork,rwork,&info);
    if (info != 0)
    {
        delete[] Atmp;
        delete[] Btmp;
        delete[] alpha;
        delete[] beta;
        delete[] rwork;
        return info;
    }
    lwork = dummywork.r;
    doublecomplex_fortran* work = new doublecomplex_fortran[lwork];
    zggev_(no,no,&n,Atmp,&n,Btmp,&n,alpha,beta,dummy,&idummy,dummy,&idummy,work,&lwork,rwork,&info);
    if (info != 0)
    {
        delete[] Atmp;
        delete[] Btmp;
        delete[] alpha;
        delete[] beta;
        delete[] rwork;
        delete[] work;
        return info;
    }
    int cntgood = 0;
    for (int i = 0; i < n; i++)
    {
        compdouble a(alpha[i].r,alpha[i].i);
        compdouble b(beta[i].r,beta[i].i);
        bool good = std::isfinite(a.real());
        good = good && std::isfinite(a.imag());
        good = good && std::isfinite(b.real());
        good = good && std::isfinite(b.imag());
        good = good && ((b.real() != 0.0) || (b.imag() != 0.0));
        if (good) cntgood++;
    }
    eigenvals.resize(cntgood);
    cntgood = 0;
    for (int i = 0; i < n; i++)
    {
        compdouble a(alpha[i].r,alpha[i].i);
        compdouble b(beta[i].r,beta[i].i);
        bool good = std::isfinite(a.real());
        good = good && std::isfinite(a.imag());
        good = good && std::isfinite(b.real());
        good = good && std::isfinite(b.imag());
        good = good && ((b.real() != 0.0) || (b.imag() != 0.0));
        if (good) eigenvals[cntgood++] = a / b;
    }
    delete[] Atmp;
    delete[] Btmp;
    delete[] alpha;
    delete[] beta;
    delete[] rwork;
    delete[] work;
    return info;
}

#endif
