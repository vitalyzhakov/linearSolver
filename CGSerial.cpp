/* 
 * File:   CGSerial.cpp
 * Author: zhakov
 * 
 * Created on 20 Декабрь 2012 г., 23:48
 */

#include "CGSerial.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"
#include "matrixHelpers.h"

CGSerial::CGSerial() {
}

CGSerial::CGSerial(const CGSerial& orig) {
}

CGSerial::~CGSerial() {
}

void CGSerial::resultCalculation(double** pMatrix, double* pVector, double* pResult, int Size) {
    double *CurrentApproximation, *PreviousApproximation;
    double *CurrentGradient, *PreviousGradient;
    double *CurrentDirection, *PreviousDirection;
    double *Denom, *tempPointer;
    double Step;
    int Iter = 1, MaxIter = Size + 1;
    float Accuracy = 0.00001f;
    //Allocating memory
    CurrentApproximation = new double[Size];
    PreviousApproximation = new double[Size];
    CurrentGradient = new double[Size];
    PreviousGradient = new double[Size];
    CurrentDirection = new double[Size];
    PreviousDirection = new double[Size];
    Denom = new double[Size];
    

    for (int i = 0; i < Size; i++) {
        PreviousApproximation[i] = 0;
        PreviousDirection[i] = 0;
        PreviousGradient[i] = -pVector[i];
    }
    do {
        
        if (Iter > 1) {
            tempPointer = PreviousApproximation;
            PreviousApproximation = CurrentApproximation;
            CurrentApproximation = tempPointer;
            //SwapPointers(PreviousApproximation, CurrentApproximation);
            tempPointer = PreviousGradient;
            PreviousGradient = CurrentGradient;
            CurrentGradient = tempPointer;
            //SwapPointers(PreviousGradient, CurrentGradient);
            tempPointer = PreviousDirection;
            PreviousDirection = CurrentDirection;
            CurrentDirection = tempPointer;
            //SwapPointers(PreviousDirection, CurrentDirection);
        }
        //compute gradient
//#pragma omp parallel for
        for (int i = 0; i < Size; i++) {
            CurrentGradient[i] = -pVector[i];
            for (int j = 0; j < Size; j++)
                CurrentGradient[i] += pMatrix[i][j] * PreviousApproximation[j];
        }
        //compute direction
        double IP1 = 0, IP2 = 0;
//#pragma omp parallel for reduction(+:IP1,IP2)
        for (int i = 0; i < Size; i++) {
            IP1 += CurrentGradient[i] * CurrentGradient[i];
            IP2 += PreviousGradient[i] * PreviousGradient[i];
        }
        
//#pragma omp parallel for
        for (int i = 0; i < Size; i++) {
            CurrentDirection[i] = -CurrentGradient[i] +
                    PreviousDirection[i] * IP1 / IP2;
        }
        //compute size step
        IP1 = 0;
        IP2 = 0;
//#pragma omp parallel for reduction(+:IP1,IP2)
        for (int i = 0; i < Size; i++) {
            Denom[i] = 0;
            for (int j = 0; j < Size; j++)
                Denom[i] += pMatrix[i][j] * CurrentDirection[j];
            IP1 += CurrentDirection[i] * CurrentGradient[i];
            IP2 += CurrentDirection[i] * Denom[i];
        }
        Step = -IP1 / IP2;
        
//#pragma omp parallel for
        for (int i = 0; i < Size; i++) {
            CurrentApproximation[i] = PreviousApproximation[i] + Step * CurrentDirection[i];
            
        }
        
        Iter++;
    } while
        ((diff(PreviousApproximation, CurrentApproximation, Size) > Accuracy)
            && (Iter < MaxIter));
    for (int i = 0; i < Size; i++)
        pResult[i] = CurrentApproximation[i];


    delete CurrentApproximation;
    delete PreviousApproximation;
    delete CurrentGradient;
    delete PreviousGradient;
    delete CurrentDirection;
    delete PreviousDirection;
    delete Denom;
}

double CGSerial::diff(double *vector1, double* vector2, int Size) {
    double sum = 0;
    for (int i = 0; i < Size; i++) {
        sum += fabs(vector1[i] - vector2[i]);
    }
    
    return sum;
}