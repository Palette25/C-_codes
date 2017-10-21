#ifndef WORLD_H_
#define WORLD_H_
#include <iostream>
using std::cout;
using std::endl;
struct person{
	int friends[100];
	int size;
	int id;
	person(int size_ = 0) { size = size_ ;}
};
 class group {
 public:
 	group(bool flag);
    void displayGroup();
    bool addMember(person &p);
    bool deleteMember(person &p);
    bool makeFriend(person &p1, person &p2);
    bool breakRelation(person &p1, person &p2);
private:
	person humans[990];
	int size;
	bool flag;
};

group::group(bool flag_){
	size = 0;
	flag = flag_;
}
void group::displayGroup(){
	for(int i=0;i<size;i++){
		cout << "Person_" << humans[i].id << ": ";
		for(int j=0;j<humans[i].size;j++){
			if(j!=humans[i].size-1) cout << humans[i].friends[j] << ", ";
			else  cout << humans[i].friends[j];
		}
	}
}
bool group::addMember(person &p){
	p.id = size;
	humans[size] = p;
	size++;
    if(flag==1){
    	for(int i=0;i<2000;i++)
    		p.friends[i] = 1;
    }
    return 1;
}
bool group::deleteMember(person &p){
	int i = 0;
	for(i=0;i<size;i++)
		if(i==p.id) break;
	for(;i<size-1;i++)
		humans[i] = humans[i+1];
	size--;
	return 1;
}
bool group::makeFriend(person &p1, person &p2){
	p1.friends[p1.size] = p2.id;
	p2.friends[p2.size] = p1.id;
	p1.size++;
	p2.size++;
	return 1;
}
bool group::breakRelation(person &p1, person &p2){
	int i = 0;
	for(i=0;i<p1.size;i++)
		if(i==p2.id) break;
	for(;i<p1.size-1;i++)
		p1.friends[i] = p1.friends[i+1];
	p1.size--;
	for(i=0;i<p2.size;i++)
		if(i==p1.id) break;
	for(;i<p2.size-1;i++)
		p2.friends[i] = p2.friends[i+1];
	p2.size--;
	return 1;
}
#endif