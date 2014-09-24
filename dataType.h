#ifndef DATATYPE_H
#define DATATYPE_H
#include <string>
#include "fraction.h"
#include "mixednum.h"
using namespace std;


// Token data type
union DataType {
    void *vptr;
    int *iptr;
    double *dptr;
    char *cPtr;
    string *sptr; // I think irrelevant
    MixedNum *mPtr;
    fraction *frPtr;
};


#endif // DATATYPE_H
