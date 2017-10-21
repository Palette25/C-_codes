#include "MyInteger.hpp"
#include <cmath>
MyInteger::MyInteger(int num){
  value = num;
}
int MyInteger::getValue() const{
  return value;
}
bool MyInteger::isEven() const{
  if(value%2==0) return 1;
  else return 0;
}
bool MyInteger::isOdd() const{
  if(value%2==0) return 0;
  else return 1;
}
bool MyInteger::isPrime() const{
  int i = 0;
  if(value<=1) return 0;
  if(value==2) return 1;
  for(i=2;i<value;i++){
    if(value%i==0) break;
    else continue;
  }
  if(i>=value) return 1;
  else return 0;
}
bool MyInteger::isEven(int num){
  if(num%2==0) return 1;
  else return 0;
}
bool MyInteger::isOdd(int num){
  if(num%2==0) return 0;
  else return 1;
}
bool MyInteger::isPrime(int num){
  int i = 0;
  if(num<=1) return 0;
  if(num==2) return 1;
  for(i=2;i<num;i++){
    if(num%i==0) break;
    else continue;
  }
  if(i>=num) return 1;
  else return 0;
}
bool MyInteger::isEven(const MyInteger& integer){
  if(integer.value%2==0) return 1;
  else return 0;
}
bool MyInteger::isOdd(const MyInteger& integer){
  if(integer.value%2==0) return 0;
  else return 1;
}
bool MyInteger::isPrime(const MyInteger& integer){
  int i = 0;
  if(integer.value<=1) return 0;
  if(integer.value==2) return 1;
  for(i=2;i<integer.value;i++){
    if(integer.value%i==0) break;
    else continue;
  }
  if(i>=integer.value) return 1;
  else return 0;
}
bool MyInteger::equals(int num){
  if(num==value) return 1;
  else return 0;
}
bool MyInteger::equals(const MyInteger& integer){
  if(integer.value==value) return 1;
  else return 0;
}
int MyInteger::parseInt(const std::string& str1){
  int i=0, sum=0, len=str1.size();
  if(str1[0]!='-'){
     for(i=0;str1[i]!='\0';i++){
      sum+=(str1[i]-'0')*pow(10,len-i-1);
  }
 }
  else {
     for(i=1;str1[i]!='\0';i++)
       sum+=(str1[i]-'0')*pow(10, len-i-1);
     sum = sum - 2 * sum;
   }
  return sum;
}