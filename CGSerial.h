/* 
 * File:   CGSerial.h
 * Author: zhakov
 *
 * Created on 20 Декабрь 2012 г., 23:48
 */

#ifndef CGSERIAL_H
#define	CGSERIAL_H

class CGSerial {
public:
    CGSerial();
    CGSerial(const CGSerial& orig);
    virtual ~CGSerial();
    void resultCalculation(double** pMatrix, double* pVector, double* pResult, int Size);
    int iterationsCount;
private:
    double diff(double *vector1, double* vector2, int Size);

};

#endif	/* CGSERIAL_H */

