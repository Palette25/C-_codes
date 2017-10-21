#include "Dress.hpp"
Dress::Dress(const string & name1, const int price1){
	name = name1;
	price = price1;
}
Dress::Dress(const Dress & oth){
	name = oth.getName();
	price = oth.getPrice();
}
int Dress::getPrice() const{
	return price;
}
string Dress::getName() const{
	return name;
}