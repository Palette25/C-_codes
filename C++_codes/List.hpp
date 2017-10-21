#ifndef LIST_HPP
#define LIST_HPP
#include "Collection.hpp"


class List:public Collection{
public:
	virtual ~List(){}
	virtual E& get(int index) = 0;
	virtual E& operator[](int index) = 0;
	virtual int indexOf(E element) = 0;
	virtual void sort() = 0;
};

#endif