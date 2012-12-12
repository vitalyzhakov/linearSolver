/* 
 * File:   main.cpp
 * Author: zhakov
 *
 * Created on 1 Декабрь 2012 г., 23:35
 */
#include <omp.h>
#include <cstdlib>
#include "stdio.h"
#include "string.h"
#include "dataGen.h"
#include "gaussSolver.h"
#include "matrixHelpers.h"


using namespace std;

/*
 * Точка входа: принимаем аргументы
 * @todo сделать чтение аргументов из командной строки
 */
int main(int argc, char** argv) {
    
    //Замер времени
    double startTime = omp_get_wtime();

    if (argc <= 1) {
        printf("Available arguments: \n\t -msize [N] - Matrix size\n");
        return 0;
    }

    if (!strcmp("-msize", argv[1])) {
        printf("Wrong syntax!!! \n");
        printf("Please, type --help for additional information\n");
        return 0;
    }

    //Первые проверки прошли, пытаемся считать аргумент-размерность
    //Размер матрицы
    int mSize;
    mSize = atoi(argv[2]);


    printf("Matrix size is %d\n", mSize);



    double **pMatrix; //Матрица коэффициентов (двумерная)
    double *pVector; //Правая часть линейной системы
    double *pResult; //Результирующий вектор

    //Инициализация массивов для адекватной работы с памятью (N+1 элементов)
    pVector = new double [mSize];
    pResult = new double [mSize];
    pMatrix = new double *[mSize];
    for (int i = 0; i < mSize; i++) {
        pMatrix[i] = new double [mSize];
    }

    dataGen::dummyDataInitialization(pMatrix, pVector, mSize);
    
    gaussSolver* solver = new gaussSolver(mSize);
    solver->serialResultCalculation(pMatrix, pVector, pResult);
    
    //Потраченное время
    double finishTime = omp_get_wtime();
    
    printf("Calculation time: %f seconds\n", finishTime - startTime);

    return 0;
}