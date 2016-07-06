# README

This is a header only C++-11 port of the zggev function from LAPLACK, based on CLAPACK (http://www.netlib.org/clapack/) with a wrapper for eigen (http://eigen.tuxfamily.org/index.php?title=Main_Page) matrices. To use it, see main.cpp in example folder. To compile the example go to example folder and compile with

```bash
g++ -o main -std=c++11 -I/usr/include/eigen3 main.cpp 
```
