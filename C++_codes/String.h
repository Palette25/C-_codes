#ifndef STRING_H
#define STRING_H
#include <iostream>
using namespace std;
class String {  
public:  
String(){
  _buff = NULL;
  _size = 0;
}
explicit String(const char *src){
  _buff = new char [20];
  for(int i=0;src[i]!='\0';i++){
    _size++;
    _buff[i] = src[i];
  }
  _buff[_size] = '\0';
}
String(const String &src){
  _buff = new char[20];
  _size = src._size;
  for(int i=0;src._buff[i]!='\0';i++)
    _buff[i] = src._buff[i];
  _buff[_size] = '\0';
}

~String(){
  delete []_buff;
  _buff = NULL;
  _size = 0;
}

String& operator =(const String& src){
  delete []_buff;
  _buff = new char[20];
  _size = src._size;
  for(int i=0;src._buff[i]!='\0';i++)
    _buff[i] = src._buff[i];
  _buff[_size] = '\0';
  return *this;
} 
const char* c_str() const{
  return _buff;
}
inline char& operator[](int i){
  return _buff[i];
}

friend ostream& operator <<(ostream& os, const String& src){
  os << src.c_str();
  return os;
}

private:  
  char *_buff;  
  int _size;  
};
#endif
