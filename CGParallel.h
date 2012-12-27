/* 
 * File:   CGParallel.h
 * Author: zhakov
 *
 * Created on 13 Декабрь 2012 г., 21:37
 */

#ifndef CGPARALLEL_H
#define	CGPARALLEL_H

class CGParallel {
public:
    CGParallel();
    CGParallel(const CGParallel& orig);
    virtual ~CGParallel();
    void resultCalculation(double** pMatrix, double* pVector, double* pResult, int Size);
    int iterationsCount;
private:
    double diff(double *vector1, double* vector2, int Size);
};

#endif	/* CGPARALLEL_H */

