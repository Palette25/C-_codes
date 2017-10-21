#include "stack.hpp"
#include <string.h>
 
void stack::push(int data) {
  if (this->isFull()) {
    return;
  }
  this->top++;
  this->storage[top] = data;
}
 
void stack::pop(void) {
  if (this->isEmpty()) {
    return;
  }
  this->top--;
}
 
int stack::peek(void) {
  if (this->isEmpty()) {
    return 0;
  }
  return storage[top];
}
 
bool stack::isEmpty(void) { return (this->top == -1); }
 
bool stack::isFull(void) { return (this->top + 1 >= this->max_size); }
 
void stack::clear(void) { this->top = -1; }
 