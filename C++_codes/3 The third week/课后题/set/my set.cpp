#include "set.hpp"
// Create an empty set.
    Set::Set(){
        size = 0;
        for(int i=0;i < MAX_MEMBERS;i++)
            members[i] = '\0';
    }
    // Create an set with some element.
    Set::Set(int* m, int s){
        int i = 0, but[10000]={0}, size_=1;
        for(i=0;i<s;i++){
            if(but[m[i]]==0)  {
              members[i] = m[i];
              but[m[i]]++;
        size_++;}
            else continue;
}
            size = size_-1;
        members[size] = '\0';
    }
    
    // append a element to set.
    // If element in the set, return false.
    // Or insert in set and return true.
    bool Set::append(int e){
        for(int i=0;i<size;i++){
            if(e==members[i]) return 0;
            else continue;
        }
        members[size] = e;
        size++;
        return 1;
    }
    
    // remove a element by its value from set.
    // If element in the set, then remove it and return true.
    // Or return false.
    bool Set::remove(int e){
        int i = 0, j = 0;
        for(i=0;i<size;i++){
            if(members[i]==e) break;
            else continue;
        }
        if(i<size) {
            for(j=i;j<size-1;j++)
                members[j] = members[j+1];
            members[size-1] = '\0';
            size--;
            return 1;
        }
        else return 0;
    }
    
    // return true if the set is empty, or return false.
    bool Set::isEmptySet(){
        if(size<=0) return 1;
        else return 0;
    }
    
    // return set.
    int* Set::getMembers(){
        return members;
    }
    
    // return size of set.
    int Set::getSize(){
        return size;
    }
 
    // return false if element not in the set, or return true.
    bool Set::isInSet(int e){
        for(int i=0;i<size;i++){
            if(members[i]==e) return 1;
            else continue;
        }
        return 0; 
    }
 