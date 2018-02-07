#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>


class Complex {
private:
  double _re;
  double _im;

public:
  Complex() : _re(0), _im(0) {}
  Complex(double re, double im): _re(re), _im(im) {}
  ~Complex() {}

  double re() { return _re; }
  double im() { return _im; }

  void set_re(double re) { _re = re; }
  void set_im(double im) { _im = im; }

  Complex operator + (const Complex& other);
  Complex operator - (const Complex& other);
  Complex operator * (const Complex& other);
  Complex operator / (const Complex& other);

  Complex& operator += (const Complex& other);
  Complex& operator -= (const Complex& other);
  Complex& operator *= (const Complex& other);
  Complex& operator /= (const Complex& other);

  bool operator == (const Complex& other);
  bool operator != (const Complex& other);

  friend std::ostream& operator << (std::ostream& str, const Complex& c);
  friend std::istream& operator >> (std::istream& str, const Complex& c);
};


#endif /* ifndef COMPLEX_H
 */
