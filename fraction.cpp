#include "fraction.h"
#include <stdint.h>
#include <cmath>

#define int64_t long
fraction::fraction(long int64_t n, long  int64_t d)
{
    if (d == 0)
        throw DIV_BY_ZERO;
    num = n;
    denom = d;
}

fraction::fraction(long double nd)
{
    cout << "DOUBLE COMING IN: " << nd;
    fraction new_frac;
    if ( nd != 0 )
    {
        long int64_t new_num=0; // just takes the whole part!
        long int64_t multiplier;
        long int64_t new_whole = nd; // integer component
        nd -= new_whole; // just the decimal component
        multiplier = 1000000000000;
        cout << "new whole: "<< new_whole;
        long int64_t new_dec = nd * multiplier; // whole component of decimal ^ 12th power
        cout << " new_dec: " << new_dec << endl;
        new_frac = reducefrac(new_dec, multiplier); // make a fraction from the decimal component ^12 / 10^12
        cout << "new frac: " << new_frac << endl;
        new_frac = new_frac + new_whole; // makes a fraction from new_whole;
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
    // (4^3)^1/4 = 2.828427 when passed to int64_twill become 2
    // Giving a result of 1 when truly it is 0.805927...
    // So you can only do fractional powers that will result in whole number numerator and denominators!
    // Unless we can recursively hold fractions in the numerator and fractions in the denominator!
    // That would go on forever
    cout << "NUM: " << num << " DEN: " << denom << "and O NUM: " << other.num << "O DEN: "<<other.denom << endl;
    fraction* tempf;
    if (((num*denom) <= 0) && (other.num % other.denom != 0))
        throw IMAGINARY;
    long double num_dbl = pow( num*1.0, (long double)((other.num)/(other.denom))) ;
    long double den_dbl = pow( denom*1.0, (long double)((other.num)/(other.denom)));
    tempf = new fraction(num_dbl, den_dbl);
    //*tempf = reducefrac(tempf->num, tempf->denom);

    cout << "TEMPFN: "<< tempf->num << " TEMPFD: "<< tempf->denom << endl;
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
