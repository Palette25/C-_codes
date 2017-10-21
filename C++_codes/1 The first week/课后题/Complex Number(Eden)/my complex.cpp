#include <iostream>
using namespace std;
#include "Complex.hpp"
Complex Complex::add(Complex &right ){
  int a, b;
  a = realPart + right.realPart;
  b = imaginary + right.imaginary;
  Complex c(a, b);
  return c;
} 

Complex Complex::subtract( Complex &right ){
  int a, b;
  a = realPart - right.realPart;
  b = imaginary - right.imaginary;
  Complex c(a, b);
  return c;
} 

void Complex::printComplex() {
  cout << '(' << realPart << ", " << imaginary << ')';
} 

void Complex::setComplexNumber( double rp, double ip ) {
  realPart = rp;
  imaginary = ip;
} 