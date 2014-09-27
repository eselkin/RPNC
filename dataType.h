#ifndef DATATYPE_H
#define DATATYPE_H

#include "fraction.h"
#include "mixednum.h"
#include "oppr.h"

using namespace std;

// Token data type
union DataType {
    void *vptr;
    MixedNum *mPtr;
    OpPr *opPtr; // just a good way to test precedence.
};

#endif // DATATYPE_H
