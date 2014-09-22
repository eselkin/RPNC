#ifndef MIXEDNUM_H
#define MIXEDNUM_H
#include "fraction.h"

enum MIXED_NUM_ERROR { BAD_MIXED_NUM };

class MixedNum : public fraction
{
public:
    MixedNum(int whole = 0, fraction frac = fraction(0,1));
    ~MixedNum();
    MixedNum& operator=(const MixedNum& other);

    MixedNum& operator/(const MixedNum& other);
    MixedNum& operator*(const MixedNum& other);
    MixedNum& operator+(const MixedNum& other);
    MixedNum& operator-(const MixedNum& other);
    MixedNum& operator ^ (const MixedNum& other);


    friend
    ostream& operator<<(ostream& out, const MixedNum &mixed);

    friend
    istream& operator>>(istream& in, MixedNum &mixed);
private:
    void nukem();
    void copy (const MixedNum& other);

};

#endif // MIXEDNUM_H
