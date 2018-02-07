#include "complex.h"

namespace Complex {

Complex Complex::operator +(const Complex &other) const {
    Complex c(*this);
    c += other;
    return c;
}

Complex Complex::operator -(const Complex &other) const {
    Complex c(*this);
    c -= other;
    return c;
}

Complex Complex::operator *(const Complex &other) const {
    Complex c(*this);
    c *= other;
    return c;
}

Complex Complex::operator /(const Complex &other) const {
    Complex c(*this);
    c /= other;
    return c;
}

Complex &Complex::operator +=(const Complex &other) {
    _re += other._re;
    _im += other._im;
    return *this;
}

Complex &Complex::operator -=(const Complex &other) {
    _re -= other._re;
    _im -= other._im;
    return *this;
}

Complex &Complex::operator *=(const Complex &other) {
    _re = _re * other._re - _im * other._im;
    _im = _re * other._im + _im * other._re;
    return *this;
}

Complex &Complex::operator /=(const Complex &other) {
    operator *=(other.conj());

    double denominator =
            other._im * other._im +
            other._re * other._re;

    _re /= denominator;
    _im /= denominator;

    return *this;
}

Complex Complex::conj() const {
    return Complex(_re, -_im);
}

bool Complex::operator ==(const Complex &other) const {
    return _re == other._re && _im == other._im;
}

bool Complex::operator !=(const Complex &other) const {
    return !(operator ==(other));
}

}
