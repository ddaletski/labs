#include "fraction.h"

typedef unsigned int uint;

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
        throw BadFraction();
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
    _numerator = numerator;
    _denominator = denominator;
    to_canonical();
}

fraction::fraction(const fraction &f)
{
    _numerator = f._numerator;
    _denominator = f._denominator;
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
    _numerator = pair.first;
    _denominator = pair.second;
    to_canonical();
    return *this;
}

fraction&fraction::operator =(const char* str)
{
    sscanf(str, "%d/%d", &_numerator, &_denominator);
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

double fraction::operator +(const double& decimal)
{
    return double(*this) + decimal;
}

double fraction::operator -(const double& decimal)
{
    return double(*this) - decimal;
}

double fraction::operator *(const double& decimal)
{
    return double(*this) * decimal;
}

double fraction::operator /(const double& decimal)
{
    return double(*this) / decimal;
}

///////////////////////////////////////////////////////

fraction fraction::operator !()
{
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

fraction fraction::operator ++(int)
{
    fraction temp = *this;
    _numerator += _denominator;
    return temp;
}

fraction&fraction::operator ++()
{
    _numerator += _denominator;
    return *this;
}

fraction fraction::operator --(int)
{
    fraction temp = *this;
    _numerator -= _denominator;
    return temp;
}

fraction&fraction::operator --()
{
    _numerator -= _denominator;
    return *this;
}

//////////////////////////////////////////////////////

bool fraction::operator ==(const fraction& f) const
{
    return double(*this) == double(f);
}

bool fraction::operator !=(const fraction& f) const
{
    return double(*this) != double(f);
}

bool fraction::operator <=(const fraction& f) const
{
    return double(*this) <= double(f);
}

bool fraction::operator >=(const fraction& f) const
{
    return double(*this) >= double(f);
}

bool fraction::operator <(const fraction& f) const
{
    return double(*this) < double(f);
}

bool fraction::operator >(const fraction& f) const
{
    return double(*this) > double(f);
}

bool fraction::operator ==(const double& decimal) const
{
    return double(*this) == decimal;
}

bool fraction::operator !=(const double& decimal) const
{
    return double(*this) != decimal;
}

bool fraction::operator <=(const double& decimal) const
{
    return double(*this) <= decimal;
}

bool fraction::operator >=(const double& decimal) const
{
    return double(*this) >= decimal;
}

bool fraction::operator <(const double& decimal) const
{
    return double(*this) < decimal;
}

bool fraction::operator >(const double& decimal) const
{
    return double(*this) > decimal;
}

//////////////////////////////////////////////////////////////////

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

double operator +(const double& decimal, const fraction& f)
{
    double temp = decimal;
    temp += double(f);
    return temp;
}

double operator -(const double& decimal, const fraction& f)
{
    double temp = decimal;
    temp -= double(f);
    return temp;
}

double operator *(const double& decimal, const fraction& f)
{
    double temp = decimal;
    temp *= double(f);
    return temp;
}

double operator /(const double& decimal, const fraction& f)
{
    fraction temp = decimal;
    temp /= double(f);
    return temp;
}

///////////////////////////////////////////////////////////////

double& operator +=(double& decimal, const fraction& f)
{
    return decimal += double(f);
}

double& operator -=(double& decimal, const fraction& f)
{
    return decimal -= double(f);
}

double& operator *=(double& decimal, const fraction& f)
{
    return decimal *= double(f);
}

double& operator /=(double& decimal, const fraction& f)
{
    return decimal /= double(f);
}

///////////////////////////////////////////////////////////////

std::istream& operator >>(std::istream& stream, fraction& f)
{
    char div;
    stream >> f._numerator >> div >> f._denominator;
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

