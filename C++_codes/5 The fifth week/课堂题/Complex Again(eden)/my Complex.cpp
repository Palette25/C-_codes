#include "Complex.hpp"
Complex::Complex(double _real, double _imag){
	real = _real;
	imag = _imag;
}
Complex::Complex(){
	real = 0;
	imag = 0;
}
std::ostream& operator<<(std::ostream &os, const Complex & one){
    if(one.imag>0) {
    	if(one.real!=0) os << one.real << "+" << one.imag << "i" <<endl;
    	else os << one.imag << "i" << endl;
    }
    if(one.imag<0) {
    	if(one.real!=0) os << one.real << one.imag << "i" << endl;
    	else os << one.imag << "i" << endl;
    }
    if(one.imag==0) {
    	if(one.real!=0) os << one.real ;
    	else os << 0 ;
    }
    return os;
}
Complex Complex::operator+(Complex& other){
	return Complex(real+other.real, imag+other.imag);
}
Complex Complex::operator-(Complex& other){
	return Complex(real-other.real, imag-other.imag);
}
Complex Complex::operator*(Complex& other){
	return Complex(real*other.real-(imag*other.imag), real*other.imag+other.real*imag);
}
Complex Complex::operator/(Complex& other){
	if(real==other.real) return Complex(real/other.real, 0);
	else return Complex((real*other.real + imag*other.imag) / (other.real*other.real+other.imag*other.imag), (imag*other.real - real*other.imag) / (other.real*other.real+other.imag*other.imag));
}
Complex& Complex::operator+=(Complex& other){
	real += other.real;
	imag += other.imag;
	return *this;
}
Complex& Complex::operator-=(Complex& other){
	real -= other.real;
	imag -= other.imag;
	return *this;
}
Complex& Complex::operator*=(Complex& other){
	double real_ = real, imag_ = imag;
	real = real_*other.real - (imag_ * other.imag);
	imag = real_*other.imag + other.real*imag_;
	return *this;
}
Complex& Complex::operator/=(Complex& other){
	if(real==0) {
		real = other.real;
		imag = other.imag;
	}
	else {
		    int real0 = real;
	    real = (real*other.real + imag*other.imag) / (other.real*other.real+other.imag*other.imag);
	    imag = (imag*other.real - real0*other.imag) / (other.real*other.real+other.imag*other.imag);
     }
	return *this;
}
Complex& Complex::operator=(Complex& other){
	real = other.real;
	imag = other.imag;
	return *this;
}
bool Complex::operator==(Complex& other){
	if(real==other.real&&imag==other.imag) return 1;
	else return 0;
}
bool Complex::operator!=(Complex& other){
	if(real==other.real&&imag==other.imag) return 0;
	else return 1;
}
