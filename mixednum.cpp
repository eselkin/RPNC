#include "mixednum.h"
#include <cstdlib>

MixedNum::MixedNum(int whole, fraction frac)
    : fraction(frac.num+whole*frac.denom, frac.denom)
{
    // We are storing as a fraction, input/output will be the only thing to change
}

MixedNum MixedNum::operator/(const MixedNum &other)
{
    return MixedNum(0, fraction(num,denom)/fraction(other.num,other.denom));
}

MixedNum MixedNum::operator*(const MixedNum &other)
{
    return MixedNum(0, fraction(num,denom)*fraction(other.num,other.denom));
}

MixedNum MixedNum::operator+(const MixedNum &other)
{
    return MixedNum(0, fraction(num,denom)+fraction(other.num,other.denom));
}

MixedNum MixedNum::operator-(const MixedNum &other)
{
    return MixedNum(0, fraction(num,denom)-fraction(other.num,other.denom));
}


ostream &operator<<(ostream &out, const MixedNum &mixed)
{
    char sign = ' '; // spaces don't really matter
    if (mixed.num*1.0/mixed.denom*1.0 < 0)
        sign = '-';
    int whole = abs(mixed.num/mixed.denom);
    int numer = abs(mixed.num % mixed.denom);
    int denom = abs(mixed.denom);
    if (numer == 0)
        out << sign << whole;
    else
        if (whole == 0)
            out << sign << numer << "/" << denom;
        else
            out << sign << whole << " " << numer << "/" << denom;
    return out;
}

istream &operator>>(istream &in, MixedNum &mixed)
{
    // throw error for div by 0
    fraction frac;     // defaults to 0/1
    string line;
    int whole  = 0;    // default to 0
    stringstream ss;
    getline(in, line); // either w n/d or w or " " or "" or " n/d"
    int space_pos = line.find_first_of(' ');
    if (space_pos == -1)
    {
        // No space in line
        // We either only have a fraction, or we only have a whole number component, or a bad mixed number
        ss << line;
        if ( line.find('/') != -1 )
            ss >> frac; // We only have a fraction
        else
            if ( line.find_first_of("0123456789") != -1)
                ss >> whole;
            else
                throw BAD_MIXED_NUM; // We only have a BAD number or something else
        frac = whole < 0? fraction(whole, 1)-frac: frac = fraction(whole, 1)+frac; // This reduces the frac value on add/sub
        mixed.num = frac.num;
        mixed.denom = frac.denom;
        return in;
    }
    // We have a space in the line
    ss.str("");
    ss.clear();
    ss << line.substr(0, space_pos); // find first not space
    if (ss.str() == "" || ss.str() == " ")
    {
        ss.str("");
        ss.clear();
        line.erase(0, line.find_first_not_of(" "));
    }
    space_pos = line.find_first_of(' ');
    if ( space_pos == -1 )
    {
        ss << line;
        ss >> mixed; // recursive call to this function if no space!!!
        return in;
    }
    ss.str("");
    ss.clear();
    ss << line.substr(0,space_pos); // space_pos was correct position in the line
    if ( ss.str().find_first_of("0123456789") != -1 )
        ss >> whole;  // In this spot there's a number
    else
        throw BAD_MIXED_NUM; // Couldn't find a whole number or fraction
    ss.clear();
    ss.str("");
    ss << line.substr(space_pos+1, string::npos);
    if (ss.str() == "" || ss.str() == " " ) // If after the first space, there is only space, make our fraction 0/1
            frac = fraction(0,1);
        else if (ss.str().find('/') != -1)
            ss >> frac;
        else
        throw BAD_MIXED_NUM;
    frac = whole < 0? fraction(whole, 1)-frac: frac = fraction(whole, 1)+frac; // This reduces the frac value on add/sub
    mixed.num = frac.num;
    mixed.denom = frac.denom;
    return in;
}
