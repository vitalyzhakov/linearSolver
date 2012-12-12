/* 
 * File:   matrixHelpers.cpp
 * Author: zhakov
 * 
 * Created on 5 Декабрь 2012 г., 22:48
 */

#include "matrixHelpers.h"
#include "stdio.h"

matrixHelpers::matrixHelpers() {
}

matrixHelpers::matrixHelpers(const matrixHelpers& orig) {
}

matrixHelpers::~matrixHelpers() {
}

int matrixHelpers::printVector(double * matrix, int size) {

    for (int i = 0; i < size; i++) {
        printf("%.4f ", matrix[i]);
    }
    printf("\n");
}

int matrixHelpers::printMatrix(double **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.4f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}