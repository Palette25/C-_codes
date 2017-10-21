#ifndef Digraph_hpp
#define Digraph_hpp

#include <stdio.h>
#include "BooleanMatrix.hpp"
#include "Set.hpp"
#include "ProductSet.hpp"
#include "Relation.hpp"

class Digraph: Relation {
private:
    Set set;
    int getSetElePos(int);
public:
    Digraph(BooleanMatrix const &m, Set const &s);
    int inDegree(int);
    int outDegree(int);
    
    Digraph pathOfLength(int);
    
    // Properties of Relations.    
    bool isReflexive() const;
    bool isIrreflexive() const;
    bool isSymmetric() const;
    bool isAsymmetric() const;
    bool isAntisymmetric() const;
    
    bool isTransitive() const;
    
    BooleanMatrix getBooleanMatrix() const;
};

#endif /* Digraph_hpp */

