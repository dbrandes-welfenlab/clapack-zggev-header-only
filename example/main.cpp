#include "../include/zggeveigen.h"

#include <tuple>
#include <iostream>

int main(int argc, char*argv[])
{
    std::ignore = argc;
    std::ignore = argv;
    Eigen::MatrixXcd AMat;
    Eigen::MatrixXcd BMat;
    Eigen::VectorXcd eigenvals;

    AMat.resize(4,4);
    AMat.setZero();
    AMat(0,0) = compdouble(0,1);
    AMat(1,1) = compdouble(2,0);
    AMat(2,2) = compdouble(3,3);
    AMat(3,3) = compdouble(4,-5);

    BMat.resize(4,4);
    BMat.setZero();
    for (int i = 0; i < 4; i++) BMat(i,i) = compdouble(1.0,0.0);

    int info = solveZGGEV(AMat,BMat,eigenvals);
    assert(info == 0);
    std::cout << "num good eigenvals: " << eigenvals.rows() << std::endl;
    for (int i = 0; i < int(eigenvals.rows());i++)
    {
        std::cout << eigenvals[i] << std::endl;
    }
    return 0;
}

#include "../include/fullcinclude.h"
