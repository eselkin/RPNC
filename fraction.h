#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

enum FRAC_ERROR { DIV_BY_ZERO, NOT_A_FRAC, IMAGINARY, UNDERFLO };

class fraction
{
public:
    fraction(long long int n = 0, long long int d = 1);
    fraction(long double nd);
    ~fraction();
    fraction(const fraction& other);

    fraction& operator=(const fraction& other);
    fraction& operator/(const fraction& other);
    fraction& operator*(const fraction& other);
    fraction& operator+(const fraction& other);
    fraction& operator-(const fraction& other);
    fraction& operator^(const fraction& other);
    // If we take a fraction and raise it to a fraction, even if it's a whole... it'll be interpreted as this
    fraction& reducefrac( long long int a, long long int b );
    fraction* convtoFrac(long double nd);

    friend
    ostream& operator<<(ostream& out, const fraction &frac);

    friend
    istream& operator>>(istream& in, fraction &frac);

    friend
    long long int GCD (long long int a, long long int b);

    //protected:
    long long int num, denom;
private:
    void nukem();
    void copy(const fraction& other);
};
#endif // FRACTION_H
