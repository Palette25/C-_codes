#ifndef ZOO_H
#define ZOO_H
#include "animal.h"
#include <vector>
class Zoo {
public:
	Zoo();
	void addAnimal(Animal* animal1);
	int getDogCount();
	int getCatCount();
	void deleteAnimalByName(std::string& name);
	void deleteAnimalByAge(int &age);
	void print();
private:
	vector<Animal*> animal;
	int dogcount;
	int catcount;
};
#endif