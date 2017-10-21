#include "queue.hpp"
void queue::push(int num){
  if(isFull()==0) {
    storage[rear] = num;
    rear++;
  }
}
void queue::pop(void){
  if(isEmpty()==0){
  storage[head] = '\0';
  head++;}
}
int queue::front(void){
  return storage[head];
}
int queue::back(void){
  return storage[rear-1];
}
bool queue::isFull(void){
  if(rear==max_size-1&&head!=max_size-1) return 1;
  else return 0;
}
bool queue::isEmpty(void){
  if(rear==head) return 1;
  else return 0;
}
void queue::clear(void){
  for(int i=0;i<=rear;i++)
    storage[i] = '\0';
  head = rear = 0;
}