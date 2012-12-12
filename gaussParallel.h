/* 
 * File:   gaussParallel.h
 * Author: zhakov
 *
 * Created on 10 Декабрь 2012 г., 23:23
 */

#ifndef GAUSSPARALLEL_H
#define	GAUSSPARALLEL_H

class gaussParallel {
public:
    gaussParallel(int size);
    gaussParallel(const gaussParallel& orig);
    virtual ~gaussParallel();
    
    int resultCalculation(double** pMatrix, double* pVector, double* pResult);
private:
    int mSize;
    int* pSerialPivotPos; // The number of pivot rows selected at the iterations
    int* pSerialPivotIter; // The iterations, at which the rows were pivots
    
    int findPivotRow(double** pMatrix, int Iter);
    int serialGaussianElimination(double** pMatrix, double* pVector);
    int serialBackSubstitution(double** pMatrix, double* pVector, double* pResult);
    int serialColumnElimination(double** pMatrix, double* pVector, int Pivot, int Iter);
};

#endif	/* GAUSSPARALLEL_H */

