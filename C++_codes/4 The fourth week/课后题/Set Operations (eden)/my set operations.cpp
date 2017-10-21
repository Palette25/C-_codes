#include <stdio.h>
#include <iostream>
#include <algorithm>
#define MAX_MEMBERS 100
 
class Set {
private:
    int members[MAX_MEMBERS];
    int size;
public:
    // Create an empty set.
    Set();
    // Create an set with some element.
    Set(int* m, int s);
    // Copy Constructor
    Set(Set const &s);
    
    // append a element to set.
    // If element in the set, return false.
    // Or insert in set and return true.
    bool append(int e);
    
    // remove a element by its value from set.
    // If element in the set, then remove it and return true.
    // Or return false.
    bool remove(int e);
    
    // return true if the set is empty, or return false.
    bool isEmptySet();
    
    // return true if the element e is in the set, or return false.
    bool isInSet(int e);
    
    // & is intersection of two set
    Set operator&(const Set &s);
    // | is union of two set
    Set operator|(const Set &s);
    // A - B is the complement of B with respect to A
    Set operator-(const Set &s);
    // A + B is their symmetric difference. A + B = (A - B) | (B - A)
    Set operator+(const Set &s);
    
    // return set.
    int* getMembers();
    
    // return size of set.
    int getSize();
    
};

Set::Set(){
	size = 0;
	int i = 0;
	for(i=0;i<100;i++)
		members[i] = '\0';
}
Set::Set(int* m, int s){
    int i = 0;
    for(i=0;i<s;i++)
    	members[i] = m[i];
    members[i] = '\0';
    size = i;
}
Set::Set(Set const &s){
	int i = 0;
	for(i=0;s.members[i]!='\0';i++)
		members[i] = s.members[i];
	members[i] = '\0';
	size = i;
}
bool Set::append(int e){
	int i = 0;
	for(i=0;i<size;i++){
		if(members[i]==e) return 0;
		else continue;
	}
	members[size] = e;
	size++;
	members[size] = '\0';
	return 1;
}
bool Set::remove(int e){
	int i = 0, j = 0;
	for(i=0;i<size;i++){
		if(members[i]==e) {
			for(j=i;j<size-1;j++)
                members[j] = members[j+1];
            members[size-1] = '\0';
            size--;
			return 1;
		}
		else continue;
	}
	return 0;
}
bool Set::isEmptySet(){
	if(size==0) return 1;
	else return 0;
}
bool Set::isInSet(int e){
	int i = 0;
	for(i=0;i<size;i++)
		if(members[i]==e) return 1;
	return 0;
}
Set Set::operator&(const Set &s){
	int arr[100] = {0}, i = 0, j = 0, k = 0;
	Set set1(s);
	int size1 = set1.getSize();
	int* point = set1.getMembers();
	for(i=0;i<size;i++){
		for(j=i;j<size1;j++)
			if(members[i]==point[j]) arr[k++] = members[i];
	}
	arr[k] = '\0';
	Set new_set(arr, k);
	return new_set;
}
Set Set::operator|(const Set &s){
	int arr[100] = {0}, i = 0, k = 0, flag[10000] = {0};
	Set set1(s);
	int size1 = set1.getSize();
	int* point = set1.getMembers();
	for(i=0;i<size;i++){
		arr[k++] = members[i];
		flag[members[i]] = 1;
	}
	for(i=0;i<size1;i++)
		if(flag[point[i]]==0) arr[k++] = point[i];
	arr[k] = '\0';
	Set new_set(arr, k);
	return new_set;
}
Set Set::operator-(const Set &s){
	int i = 0;
	Set new_set(*this);
	Set set1(s);
	int size1 = set1.getSize();
	int* point = set1.getMembers();
	for(i=0;i<size1;i++)
		if(new_set.remove(point[i])) continue;
	return new_set;
}
Set Set::operator+(const Set &s){
	Set set_r;
	Set set1(s);
	set_r = (*this-set1) | (set1-*this);
	return set_r;
}
int* Set::getMembers(){
	return members;
}
int Set::getSize(){
	return size;
}

void display(int* members, int size) {
    std::sort(members, members + size);
    std::cout << "{";
    for (int i = 0; i < size; i++) {
        if (i < size - 1) std::cout << members[i] << ", ";
        else std::cout << members[i];
    }
    std::cout << "}" << std::endl;
}
 
int main(int argc, const char * argv[]) {
    int test[6];
    std::cin >> test[0]
    >> test[1]
    >> test[2]
    >> test[3]
    >> test[4]
    >> test[5];
    // Constructor 1
    Set s1 = Set();
    display(s1.getMembers(), s1.getSize());
    std::cout << "is empty set: " << s1.isEmptySet() << std::endl;
    // append func
    std::cout << "append: " << s1.append(test[0]) << std::endl;
    std::cout << "append: " << s1.append(test[4]) << std::endl;
    display(s1.getMembers(), s1.getSize());
    // repeat append
    std::cout << "append: " << s1.append(test[0]) << std::endl;
    display(s1.getMembers(), s1.getSize());
 
    std::cout << "is empty set: " << s1.isEmptySet() << std::endl;
 
    // Constructor 2
    Set s2 = Set(test, 5);
    // remove func
    std::cout << "remove: " << s2.remove(test[0]) << std::endl;
    display(s2.getMembers(), s2.getSize());
    // repeat append
    std::cout << "remove: " << s2.remove(test[0]) << std::endl;
    display(s2.getMembers(), s2.getSize());
 
    std::cout << test[5] << " is in set: " << s2.isInSet(test[5]) << std::endl;
    std::cout << test[2] << " is in set: " << s2.isInSet(test[2]) << std::endl;
 
    display(s1.getMembers(), s1.getSize());
    display(s2.getMembers(), s2.getSize());
 
    Set s3;
    s3 = s1 & s2;
    display(s3.getMembers(), s3.getSize());
 
    s3 = s1 | s2;
    display(s3.getMembers(), s3.getSize());
 
    s3 = s1 - s2;
    display(s3.getMembers(), s3.getSize());
 
    s3 = s2 - s1;
    display(s3.getMembers(), s3.getSize());
 
    s3 = s1 + s2;
    display(s3.getMembers(), s3.getSize());
 
    return 0;
}
