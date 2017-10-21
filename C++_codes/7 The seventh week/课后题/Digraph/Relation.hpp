#ifndef RELATION_H
#define RELATION_H
#include "BooleanMatrix.hpp"
class Relation{
public:
     Relation(BooleanMatrix const &m);
protected:
	BooleanMatrix m1;
};
#endif