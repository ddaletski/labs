#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <cstring>
#include <cmath>

namespace Complex {

class InvalidFormat : public std::exception {
    std::string _info;
public:
    InvalidFormat(const std::string& arg) {
	_info = "Invalid format of complex number: " + arg;
    }
    virtual const char* what() const noexcept {
        return _info.c_str();
    }
};


class Complex {
private:
    double _re;
    double _im;

public:
    Complex() : _re(0), _im(0) {}
    Complex(double re, double im): _re(re), _im(im) {}
    Complex(const Complex& c) : _re(c._re), _im(c._im) {}
    ~Complex() {}

    double re() { return _re; }
    double im() { return _im; }

    void set_re(double re) { _re = re; }
    void set_im(double im) { _im = im; }

    Complex operator + (const Complex& other) const;
    Complex operator - (const Complex& other) const;
    Complex operator * (const Complex& other) const;
    Complex operator / (const Complex& other) const;

    Complex& operator += (const Complex& other);
    Complex& operator -= (const Complex& other);
    Complex& operator *= (const Complex& other);
    Complex& operator /= (const Complex& other);

    Complex conj() const;

    bool operator == (const Complex& other) const;
    bool operator != (const Complex& other) const;

    friend std::ostream& operator << (std::ostream& str, const Complex& c) {
	char plus = c._im > 0 ? '+' : '-';
        str << c._re << plus << fabs(c._im) << '*' << 'i';
    }

    friend std::istream& operator >> (std::istream& str, Complex& c) {
        double re, im;
        char plus, i, mul;
        str >> re >> plus >> im >> mul >> i;
        if (i != 'i' || (plus != '+' && plus !='-') || mul !='*') {
            std::ostringstream tmp;
            tmp << re << plus << im << mul << i;
            throw InvalidFormat(tmp.str());
        }

	c._re = re;
	c._im = (plus == '+' ? im : -im);
    }
};

}

#endif /* ifndef COMPLEX_H
    */
