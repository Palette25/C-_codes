#include <iostream>
using std::cin;
using std::string;

void Assign(char * &str, int &len){
  char *str1 = new char [len + 1];
  str = str1;
}
void AddTwo(string &res, char * &str1, char * &str2){
    int i, j;
    string s1 = str1;
    string s2 = str2;
    res = s1 + s2;
    delete [] str1;
    delete [] str2;
}