//
//  matmul.hpp
//  matrix_multiplication
//
//  Created by oscar on 26.10.2022.
//

#ifndef matmul_hpp
#define matmul_hpp

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
void evaluate(void (*f)(float **mat1,
                        float **mat2,
                        float **res,
                        int N),
              const char *name);
void multiply_ijk(float **mat1,
              float **mat2,
              float **res,
              int N);
void multiply_jik(float **mat1,
              float **mat2,
              float **res,
              int N);
void multiply_kij(float **mat1,
              float **mat2,
              float **res,
              int N);
void multiply_jki(float **mat1,
              float **mat2,
              float **res,
              int N);
void multiply_kji(float **mat1,
              float **mat2,
              float **res,
              int N);
void multiply_ikj(float **mat1,
              float **mat2,
              float **res,
              int N);
#endif /* matmul_hpp */
