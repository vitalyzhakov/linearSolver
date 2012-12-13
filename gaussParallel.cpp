/* 
 * File:   gaussParallel.cpp
 * Author: zhakov
 * 
 * Created on 10 Декабрь 2012 г., 23:23
 */

#include "gaussParallel.h"
#include "omp.h"
#include "math.h"
#include "types.h"
#include "stdio.h"
#include "matrixHelpers.h"

gaussParallel::gaussParallel(int size) {
    mSize = size;

    pSerialPivotIter = new int[size];
    pSerialPivotPos = new int[size];
    //Заполняем -1, чтобы было понятно, что в эти строки мы ещё не заходили
    for (int i = 0; i < size; i++) {
        pSerialPivotIter[i] = -1;
    }
}

gaussParallel::gaussParallel(const gaussParallel& orig) {
}

gaussParallel::~gaussParallel() {
}

int gaussParallel::resultCalculation(double** pMatrix, double* pVector, double* pResult) {


    // Gaussian elimination
    gaussianElimination(pMatrix, pVector);
    // Back substitution
    backSubstitution(pMatrix, pVector, pResult);

    return 0;
}

// Function for finding the pivot row
int gaussParallel::findPivotRow(double** pMatrix, int Iter) {
    int PivotRow = -1; // The index of the pivot row 
    double MaxValue = 0; // The value of the pivot element 
    int i; // Loop variable 

    // Choose the row, that stores the maximum element
#pragma omp parallel
    {
        TThreadPivotRow ThreadPivotRow;
        ThreadPivotRow.MaxValue = 0;
        ThreadPivotRow.PivotRow = -1;

#pragma omp for
        for (i = 0; i < mSize; i++) {
            if ((pSerialPivotIter[i] == -1) && (fabs(pMatrix[i][Iter]) > ThreadPivotRow.MaxValue)) {
                ThreadPivotRow.PivotRow = i;
                ThreadPivotRow.MaxValue = fabs(pMatrix[i][Iter]);
            }
        }
#pragma omp critical
        {
            if (ThreadPivotRow.MaxValue > MaxValue) {
                MaxValue = ThreadPivotRow.MaxValue;
                PivotRow = ThreadPivotRow.PivotRow;
            }
        } // pragma omp critical
    }// pragma omp parallel

    return PivotRow;
}


// Column elimination

int gaussParallel::columnElimination(double** pMatrix, double* pVector, int Pivot, int Iter) {
    double PivotValue, PivotFactor;
    PivotValue = pMatrix[Pivot][Iter];
#pragma omp parallel for private (PivotFactor) schedule(dynamic,1)
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

int gaussParallel::gaussianElimination(double** pMatrix, double* pVector) {
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
        columnElimination(pMatrix, pVector, PivotRow, Iter);
    }



    return 0;
}

/* Обратный ход метода Гаусса
 */
int gaussParallel::backSubstitution(double** pMatrix, double* pVector, double* pResult) {
    int RowIndex, Row;
    for (int i = mSize - 1; i >= 0; i--) {
        RowIndex = pSerialPivotPos[i];
        pResult[i] = pVector[RowIndex] / pMatrix[RowIndex][i];
//#pragma omp parallel for private (Row)
        for (int j = 0; j < i; j++) {
            Row = pSerialPivotPos[j];
            pVector[j] -= pMatrix[Row][i] * pResult[i];
            pMatrix[Row][i] = 0;
        }
    }

    return 0;
}