#include "stack.hpp"
void stack::push(int num){
  if(isFull()==0) {
    storage[++top] = num;
  }
}
void stack::pop(void){
  if(isEmpty()==0){
    storage[top] = '\0';
    top--;
  }
}
int stack::peek(void){
  return top;
}
bool stack::isEmpty(void){
  if(top==-1) return 1;
  else return 0;
}
bool stack::isFull(void){
  if(top==max_size-1) return 1;
  else return 0;
}
void stack::clear(void){
  for(int i=0;i<=top;i++)
    storage[i] = '\0';
  top = -1;
}