#ifndef EXCHANGE_H_
#define EXCHANGE_H_
#include <string>
std::string change1(char* st){
    std::string str = st;
    return str;
}
void change2(std::string st1, char* st2){
  int i = 0;
    for(i=0;st1[i]!='\0';i++)
      st2[i] = st1[i];
    st2[i]='\0';
}
#endif