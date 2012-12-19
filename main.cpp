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
#include "gaussSerial.h"
#include "matrixHelpers.h"
#include "gaussParallel.h"

//Возможные варианты алгоритмов решения
#define METHOD_TYPE_SERIAL_GAUSS 1
#define METHOD_TYPE_PARALLEL_GAUSS 2
#define METHOD_TYPE_SERIAL_CG 3
#define METHOD_TYPE_PARALLEL_CG 4

//Соответствующие константы
#define METHOD_NAME_SERIAL_GAUSS "gauss-serial" //Гаусс
#define METHOD_NAME_PARALLEL_GAUSS "gauss-parallel"
#define METHOD_NAME_SERIAL_CG "CG-serial" //Сопряжённых градиентов
#define METHOD_NAME_PARALLEL_CG "CG-parallel"


//Ошибки выполнения
#define EXECUTION_ERROR_NOT_ENOUGH_ARGUMENTS 101 //Не хватает аргументов
#define EXECUTION_ERROR_MATRIX_SIZE_NOT_DEFINED 102 //Размер матрицы не определён
#define EXECUTION_ERROR_METHOD_NOT_DEFINED 103 //Метод решения задан неверно

using namespace std;

/*
 * Точка входа: принимаем аргументы
 * @todo сделать чтение аргументов из командной строки
 */
int main(int argc, char** argv) {

    //Замер времени
    double startTime = omp_get_wtime();

    if (argc <= 4) {
        printf("Available arguments: \n\t -msize [N] - Matrix size\n");
        return EXECUTION_ERROR_NOT_ENOUGH_ARGUMENTS;
    }

    if (strcmp("-msize", argv[1])) {
        printf("Wrong syntax!!! \n");
        printf("Please, type -msize\n");
        return EXECUTION_ERROR_MATRIX_SIZE_NOT_DEFINED;
    }

    if (strcmp("-algorithm", argv[3])) {
        printf("Wrong syntax!!! \n");
        printf("Please, type -algotithm\n");
        return EXECUTION_ERROR_METHOD_NOT_DEFINED;
    }

    int solutionMethod = 0; //Код метода для вычисления
    if (!strcmp(METHOD_NAME_SERIAL_GAUSS, argv[4])) {
        solutionMethod = METHOD_TYPE_SERIAL_GAUSS;
    } else if (!strcmp(METHOD_NAME_PARALLEL_GAUSS, argv[4])) {
        solutionMethod = METHOD_TYPE_PARALLEL_GAUSS;
    } else if (!strcmp(METHOD_NAME_SERIAL_CG, argv[4])) {
        solutionMethod = METHOD_TYPE_SERIAL_CG;
    } else if (!strcmp(METHOD_NAME_PARALLEL_CG, argv[4])) {
        solutionMethod = METHOD_TYPE_PARALLEL_CG;
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

    //Генерация данных
    dataGen::dummyDataInitialization(pMatrix, pVector, mSize);
    
    //matrixHelpers::printMatrix(pMatrix, mSize);
    //matrixHelpers::printVector(pVector, mSize);

    //Идём по выбранному методу вычисления
    switch (solutionMethod) {
        case METHOD_TYPE_SERIAL_GAUSS: {
            printf("Using GAUSS SERIAL\n");
            gaussSerial* gaussSerialSolver = new gaussSerial(mSize);
            gaussSerialSolver->resultCalculation(pMatrix, pVector, pResult);
            break;
        }
        case METHOD_TYPE_PARALLEL_GAUSS: {
            printf("Using GAUSS PARALLEL\n");
            gaussParallel* gaussParallelSolver = new gaussParallel(mSize);
            gaussParallelSolver->resultCalculation(pMatrix, pVector, pResult);
            break; 
        }
        case METHOD_TYPE_SERIAL_CG: {
            printf("Using CG SERIAL\n");
            //@todo Добавить вызов метода
            break;
        }
        case METHOD_TYPE_PARALLEL_CG: {
            printf("Using CG PARALLEL\n");
            //@todo добавить вызов методаы
            break;
        }
        default: {
            //Если ни один из методов не реализован, выходим
            return EXECUTION_ERROR_METHOD_NOT_DEFINED;
            break;
        }
    }


    matrixHelpers::printVector(pResult, mSize);

    //Проверяем результат
    matrixHelpers::testSolvingResult(pMatrix, pVector, pResult, mSize);
    
    //matrixHelpers::printVector(pResult, mSize);

    //Потраченное время
    double finishTime = omp_get_wtime();

    printf("Calculation time: %f seconds\n", finishTime - startTime);

    return 0;
}