//
//  main.cpp
//  matrix_multiplication
//
//  Created by oscar on 26.10.2022.
//
#include "matmul.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    
    evaluate(multiply_ijk, "ijk");
    evaluate(multiply_jik, "jik");
    evaluate(multiply_kij, "kij");
    evaluate(multiply_jki, "jki");
    evaluate(multiply_kji, "kji");
    evaluate(multiply_ikj, "ikj");
    return 0;
}


