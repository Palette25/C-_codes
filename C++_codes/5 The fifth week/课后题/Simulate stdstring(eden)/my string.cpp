#include <iostream>
#include <cstring>
#include <string>
using namespace std;
class String {
  private:
    char *_buff;
    int _length, _size;  // _size is of the allocated memory
 
  public:
    // constructors
    String();
    explicit String(const char *src);
    String(const String &src);
    // destructor
    ~String();
    // member methods
    void assign(const char *src);
    void append(const char &other);
    void clear();
    int compare(const String &other) const;
    const char* c_str() const;
    bool empty() const;
    int find(const String &other, int pos = 0) const;
    int length() const;
    String substr(const int &pos, const int &count) const;
    // overload operators
    char& operator[](const int &index);
    void operator=(const String &other);
    void operator=(const char *src);
    String operator+(const String &other) const;
    bool operator<(const String &other) const;
    bool operator<=(const String &other) const;
    bool operator>(const String &other) const;
    bool operator>=(const String &other) const;
    bool operator==(const String &other) const;
    bool operator!=(const String &other) const;
    // friend methods
    friend std::ostream& operator<<(std::ostream& out, const String &str);
    // non-meaning static property
    static char _error_sign;  // initial as any char is okay
};
String::String(){
	_buff = NULL;
	_length = 0;
	_size = 0;
}
String::String(const char *src){
	int i = 0;
	_size = _length = 0;
	for(i=0;src[i]!='\0';i++)
		_size++;
	_length = _size;
	_size++;
	_buff = new char [_size];
	for(i=0;i<_length;i++)
		_buff[i] = src[i];
	_buff[i] = '\0';
}
String::String(const String &src){
	_size = src._size;
	_length = src._length;
	_buff = new char [_size];
	for(int i=0;i<_length;i++)
		_buff[i] = src._buff[i];
	_buff[_length] = '\0';
}
String::~String(){
	if(_buff!=NULL) delete [] _buff;
}
void String::assign(const char *src){
	if(_buff!=NULL) delete [] _buff;
	_length = _size = 0;
    for(int i=0;src[i]!='\0';i++)
    	  _length++;
    	  _size = _length + 1;
    	  _buff = new char [_size];
    	  for(int i=0;i<_length;i++)
    	   _buff[i] = src[i];
    	   _buff[_length] = '\0';
    
}
void  String::append(const char &other){
	if(_buff!=NULL) {
	  char str[100]={0};
	  int i = 0;
	  for(i=0;_buff[i]!='\0';i++)
	 	str[i] = _buff[i];
	 	_length++;
	    _size++;
	   delete [] _buff;
	   _buff = new char [_size];
	   for(i=0;i<_length;i++){
     	if(i==_length-1) _buff[i] = other;
     	else _buff[i] = str[i];
 }
       _buff[_length] = '\0';
}
    else {
          _length = 1;
	      _size = 2;
    	  _buff = new char [_size];
    	  _buff[0] = other;
	      _buff[_length] = '\0';
    }
}
void  String::clear(){
	delete [] _buff;
	_buff = NULL;
	_size = _length = 0;
}
int  String::compare(const String &other) const{
	if(strcmp(_buff, other._buff)>0) return 1;
	else if(strcmp(_buff, other._buff)==0) return 0;
	     else return -1;
}
const char*  String::c_str() const{
	return _buff;
}
bool  String::empty() const{
	if(_length==0) return 1;
	else return 0;
}
int  String::find(const String &other, int pos) const{
	int i = 0, flag = 0;
	for(i=0;i<_length;i++)
		if(_buff[i]==other._buff[pos]&&_buff[i+1]==other._buff[pos+1]) {
		    flag = 1;
		    break;
		}
	if(flag==0) return _length;
	else return i;
}
int  String::length() const{
	return _length;
}
String  String::substr(const int &pos, const int &count) const{
	String pi;
	pi._buff = new char [count+1];
	pi._size = count+1;
	pi._length = count;
	for(int i=pos, j = 0;j<count;i++, j++)
		pi._buff[j] = _buff[i];
	pi._buff[count] = '\0';
	return pi;
}
char&  String::operator[](const int &index){
	return _buff[index];
}
void  String::operator=(const String &other){
	_size = other._size;
	_length = other._length;
	delete [] _buff;
	_buff = new char [_size];
	for(int i=0;i<_size;i++)
		_buff[i] = other._buff[i];
	_buff[_length] = '\0';
}
void  String::operator=(const char *src){
	int i = 0;
	delete [] _buff;
	_length = 0;
	for(i=0;src[i]!='\0';i++)
		_length++;
	_size = _length + 1;
	_buff = new char [_size];
	for(i=0;i<_length;i++)
		_buff[i] = src[i];
	_buff[i] = '\0';
}
String  String::operator+(const String &other) const{
	String new_one;
	int i = 0;
	new_one._length = _length + other._length;
	new_one._size = _size + other._size;
	new_one._buff = new char [new_one._size];
	for(i=0;i<_length;i++)
		new_one._buff[i] = _buff[i];
	for(i=_length;i<new_one._length;i++)
		new_one._buff[i] = other._buff[i-_length];
	new_one._buff[i] = '\0';
	return new_one;
}
bool  String::operator<(const String &other) const{
	if(strcmp(_buff, other._buff)<0) return 1;
	else return 0;
}
bool  String::operator<=(const String &other) const{
	if(strcmp(_buff, other._buff)<=0) return 1;
	else return 0;
}
bool  String::operator>(const String &other) const{
	if(strcmp(_buff, other._buff)>0) return 1;
	else return 0;
}
bool  String::operator>=(const String &other) const{
	if(strcmp(_buff, other._buff)>=0) return 1;
	else return 0;
}
bool  String::operator==(const String &other) const{
	if(strcmp(_buff, other._buff)==0) return 1;
	else return 0;
}
bool  String::operator!=(const String &other) const{
    if(strcmp(_buff, other._buff)==0) return 0;
	else return 1;
}
std::ostream& operator<<(std::ostream& out, const String &str){
	int i = 0;
	for(i=0;i<str._length;i++)
		out << str._buff[i];
	return out;
}

String a, b("MFGZ!");
String c = b;
 
void display() {
  cout << a.empty() << " " << a.length() << " " << a << endl;
  cout << b.empty() << " " << b.length() << " " << b << endl;
  cout << c.empty() << " " << c.length() << " " << c << endl;
}
 
int main() {
  string aa, bb, cc;
  display();
  c[0] = 'K';
  display();
  cin >> aa >> cc;
  a.assign(aa.c_str());
  c.assign(cc.c_str());
  display();
  b.clear();
  display();
  for (int i = 0 ; i < 10; ++i) {
      char t;
      cin >> t;
      a.append(t);
      b.append(t);
      c.append(t);
  }
  display();
  b = c;
  display();
  b = a + c;
  display();
  cout << a.find(String("1993")) << endl;
  cout << b.find(String("HYOUKA")) << endl;
  cout << c.find(String("RIKKA")) << endl;
  cout << a.substr(0, 3) << endl;
  cout << b.substr(3, 8) << endl;
  cout << c.substr(6, 1) << endl;
  cout << (a > b) << (a >= b) << (a < b) << (a <= b) << (a == b) << endl;
  cout << a.compare(b) << b.compare(a) << endl;
  cout << (a > c) << (a >= c) << (a < c) << (a <= c) << (a == c) << endl;
  cout << a.compare(c) << c.compare(a) << endl;
  b = a;
  cout << (a > b) << (a >= b) << (a < b) << (a <= b) << (a == b) << endl;
  cout << a.compare(b) << b.compare(a) << endl;
  cout << a.compare(a) << endl;
  return 0;
}
 


