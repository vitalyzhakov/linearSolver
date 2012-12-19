/* 
 * File:   gaussSerial.h
 * Author: zhakov
 *
 * Created on 4 Декабрь 2012 г., 23:51
 */

#ifndef GAUSSSERIAL_H
#define	GAUSSSERIAL_H

class gaussSerial {
public:
    gaussSerial(int size);
    gaussSerial(const gaussSerial& orig);
    virtual ~gaussSerial();

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

#endif	/* GAUSSSERIAL_H */

