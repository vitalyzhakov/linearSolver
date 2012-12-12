/* 
 * File:   gaussSolver.cpp
 * Author: zhakov
 * 
 * Created on 4 Декабрь 2012 г., 23:51
 */

#include "gaussSolver.h"
#include "math.h"
#include "stdio.h"
#include "matrixHelpers.h"

gaussSolver::gaussSolver(int size) {
    mSize = size;

    pSerialPivotIter = new int[size];
    pSerialPivotPos = new int[size];
    //Заполняем -1, чтобы было понятно, что в эти строки мы ещё не заходили
    for (int i = 0; i < size; i++) {
        pSerialPivotIter[i] = -1;
    }

}

gaussSolver::gaussSolver(const gaussSolver& orig) {
}

gaussSolver::~gaussSolver() {
}

int gaussSolver::serialResultCalculation(double** pMatrix, double* pVector, double* pResult) {


    // Gaussian elimination
    serialGaussianElimination(pMatrix, pVector);
    // Back substitution
    serialBackSubstitution(pMatrix, pVector, pResult);

    return 0;
}

// Function for finding the pivot row

int gaussSolver::findPivotRow(double** pMatrix, int Iter) {
    int PivotRow = -1; // The index of the pivot row 
    double MaxValue = 0; // The value of the pivot element 
    int i; // Loop variable 

    // Choose the row, that stores the maximum element
    for (i = 0; i < mSize; i++) {
        if ((pSerialPivotIter[i] == -1) && (fabs(pMatrix[i][Iter]) > MaxValue)) {
            PivotRow = i;
            MaxValue = fabs(pMatrix[i][Iter]);
        }
    }
    return PivotRow;
}


// Column elimination

int gaussSolver::serialColumnElimination(double** pMatrix, double* pVector, int Pivot, int Iter) {
    double PivotValue, PivotFactor;
    PivotValue = pMatrix[Pivot][Iter];
    for (int i = 0; i < mSize; i++) {
        if (pSerialPivotIter[i] == -1) {
            PivotFactor = pMatrix[i][Iter] / PivotValue;
            for (int j = Iter; j < mSize; j++) {
                pMatrix[i][j] -= PivotFactor * pMatrix[Pivot][j];
            }
            pVector[i] -= PivotFactor * pVector[Pivot];
        }
    }
    
    return 0;
}


// Gaussian elimination

int gaussSolver::serialGaussianElimination(double** pMatrix, double* pVector) {
    int Iter;
    // The Number of the iteration of the gaussian
    // elimination
    int PivotRow;
    // The Number of the current pivot row
    for (Iter = 0; Iter < mSize; Iter++) {

        // Finding the pivot row
        PivotRow = findPivotRow(pMatrix, Iter);
        pSerialPivotPos[Iter] = PivotRow;
        pSerialPivotIter[PivotRow] = Iter;
        serialColumnElimination(pMatrix, pVector, PivotRow, Iter);
    }
    
    

    return 0;
}

//Обратный ход метода Гаусса

int gaussSolver::serialBackSubstitution(double** pMatrix, double* pVector, double* pResult) {
    int RowIndex, Row;
    for (int i = mSize - 1; i >= 0; i--) {
        RowIndex = pSerialPivotPos[i];
        pResult[i] = pVector[RowIndex] / pMatrix[RowIndex][i];
        for (int j = 0; j < i; j++) {
            Row = pSerialPivotPos[j];
            pVector[j] -= pMatrix[Row][i] * pResult[i];
            pMatrix[Row][i] = 0;
        }
    }

    return 0;
}