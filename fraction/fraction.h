#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <iomanip>
#include <exception>
#include <sstream>

typedef unsigned int uint;

class ZeroDivision : public std::exception {
    public:
        virtual const char* what() noexcept {
            return "zero division occured or denominator is 0";
        }
};

class BadInputFormat {
    private:
        std::string _info;
    public:
        BadInputFormat(const std::string& arg) {
            _info = "Bad input format for fraction: " + arg;
        }

        virtual const char* what() noexcept {
            return _info.c_str();
        }
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

    int numerator() { return _numerator; }
    int denominator() { return _denominator; }

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

    double to_d() const { return double(_numerator) / _denominator; }
    operator double() { return to_d(); }
};

#endif // FRACTION_H
