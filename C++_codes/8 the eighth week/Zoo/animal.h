#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>
#include <string>
using namespace std;
enum Type {
	CAT,
	DOG
};
class Animal {
public:
	Animal(std::string _name, int _age) : name(_name), age(_age) {}
	virtual void Shout() const = 0;
	virtual Type getType() const = 0;
	std::string getName() const {
		return name;
	}

	int getAge() const {
		return age;
	}
	void ChangeName(std::string name_) {
		name = name_;
	}
	void ChangeAge(int age_) {
		age = age_;
	}
private:
	std::string name;
	int age;
};
class Dog :public Animal {
public:
	Dog(std::string _name, int _age) :Animal(_name, _age) {}
	Dog() :Animal("dog", 0) {}
	virtual void Shout()const {
		cout << getName() << ": bark!!" << endl;
	}
	virtual Type getType()const {
		return DOG;
	}
};
class Cat :public Animal {
public:
	Cat(std::string _name, int _age) :Animal(_name, _age) {}
	Cat() :Animal("cat", 0) {}
	virtual void Shout() const {
		cout << getName() << ": meow~~" << endl;
	}
	virtual Type getType()const {
		return CAT;
	}
};
#endif