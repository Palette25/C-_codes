#ifndef VECTOR_H
#define VECTOR_H
#include "base.h"
#include "test.h"
using namespace std;

template< typename T, typename Alloc = std::allocator<T> >
class myVector:public Base{
public:
      myVector(){
      	_data = Alloc().allocate(1);
      	_size = 0;
		_capacity = 1;
      }
      myVector(const size_t & size, const T & val,
                 Alloc a = Alloc()){
      	_size = size;
      	_capacity = size;
      	_data = a.testAllocator::allocate(size);
      	for(size_t i=0;i<size;i++)
      		a.testAllocator::construct(_data+i, val);
      }
      template<typename InputIterator>
          myVector(InputIterator begin, InputIterator end,
                     Alloc a = Alloc()){
			_size = end - begin;
          	_capacity = _size;
          	_data = a.testAllocator::allocate(_size);
          	InputIterator temp = begin;
          	for(size_t i=0;temp!=end;i++, temp++)
          		a.construct(_data+i, *temp);
          }
      myVector(const myVector & other){
      	_size = other._size;
      	_capacity = other._capacity;
		Alloc a = Alloc();
		_data = a.testAllocator::allocate(_capacity);
		for (size_t i = 0; i < _size; i++)
			a.construct(_data + i, other[i]);
      }
      ~myVector(){
		  for (size_t i = 0; i < _size; i++)
			  Alloc().testAllocator::destroy(_data + i);
		  if (_capacity > 0) Alloc().testAllocator::deallocate(_data, _capacity);
      }
      myVector & operator=(const myVector & other){
		  if (&other == this) return *this;
		  else {
			  for (size_t i = 0; i < _size; i++)
				  Alloc().testAllocator::destroy(_data + i);
			  if (_capacity > 0) Alloc().testAllocator::deallocate(_data, _capacity);
			  _size = other._size;
			  _capacity = other._capacity;
			  _data = Alloc().testAllocator::allocate(_capacity);
			  for (size_t i = 0; i < _size; i++)
				  Alloc().testAllocator::construct(_data + i, other._data[i]);
			  return  *this;
		  }
      }
      typedef T * iterator;
      typedef const T * const_iterator;
      inline iterator begin(){
      	return _data;
      }
      inline const_iterator begin() const{
		  return _data;
      }
      inline iterator end(){
      	return (_data + _size);
      }
      inline const_iterator end() const{
		  return (_data + _size);
      }
      inline size_t size(){
      	return _size;
      }
	  void resize(const size_t & newSize) {
		  if(newSize > _size){
			  if (newSize > _capacity) {
				  size_t newcapacity = _capacity;
				  while (newSize > newcapacity) {
					  newcapacity *= 2;
				  }
				  reserve(newcapacity);
			  }
			  for (size_t i = _size; i < newSize; i++)
				  Alloc().testAllocator::construct(_data + i, 0);
		  }
		  else {
			  for (size_t i = newSize; i < _size; i++)
				  Alloc().testAllocator::destroy(_data + i);
		  }
		  _size = newSize;
	  }
	  void resize(const size_t & newSize, const T & val) {
		  if (newSize > _size) {
			  if (newSize > _capacity) {
				  size_t newcapacity = _capacity ;
				  while (newSize > newcapacity) {
					  newcapacity *= 2;
				  }
				  reserve(newcapacity);
			  }
			  for (size_t i = _size; i < newSize; i++)
				  Alloc().testAllocator::construct(_data + i, val);
		  }
		  else {
			  for (size_t i = newSize; i < _size; i++)
				  Alloc().testAllocator::destroy(_data + i);
		  }
		  _size = newSize;
	  }
      inline std::size_t capacity() const{
      	return _capacity;
      }
      inline bool empty() const{
		  if (_size == 0) return 1;
		  else return 0;
      }
	  void reserve(const std::size_t & newCapacity) {
		  if (newCapacity > _capacity) {
			  T* other = Alloc().testAllocator::allocate(newCapacity);
			  for (size_t i = 0; i < _size; i++) {
				  Alloc().testAllocator::construct(other + i, _data[i]);
				  Alloc().testAllocator::destroy(_data + i);
			  }
			  Alloc().testAllocator::deallocate(_data, _capacity);
			  _data = other;
			  _capacity = newCapacity;
		  }
	  }
         // Element Access
	  inline T & operator[](const std::size_t & index) {
		  return _data[index];
	  }
	  inline const T & operator[](const std::size_t & index) const {
		  return _data[index];
	  }
	  inline T & front() {
		  return _data[0];
	  }
	  inline const T & front() const {
		  return _data[0];
	  }
	  inline T & back() {
		  return _data[_size - 1];
	  }
	  inline const T & back() const {
		  return _data[_size - 1];
	  }
	  inline T * data() {
		  return _data;
	  }
	  inline const T * data() const {
		  return _data;
	  }
         // Modifiers
	  template<typename InputIterator>
	  void assign(InputIterator begin, InputIterator end) {
		  InputIterator temp = begin;
		  size_t size = 0;
		  for (; temp != end; temp++) {
			  size++;
		  }
		  if (size > _capacity) {
			  size_t capacity = _capacity;
			  while (size > capacity) {
				  capacity++;
			  }
			  reserve(capacity);
		  }
		  for (size_t i = 0; i < _size; i++)
			  Alloc().testAllocator::destroy(_data + i);
		  temp = begin;
		  for (size_t i = 0;i<size;i++)
			  Alloc().testAllocator::construct(_data + i, *(temp++));
		  _size = size;
	  }
	  void assign(const size_t & newSize, const T & val) {
		  if (newSize > _capacity) {
			  size_t capacity = _capacity * 2;
			  while (newSize > capacity) {
				  capacity *= 2;
			  }
			  reserve(capacity);
		  }
		  for (size_t i = 0; i<_size; i++)
			  Alloc().testAllocator::destroy(_data + i);
		  for (size_t i = 0; i<newSize; i++)
			  Alloc().testAllocator::construct(_data + i, val);
		  _size = newSize;
	  }
	  void push_back(const T & val) {
		  if (_size >= _capacity)
			  reserve(_capacity * 2);
		  Alloc().testAllocator::construct(_data + _size, val);
		  _size++;
	  }
	  void pop_back() {
		  Alloc().testAllocator::destroy(_data + _size - 1);
		  _size--;
	  }
      void clear(){
		  for (size_t i = 0; i < _size; i++)
			  Alloc().testAllocator::destroy(_data + i);
		  _size = 0;
	  }
private:
      T * _data;
      size_t _size, _capacity;
};

#endif