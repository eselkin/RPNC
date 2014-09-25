#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

enum FRAC_ERROR { DIV_BY_ZERO, NOT_A_FRAC };

class fraction
{
public:
    fraction(int n = 0, int d = 1);
    fraction(double nd);
    ~fraction();
    fraction(const fraction& other);
    fraction& operator=(const fraction& other);
    fraction& operator/(const fraction& other);
    fraction& operator*(const fraction& other);
    fraction& operator+(const fraction& other);
    fraction& operator-(const fraction& other);
    fraction& operator^(const fraction& other);
    // If we take a fraction and raise it to a fraction, even if it's a whole... it'll be interpreted as this
    fraction& reducefrac( int a, int b );

    friend
    ostream& operator<<(ostream& out, const fraction &frac);

    friend
    istream& operator>>(istream& in, fraction &frac);

    friend
    int GCD (int a, int b);

    //protected:
    int num, denom;
private:
    void nukem();
    void copy(const fraction& other);
};

#endif // FRACTION_H
