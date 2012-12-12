/* 
 * File:   dataGen.h
 * Author: zhakov
 *
 * Created on 5 Декабрь 2012 г., 19:55
 */

#ifndef DATAGEN_H
#define	DATAGEN_H

class dataGen {
public:
    dataGen();
    dataGen(const dataGen& orig);
    virtual ~dataGen();
    static int dummyDataInitialization(double** pMatrix, double* pVector, int Size);
    static int randomDataInitialization(double** pMatrix, double* pVector, int Size);
private:

};

#endif	/* DATAGEN_H */

