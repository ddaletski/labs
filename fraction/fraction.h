#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <iomanip>

typedef unsigned int uint;

class BadFraction {

};

class ZeroDivision {

};

class fraction
{
private:
    int _numerator;
    int _denominator;

    void to_canonical(); // reduction to canonical form

public:
    fraction(int numerator = 0, int denominator = 1);
    fraction(const fraction& f);
    ~fraction() {}

    friend std::ostream& operator << (std::ostream& stream, const fraction& f);
    friend std::istream& operator >> (std::istream& stream, fraction& f);

    fraction& operator = (const fraction& f);
    fraction& operator = (const int& decimal);
    fraction& operator = (const char* str);
    fraction& operator = (const std::pair<int, int>& pair);

    fraction& operator += (const fraction& f);
    fraction& operator -= (const fraction& f);
    fraction& operator *= (const fraction& f);
    fraction& operator /= (const fraction& f);

    fraction&operator +=(const int& decimal);
    fraction&operator -=(const int& decimal);
    fraction&operator *=(const int& decimal);
    fraction&operator /=(const int& decimal);

    fraction operator + (const fraction& f);
    fraction operator - (const fraction& f);
    fraction operator * (const fraction& f);
    fraction operator / (const fraction& f);

    fraction operator +(const int& decimal);
    fraction operator -(const int& decimal);
    fraction operator *(const int& decimal);
    fraction operator /(const int& decimal);

    fraction operator !();
    fraction operator -();

    fraction operator ++(int);
    fraction& operator ++();
    fraction operator --(int);
    fraction& operator --();

    bool operator ==(const fraction& f) const;
    bool operator !=(const fraction& f) const;
    bool operator <=(const fraction& f) const;
    bool operator >=(const fraction& f) const;
    bool operator <(const fraction& f) const;
    bool operator >(const fraction& f) const;

    bool operator ==(const double& decimal) const;
    bool operator !=(const double& decimal) const;
    bool operator <=(const double& decimal) const;
    bool operator >=(const double& decimal) const;
    bool operator <(const double& decimal) const;
    bool operator >(const double& decimal) const;

    double operator +(const double& decimal);
    double operator -(const double& decimal);
    double operator *(const double& decimal);
    double operator /(const double& decimal);

    operator double() const { return double(_numerator) / _denominator; }
    operator float() const { return float(_numerator) / _denominator; }
    operator int() const { return _numerator / _denominator; }
};

#endif // FRACTION_H
