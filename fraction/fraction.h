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

    static fraction from_string(const std::string& s);

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

    bool operator ==(const int& decimal) const;
    bool operator !=(const int& decimal) const;
    bool operator <=(const int& decimal) const;
    bool operator >=(const int& decimal) const;
    bool operator <(const int& decimal) const;
    bool operator >(const int& decimal) const;

	
    friend fraction operator + (const int& decimal, const fraction& f);
    friend fraction operator - (const int& decimal, const fraction& f);
    friend fraction operator * (const int& decimal, const fraction& f);
    friend fraction operator / (const int& decimal, const fraction& f);

    friend fraction operator += (int& decimal, const fraction& f);
    friend fraction operator -= (int& decimal, const fraction& f);
    friend fraction operator *= (int& decimal, const fraction& f);
    friend fraction operator /= (int& decimal, const fraction& f);

    friend bool operator ==(const int& decimal, const fraction& f);
    friend bool operator !=(const int& decimal, const fraction& f);
    friend bool operator <=(const int& decimal, const fraction& f);
    friend bool operator >=(const int& decimal, const fraction& f);
    friend bool operator <(const int& decimal, const fraction& f);
    friend bool operator >(const int& decimal, const fraction& f);

    double to_d() const { return double(_numerator / _denominator); }
    operator double() { return to_d(); }
};

#endif // FRACTION_H
