//
//  matmul.cpp
//  matrix_multiplication
//
//  Created by oscar on 26.10.2022.
//

#include "matmul.hpp"
using namespace std;
void evaluate(void (*f)(float **mat1,
                        float **mat2,
                        float **res,
                        int N),
              const char *name){
    cout << name << '\n';
    int sizes[6] = {500, 512, 1000, 1024, 2000, 2048};
    const int LENGTH = 6;
    
    for (int j = 0; j < LENGTH; j++) {
        int N = sizes[j];
        float** res = new float*[N]; // To store result
        float** mat1 = new float*[N];
        float** mat2 = new float*[N];

        for (int i = 0; i < N; i ++){
            mat1[i] = new float[N];
            mat2[i] = new float[N];
            res[i] = new float[N];
        };

        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                mat1[i][j] = rand() % 100;
                mat2[i][j] = rand() % 100;
                res[i][j] = 0;
            };
        };
        
        clock_t begin = clock();
        f(mat1, mat2, res, N);
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout << "Time to multiply matrix with(" << N << "x" << N << ")=" << elapsed_secs << " seconds \n";
        delete[] res;
        delete[] mat1;
        delete[] mat2;
    }
}

void multiply_ijk(float **mat1,
              float **mat2,
              float **res,
              int N)
{
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

void multiply_jik(float **mat1,
              float **mat2,
              float **res,
              int N)
{
    int i, j, k;
    for (j = 0; j < N; j++) {
        for (i = 0; i < N; i++) {
            for (k = 0; k < N; k++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

void multiply_kij(float **mat1,
              float **mat2,
              float **res,
              int N)
{
    int i, j, k;
    for (k = 0; k < N; k++) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

void multiply_jki(float **mat1,
              float **mat2,
              float **res,
              int N)
{
    int i, j, k;
    for (j = 0; j < N; j++) {
        for (k = 0; k < N; k++) {
            for (i = 0; i < N; i++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

void multiply_kji(float **mat1,
              float **mat2,
              float **res,
              int N)
{
    int i, j, k;
    for (k = 0; k < N; k++) {
        for (j = 0; j < N; j++) {
            for (i = 0; i < N; i++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

void multiply_ikj(float **mat1,
              float **mat2,
              float **res,
              int N)
{
    int i, j, k;
    for (k = 0; k < N; k++)
    {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}
