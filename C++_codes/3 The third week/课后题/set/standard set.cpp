#include "set.hpp"
 
Set::Set() {
    size = 0;
}
 
Set::Set(int* m, int s) {
    size = 0;
    for (int i = 0; i < s ; i++) {
        if (!isInSet(m[i])) {
            members[size++] = m[i];
        }
        if (size == MAX_MEMBERS) break;
    }
}
 
bool Set::append(int element) {
    if (size < MAX_MEMBERS && !isInSet(element)) {
        members[size] = element;
        size++;
        return true;
    } else {
        return false;
    }
}
 
bool Set::remove(int element) {
    for (int i = 0; i < size; i++) {
        if (members[i] == element) {
            members[i] = members[--size];
            return true;
        }
    }
    return false;
}
 
bool Set::isEmptySet() {
    return (size == 0) ? true : false;
}
 
int* Set::getMembers() {
    return members;
}
 
int Set::getSize() {
    return size;
}
 
bool Set::isInSet(int element) {
    for (int i = 0; i < size; i++) {
        if (members[i] == element) {
            return true;
        }
    }
    return false;
}
