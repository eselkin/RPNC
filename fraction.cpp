#include "fraction.h"
#include <cmath>

using namespace std;

fraction::fraction(int n, int d)
{
    num = n;
    denom = d;
}

fraction::fraction(double nd)
{
    fraction new_frac;
    if (nd !=0)
    {
        long long int new_num=0; // just takes the whole part!
        int i = 0;

        while (abs(new_num) < 270000000)
            new_num = nd * 100 * i++; // Keep it under the max limit for an int
        long long int new_denom = --i*100;
        new_frac = reducefrac(new_num, new_denom); // reduce should bring down the size but retain the relationship n/d
    }
    num = new_frac.num;
    denom = new_frac.denom;
}

fraction::~fraction()
{
    // Nothing, because we're making copies... not pointers
}

fraction::fraction(const fraction &other)
{
    copy(other);
}

fraction& fraction::operator=(const fraction &other)
{
    if (this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

fraction& fraction::operator/(const fraction &other)
{
    return reducefrac(num * other.denom, denom * other.num);
}

fraction& fraction::operator*(const fraction &other)
{
    return reducefrac(num*other.num, denom*other.denom);
}

fraction& fraction::operator+(const fraction &other)
{
    return reducefrac(num*other.denom + denom*other.num, denom*other.denom);
}

fraction& fraction::operator-(const fraction &other)
{
    return reducefrac(num*other.denom - denom*other.num, denom*other.denom);
}

fraction& fraction::operator^(const fraction &other)
{
    // (3^3)^1/4 = 2.279507 when passed will become 2
    // (4^3)^1/4 = 2.828427 when passed to int will become 2
    // Giving a result of 1 when truly it is 0.805927...
    // So you can only do fractional powers that will result in whole number numerator and denominators!
    // Unless we can recursively hold fractions in the numerator and fractions in the denominator!
    // That would go on forever
    double num_dbl = pow( pow(num*1.0,other.num),   (1.0/(1.0*other.denom)));
    double den_dbl = pow( pow(denom*1.0,other.num), (1.0/(1.0*other.denom)));
    double new_dbl = (1.0*num_dbl) / (1.0*den_dbl);    
    fraction* tempf = new fraction(new_dbl);
    return *tempf;
}

int GCD(int a, int b)
{
    return b == 0? a : GCD(b, a%b);
}

fraction& fraction::reducefrac(int a, int b)
{
    int divisor = GCD(a, b);
    //    fraction tempfrac(a/divisor, b/divisor);
    //    return tempfrac;
    fraction *tempfrac = new fraction(a/divisor, b/divisor);
    return *tempfrac;
}


void fraction::nukem()
{
    // nothing really;
}

void fraction::copy(const fraction &other)
{
    num = other.num;
    denom = other.denom; // straight copy, since they are simple types
}

ostream &operator<<(ostream &out, const fraction &frac)
{
    // should reduce here... so when outputted as part of RPN
    if ( frac.num == 0 )
        out << 0;
    else
        if( frac.denom == 0 )
            throw DIV_BY_ZERO;
        else out << frac.num << '/' << frac.denom;
}

istream &operator>>(istream& in, fraction &frac)
{
    string line, n, d;
    stringstream ss;
    getline(in,line);
    int pos = line.find('/');
    if (pos != -1)
    {
        n = line.substr(0,pos);
        d = line.substr(pos+1, string::npos);
        ss << n;
        ss >> frac.num;
        ss.clear();
        ss.str("");
        ss << d;
        ss >> frac.denom;
    }
    else
        if (line.find_first_of("0123456789") != -1){
            double frac_num_dbl = 0;
            // whole number entered into fraction object
            ss << line;
            ss >> frac_num_dbl;
            fraction tempf = fraction(frac_num_dbl);
            frac = tempf; // assignment
        } else {
            // has no numerical value
            throw NOT_A_FRAC;
        }
    return in;
}

