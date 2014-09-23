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
    char *cPtr; // why?? For the operator stack it will only contain characters... so not here
    string *sptr; // also irrelevant!
    fraction *frPtr;
    MixedNum *mPtr;
};


#endif // DATATYPE_H
