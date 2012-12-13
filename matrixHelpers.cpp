/* 
 * File:   matrixHelpers.cpp
 * Author: zhakov
 * 
 * Created on 5 Декабрь 2012 г., 22:48
 */

#include "matrixHelpers.h"
#include "stdio.h"
#include "math.h"

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

/**
 * Функция проверяет результат:
 * умножает матрицу на вектор и сравнивает с результатом
 * 
 * @param pMatrix
 * @param pVector
 * @param pResult
 * @param Size
 * @return 
 */
int matrixHelpers::testSolvingResult(double** pMatrix, double* pVector, double* pResult, int Size) {
    /* Buffer for storing the vector, that is a result of multiplication
    of the linear system matrix by the vector of unknowns */
    double* pRightPartVector;
    // Flag, that shows wheather the right parts vectors are identical or not
    int equal = 0;
    double Accuracy = 1.e-6; // Comparison accuracy
    pRightPartVector = new double [Size];
    for (int i = 0; i < Size; i++) {
        pRightPartVector[i] = 0;
        for (int j = 0; j < Size; j++) {
            pRightPartVector[i] += pMatrix[i][j] * pResult[j];
        }
    }
    for (int i = 0; i < Size; i++) {
        if (fabs(pRightPartVector[i] - pVector[i]) > Accuracy) {
            equal = 1;
        }
    }
    if (equal == 1) {
        printf("The result of the algorithm is NOT correct."
                "Check your code.\n");
    } else {
        printf("The result of the algorithm is correct.\n");
    }
    
    delete [] pRightPartVector;
    
    
    return 0;
}