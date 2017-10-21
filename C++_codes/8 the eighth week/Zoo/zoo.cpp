#include "zoo.h"
Zoo::Zoo() {
	dogcount = 0;
	catcount = 0;
}
void Zoo::addAnimal(Animal* ani) {
	if (ani->getType() == 0) {
		animal.push_back(ani);
		catcount++;
	}
	else {
		animal.push_back(ani);
		dogcount++;
	}
}
int Zoo::getDogCount() {
	return dogcount;
}
int Zoo::getCatCount() {
	return catcount;
}
void Zoo::deleteAnimalByName(std::string& name) {
	int i = 0, j = 0;
	int all = dogcount + catcount;
	for (i = 0; i < all; i++) {
		all = dogcount + catcount;
		if (animal[i]->getName() == name) {
			if (animal[i]->getType() == 0) catcount--;
			else dogcount--;
			for (j = i; j < all-1; j++)
				animal[j] = animal[j + 1];
			if(i!=all-1) i--;
		}
	}
}
void Zoo::deleteAnimalByAge(int &age) {
	int i = 0, j = 0;
	int all = dogcount + catcount;
	for (i = 0; i < all; i++) {
		all = dogcount + catcount;
		if (animal[i]->getAge() == age) {
			if (animal[i]->getType() == 0) catcount--;
			else dogcount--;
			for (j = i; j < all - 1; j++)
				animal[j] = animal[j + 1];
			if (i != all - 1) i--;
		}
	}
}
void Zoo::print() {
	int i = 0;
	for (i = 0; i < dogcount + catcount; i++)
		animal[i]->Shout();
}