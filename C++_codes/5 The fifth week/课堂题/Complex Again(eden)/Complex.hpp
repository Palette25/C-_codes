#ifndef COMPLEX_HPP_
#define COMPLEX_HPP_
#include <iostream>
using namespace std;
class Complex {
public:
   Complex(double , double );
   Complex();
   Complex operator + (Complex& );
   Complex operator - (Complex& );
   Complex operator * (Complex& );
   Complex operator / (Complex& );
   Complex& operator += (Complex& );
   Complex& operator -= (Complex& );
   Complex& operator *= (Complex& );
   Complex& operator /= (Complex& );
   Complex& operator = (Complex& );
   bool operator == (Complex& );
   bool operator != (Complex& );
   void SetReal(double re){real = re;}
   void SetImag(double im){imag = im;}
   friend std::ostream& operator<<(std::ostream &os, const Complex & one);
private:
   double real; 
   double imag; 
};
#endif