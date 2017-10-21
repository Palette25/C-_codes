#ifndef COLLECTION_HPP
#define COLLECTION_HPP
#include <iostream>
typedef int E;

class Collection{
public:
	virtual ~Collection(){}
	virtual void add(E e) = 0;
	virtual void clear() = 0;
	virtual bool contain(E e) = 0;
	virtual bool isEmpty() = 0;
	virtual void remove(E e) = 0;
	virtual int size() = 0;
};

#endif