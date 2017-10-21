#include "SingleDog.h"
int SingleDog::count = 0;
SingleDog::SingleDog(int id_, char* name_):id(id_){
    int i = 0;
    name = new char [20];
    for(i=0;name_[i]!='\0';i++){
        name[i] = name_[i];
    }
    name[i] = '\0';
    count++;
}
SingleDog::SingleDog(const SingleDog &other):id(other.id){
    int i = 0;
    name = new char [20];
    for(i=0;other.name[i]!='\0';i++){
        name[i] = other.name[i];
    }
  name[i] = '\0';
    count++;
}
SingleDog::~SingleDog(){
    delete [] name;
    name = NULL;
    count--;
}
int SingleDog::getCount(){
    return count;
}
