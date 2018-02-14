#include "fraction.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>

typedef unsigned int uint;

// the greatest common divisor
int gcd(int a, int b) {
    if(abs(a) < abs(b))
        return gcd(abs(b), abs(a));
    if(a % b == 0)
        return b;
    else
        return gcd(abs(a % b), abs(b));
}

void fraction::to_canonical()
{
    if(_numerator == 0) {
        _denominator = 1;
        return;
    }
    if(_denominator == 0)
        throw ZeroDivision();
    else if(_denominator < 0) {
        _numerator = -_numerator;
        _denominator = -_denominator;
    }
    int gcdiv = gcd(abs(_numerator), _denominator);
    _denominator /= gcdiv;
    _numerator /= gcdiv;
}

fraction::fraction(int numerator, int denominator)
{
    if(denominator == 0)
        throw ZeroDivision();
    _numerator = numerator;
    _denominator = denominator;
    to_canonical();
}

fraction::fraction(const fraction &f)
{
    _numerator = f._numerator;
    _denominator = f._denominator;
}

fraction fraction::from_string(const std::string& s)
{
    std::istringstream str(s);
    fraction f;
    str >> f;
    return f;
}

////////////////////////////////////////////////////
///
fraction&fraction::operator =(const fraction& f)
{
    _numerator = f._numerator;
    _denominator = f._denominator;
    return *this;
}

fraction&fraction::operator =(const std::pair<int, int>& pair)
{
    if(pair.second == 0)
        throw ZeroDivision();
    _numerator = pair.first;
    _denominator = pair.second;
    to_canonical();
    return *this;
}

fraction&fraction::operator =(const char* str)
{
    int num, denom;
    sscanf(str, "%d/%d", &num, &denom);
    if(denom == 0)
        throw ZeroDivision();

    _numerator = num;
    _denominator = denom;

    to_canonical();
    return *this;
}

fraction&fraction::operator =(const int& decimal)
{
    _numerator = decimal;
    _denominator = 1;
    return *this;
}

/////////////////////////////////////////////////////////

fraction&fraction::operator +=(const fraction& f)
{
    _numerator = _numerator * f._denominator + _denominator * f._numerator;
    _denominator *= f._denominator;
    to_canonical();
    return *this;
}

fraction&fraction::operator -=(const fraction& f)
{
    _numerator = _numerator * f._denominator - _denominator * f._numerator;
    _denominator *= f._denominator;
    to_canonical();
    return *this;

}

fraction&fraction::operator *=(const fraction& f)
{
    _numerator *= f._numerator;
    _denominator *= f._denominator;
    to_canonical();
    return *this;
}

fraction&fraction::operator /=(const fraction& f)
{
    if(f._numerator == 0)
        throw ZeroDivision();
    _numerator *= f._denominator;
    _denominator *= f._numerator;
    to_canonical();
    return *this;
}

fraction& fraction::operator +=(const int& decimal)
{
    _numerator += decimal * _denominator;
    return *this;
}

fraction& fraction::operator -=(const int& decimal)
{
    _numerator -= decimal * _denominator;
    return *this;
}

fraction& fraction::operator *=(const int& decimal)
{
    _numerator *= decimal;
    to_canonical();
    return *this;
}

fraction& fraction::operator /=(const int& decimal)
{
    if(decimal == 0)
        throw ZeroDivision();
    _denominator *= decimal;
    to_canonical();
    return *this;
}

///////////////////////////////////////////////////

fraction fraction::operator +(const fraction& f)
{
    fraction temp = *this;
    temp += f;
    return temp;
}

fraction fraction::operator -(const fraction& f)
{
    fraction temp = *this;
    temp -= f;
    return temp;

}

fraction fraction::operator *(const fraction& f)
{
    fraction temp = *this;
    temp *= f;
    return temp;

}

fraction fraction::operator /(const fraction& f)
{
    fraction temp = *this;
    temp /= f;
    return temp;
}

fraction fraction::operator +(const int& decimal)
{
    fraction temp = *this;
    temp += decimal;
    return temp;
}

fraction fraction::operator -(const int& decimal)
{
    fraction temp = *this;
    temp -= decimal;
    return temp;
}

fraction fraction::operator *(const int& decimal)
{
    fraction temp = *this;
    temp *= decimal;
    return temp;
}

fraction fraction::operator /(const int& decimal)
{
    fraction temp = *this;
    temp /= decimal;
    return temp;
}

///////////////////////////////////////////////////////

fraction fraction::operator !()
{
    if(_numerator == 0)
        throw ZeroDivision();
    fraction temp = *this;
    std::swap(temp._numerator, temp._denominator);
    temp.to_canonical();
    return temp;
}

fraction fraction::operator -()
{
    fraction temp = *this;
    temp._numerator = -temp._numerator;
    return temp;
}

//////////////////////////////////////////////////////

bool fraction::operator ==(const fraction& f) const
{
    return (*this).to_d() == (f).to_d();
}

bool fraction::operator !=(const fraction& f) const
{
    return (*this).to_d() != (f).to_d();
}

bool fraction::operator <=(const fraction& f) const
{
    return (*this).to_d() <= (f).to_d();
}

bool fraction::operator >=(const fraction& f) const
{
    return (*this).to_d() >= (f).to_d();
}

bool fraction::operator <(const fraction& f) const
{
    return (*this).to_d() < (f).to_d();
}

bool fraction::operator >(const fraction& f) const
{
    return (*this).to_d() > (f).to_d();
}

bool fraction::operator ==(const int& decimal) const
{
    return (*this).to_d() == decimal;
}

bool fraction::operator !=(const int& decimal) const
{
    return (*this).to_d() != decimal;
}

bool fraction::operator <=(const int& decimal) const
{
    return (*this).to_d() <= decimal;
}

bool fraction::operator >=(const int& decimal) const
{
    return (*this).to_d() >= decimal;
}

bool fraction::operator <(const int& decimal) const
{
    return (*this).to_d() < decimal;
}

bool fraction::operator >(const int& decimal) const
{
    return (*this).to_d() > decimal;
}

//////////////////////////////////////////////////////////////////
//  OUTER OPS //

fraction operator +(const int& decimal, const fraction& f)
{
    fraction temp = decimal;
    temp += f;
    return temp;
}

fraction operator -(const int& decimal, const fraction& f)
{
    fraction temp = decimal;
    temp -= f;
    return temp;
}

fraction operator *(const int& decimal, const fraction& f)
{
    fraction temp = decimal;
    temp *= f;
    return temp;
}

fraction operator /(const int& decimal, const fraction& f)
{
    fraction temp = decimal;
    temp /= f;
    return temp;
}


fraction operator +=(int& decimal, const fraction& f)
{
    return int(decimal + f.to_d());
}

fraction operator -=(int& decimal, const fraction& f)
{
    return int(decimal - f.to_d());
}

fraction operator *=(int& decimal, const fraction& f)
{
    return int(decimal * f.to_d());
}

fraction operator /=(int& decimal, const fraction& f)
{
    if (f._numerator == 0)
        throw ZeroDivision();
    return int(decimal / f.to_d());
}

bool operator ==(const int& decimal, const fraction& f) {
    return decimal == f.to_d();
}

bool operator !=(const int& decimal, const fraction& f) {
    return decimal != f.to_d();
}

bool operator <=(const int& decimal, const fraction& f) {
    return decimal <= f.to_d();
}

bool operator >=(const int& decimal, const fraction& f) {
    return decimal >= f.to_d();
}

bool operator <(const int& decimal, const fraction& f) {
    return decimal < f.to_d();
}

bool operator >(const int& decimal, const fraction& f) {
    return decimal > f.to_d();
}


///////////////////////////////////////////////////////////////


std::istream& operator >>(std::istream& stream, fraction& f)
{
    char div;
    int num, denom;
    stream >> num >> div >> denom;
    if (denom == 0)
        throw ZeroDivision();

    if (div != '/') {
        std::ostringstream stream;
        stream << num << div << denom;
        throw BadInputFormat(stream.str());
    }

    f._numerator = num;
    f._denominator = denom;
    f.to_canonical();

    return stream;
}

std::ostream& operator <<(std::ostream& stream, const fraction& f)
{
    stream << f._numerator;
    if(f._denominator > 1)
        stream << "/" << f._denominator;
    return stream;
}

///////////////////////////////////////////////////////////////
