#include "queue.hpp"
 
void queue::push(int data) {
  if (this->isFull()) {
    return;
  }
  this->storage[rear] = data;
  this->rear = (this->rear + 1) % this->max_size;
}
 
void queue::pop(void) {
  if (this->isEmpty()) {
    return;
  }
  this->head = (this->head + 1) % this->max_size;
}
 
int queue::front(void) {
  if (this->isEmpty()) {
    return 0;
  }
  return this->storage[head];
}
 
int queue::back(void) {
  if (this->isEmpty()) {
    return 0;
  }
  return this->storage[(rear-1+max_size) % max_size];
}
 
bool queue::isFull(void) {
  return ((this->rear + 1) % this->max_size) == this->head;
}
 
bool queue::isEmpty(void) { return this->head == this->rear; }
 
void queue::clear(void) { this->rear = this->head; }
 