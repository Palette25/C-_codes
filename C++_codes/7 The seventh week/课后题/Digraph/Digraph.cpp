#include "Digraph.hpp"
int Digraph::getSetElePos(int n){
	if(set.isInSet(n)==0) return -1;
	for(int i=0;i<set.getSize();i++)
		if (n == set.getMembers()[i]) 
			return i;
}
Digraph::Digraph(BooleanMatrix const &m, Set const &s):Relation(m){
	set = s;
}
int Digraph::inDegree(int a){
	int sum = 0;
	for(int i=1;i<=m1.getRow();i++)
		if(m1.getElement(i, getSetElePos(a)+1)==1) sum++;
	return sum;
}
int Digraph::outDegree(int a){
	int sum = 0;
	for(int i=1;i<=m1.getColums();i++)
		if(m1.getElement(getSetElePos(a)+1, i)==1) sum++;
	return sum;
}
    
Digraph Digraph::pathOfLength(int n){
	if(n>1) {
		Digraph dir(m1, set);
		for(int k=1;k<=m1.getRow();k++){
		for(int i=1;i<=m1.getColums();i++){
			if (m1.getElement(k, i) == 1) {
				for (int j = 1; j <= m1.getColums(); j++) {
					if (m1.getElement(i, j) == 1) dir.m1.replace(1, k, j);
				}
			}
		}
	}
		return dir.pathOfLength(n - 1);
	}
	return *this;
}
    // Properties of Relations.    
bool Digraph::isReflexive() const{
	if (m1.getRow() != m1.getColums()) return 0;
	for(int i=1;i<=m1.getRow();i++)
		if(m1.getElement(i, i)!=1) return 0;
	return 1;
}
bool Digraph::isIrreflexive() const{
	if (m1.getRow() != m1.getColums()) return 0;
	for (int i = 1; i <= m1.getRow(); i++)
		if (m1.getElement(i, i) != 0) return 0;
	return 1;
}
bool Digraph::isSymmetric() const{
	if(m1.isSymmetrix()==1) return 1;
	else return 0;
}
bool Digraph::isAsymmetric() const{
	for(int i=1;i<=m1.getRow();i++){
		for(int j=1;j<=m1.getColums();j++)
			if(m1.getElement(i, j)==1){
				if(m1.getElement(j, i)!=0) return 0;
			}
	}
	return 1;
}
bool Digraph::isAntisymmetric() const{
	for(int i=1;i<=m1.getRow();i++){
		for(int j=1;j<m1.getColums();j++)
			if(m1.getElement(i, j)&&m1.getElement(j, i)){
				if(i!=j) return 0;
			}
	}
	return 1;
}
    
bool Digraph::isTransitive() const{
	for(int k=1;k<=m1.getRow();k++){
		for(int i=1;i<=m1.getRow();i++){
		  for(int j=1;j<m1.getColums();j++)
			if(m1.getElement(i, k)&&m1.getElement(k, j))
				if(m1.getElement(i, j)==0) return 0;
	}
	}
	return 1;
}
    
BooleanMatrix Digraph::getBooleanMatrix() const{
	return m1;
}