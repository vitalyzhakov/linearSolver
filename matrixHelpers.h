/* 
 * File:   matrixHelpers.h
 * Author: zhakov
 *
 * Created on 5 Декабрь 2012 г., 22:48
 */

#ifndef MATRIXHELPERS_H
#define	MATRIXHELPERS_H

class matrixHelpers {
public:
    matrixHelpers();
    matrixHelpers(const matrixHelpers& orig);
    virtual ~matrixHelpers();
    
    static int printVector(double * matrix, int size);
    static int printMatrix(double **matrix, int size);
    static int testSolvingResult(double** pMatrix, double* pVector, double* pResult, int Size);
private:

};

#endif	/* MATRIXHELPERS_H */

