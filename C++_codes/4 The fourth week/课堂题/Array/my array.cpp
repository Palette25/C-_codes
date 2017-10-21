#include "array.hpp"
#include <iostream>
array::array(size_t size){
  _size = size;
  _data = new int[size+1];
}
//constructor
array::~array(){
  delete [] _data;
}
array::size_t array::max_size(void){
  return _size;
}
array::data_type& array::at(const data_type& i){
  return _data[i];
}

array::data_type& array::front(){
  return _data[0];
}
  
array::data_type& array::back(){
  return _data[_size-1];
}
  
array::pointer array::data(){
  return _data;
}
 
  
void array::fill(const data_type& value){
  int i = 0;
  for(i=0;i<_size;i++)
    _data[i] = value;
  _data[_size] = '\0';
}
  
void array::resize(int newSize){
  int i =0;
  int arr[_size] = {0};
  for(i=0;i<_size;i++)
    arr[i] = _data[i];
  delete [] _data;
  _data = new int[newSize+1];
  for(i=0;i<_size;i++)
    _data[i] = arr[i];
  _size = newSize;
  _data[i] = '\0';
}
  
void array::sort(int from, int to){
  int i = 0, j = 0;
  for(i=from;i<to;i++){
    for(j=i;j<to;j++)
      if(_data[i]>_data[j]){
        int temp = _data[i];
        _data[i] = _data[j];
        _data[j] = temp;
      }
  }
}