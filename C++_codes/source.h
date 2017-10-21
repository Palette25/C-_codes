#ifndef SOURCE_H
#define SOURCE_H
#include <iostream>
using namespace std;
class Vector{
public:
	Vector(int num1, int num2){
		var1 = num1;
		var2 = num2;
	}
	Vector(){}
	friend ostream& operator<<(ostream& os, const Vector& oth){
		os << oth.var1 << " " << oth.var2;
		return os;
	}
	Vector operator+(Vector& oth){
		return Vector(var1+oth.var1, var2+oth.var2);
	}
	int get_var1(){return var1;}
	int get_var2(){return var2;}
private:
	int var1;
	int var2;
};

class Point{
public:
	Point(int x_, int y_){x = x_;y = y_;}
	Point(){}
	friend ostream& operator<<(ostream& os, const Point& oth){
		os << oth.x << " " << oth.y;
		return os;
	}
	Point operator+(Vector& oth){
		return Point(x+oth.get_var1(), y+oth.get_var2());
	}
private:
	int x;
	int y;
};

#endif