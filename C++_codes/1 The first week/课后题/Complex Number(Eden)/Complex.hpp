#ifndef COMPLEX_HPP_
#define COMPLEX_HPP_
class Complex{
public:
    Complex( double real, double imaginary ) {
    setComplexNumber( real, imaginary );
} 
    Complex(){
    setComplexNumber( 0, 0);
}
     Complex add(Complex &);
    Complex subtract(Complex &);
    void printComplex();
    void setComplexNumber(double, double);
private:
  int realPart;
  int imaginary;
};
#endif