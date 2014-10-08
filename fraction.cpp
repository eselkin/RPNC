#include "fraction.h"
#include <stdint.h>
#include <cmath>
#include <iomanip>

#define int64_t long
fraction::fraction(long int64_t n, long  int64_t d)
{
    if (d == 0)
        throw DIV_BY_ZERO;
    num = n;
    denom = d;
}

fraction* fraction::convtoFrac(long double nd)
{
    fraction *new_frac = new fraction;
    long int64_t new_num=0; // just takes the whole part!
    long int64_t new_whole = nd; // integer component
    nd -= new_whole; // just the decimal component
    long long int multiplier;
    if (abs(nd) <= 1e-9)
        multiplier = 10000000000000; // use a variable, easier to manage
    else
        if (abs(nd) < 1e2)
            multiplier = 100000000;
        else if (abs(nd) < 1e4)
            multiplier = 1000000;
        else if(abs(nd) < 1e8)
            multiplier = 1000;
        else if(abs(nd) < 1e12)
            multiplier = 1e-2;
        else
            multiplier = 1e-4;
    long int64_t new_dec = nd * multiplier;
    *new_frac = reducefrac(new_dec, multiplier) + new_whole; // make a fraction from the decimal component ^12 / 10^12
    while (new_frac->denom >= 100000000)
    {
        (new_frac->num)--;
        *new_frac = reducefrac(new_frac->num, new_frac->denom);
    }
    return new_frac;
}


fraction::fraction(long double nd)
{
    fraction* new_frac;
    if ( nd != 0 )
        new_frac = convtoFrac(nd);
    num = new_frac->num;
    denom = new_frac->denom;
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
    // (4^3)^1/4 = 2.828427 when passed to int64_twill become 2
    // Giving a result of 1 when truly it is 0.805927...
    // So you can only do fractional powers that will result in whole number numerator and denominators!
    // Unless we can recursively hold fractions in the numerator and fractions in the denominator!
    // That would go on forever
    fraction *tempf;
    long double num_dbl;
    long double den_dbl;
    if (((num*denom) < 0) && (other.num % other.denom != 0))
    {
        if (other.num %2 == 0 )
        {
            num_dbl = pow( (long double)(num*1.0), (long double)(1.*other.num));
            den_dbl = pow( (long double)(denom*1.0), (long double)((1.*other.num)));
            num_dbl = pow((long double)(num_dbl), (long double)(1.0/other.denom));
            den_dbl = pow((long double)(den_dbl), (long double)(1.0/other.denom));
        }
        else
            throw IMAGINARY;
    }
    else
    {
        num_dbl = pow( (long double)(num*1.0), (long double)((1.*other.num)/(1.*other.denom)) );
        den_dbl = pow( (long double)(denom*1.0), (long double)((1.*other.num)/(1.*other.denom)) );
    }
    //DEBUG // cout << "NUM: " << num_dbl << " DEN: " << den_dbl << " PASSING: " << (long double)(num_dbl/den_dbl) << endl;
    if (num_dbl == 0)
        den_dbl = 1; // MAKE OUR FRACTION BE 0/1 Because, if the numerator is 0/-1 we'll get -0
    if (den_dbl == 0 || (num_dbl != 0 && abs((long double)(num_dbl/den_dbl)) <= 2e-8))
        throw UNDERFLO;
    if ( abs(num_dbl) >= 2.7e9 || abs((long double)(num_dbl/den_dbl)) > 2.7e9 )
        throw OVERFLO;
    tempf = convtoFrac((long double)(num_dbl/den_dbl));
    return *tempf;
}

long  int64_t GCD(long  int64_t a, long  int64_t b)
{
    return b == 0? a : GCD(b, a%b);
}

fraction& fraction::reducefrac(long  int64_t a, long  int64_t b)
{
    if (b == 0)
        throw DIV_BY_ZERO;
    long  int64_t divisor = GCD(a, b);
    if (divisor == 0)
        throw DIV_BY_ZERO;
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

bool operator >=(const fraction &f1, const fraction &f2)
{
    long double d1, d2;
    d1 = (1.0*f1.num)/(1.0*f1.denom);
    d2 = (1.0*f2.num)/(1.0*f2.denom);
    return d1 >= d2;
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
    return out;
}

istream &operator>>(istream& in, fraction &frac)
{
    string line, n, d;
    stringstream ss;
    getline(in,line);
    int64_t pos = line.find('/');
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
        if (int(line.find_first_of("0123456789")) != -1)
        {
            long double frac_num_dbl = 0;
            // whole number entered into fraction object
            ss << line;
            ss >> frac_num_dbl;
            fraction tempf = fraction(frac_num_dbl);
            frac = tempf; // assignment
        }
        else
        {
            // has no numerical value
            throw NOT_A_FRAC;
        }
    return in;
}
