#include <string>
#include "user.hpp"
using namespace alipay;
inline bool User::verifyPasswordFormat(const std::string &password){
  if(password.size()<8||password.size()>20) return 0;
  for(int i=0;i<password.size();i++) {
    if(password[i]>=48&&password[i]<=57||password[i]>=65&&password[i]<=90||password[i]>=97&&password[i]<=122)
      continue;
    else return 0;
  }
  return 1;
}
inline bool User::verifyUsernameFormat(const std::string &username){
  if(username.size()<6||username.size()>20) return 0;
  for(int i=0;i<username.size();i++) {
    if(username[i]>=48&&username[i]<=57||username[i]>=65&&username[i]<=90||username[i]>=97&&username[i]<=122)
      continue;
    else return 0;
  }
  return 1;
}
inline bool User::verifyPhoneFormat(const std::string &phone){
  if(phone.size()!=13) return 0;
  for(int i=0;i<phone.size();i++){
    if(phone[i]>=48&&phone[i]<=57) continue;
    else return 0;
  }
  return 1;
}
bool User::setUsername(const char *new_username){
  std::string user = new_username;
  if(verifyUsernameFormat(user)) {
    username = user;
    return 1;
  }
  else return 0;
}
bool User::setPassword(const char *new_password, const char *old_password){
  std::string pass1 = new_password;
  std::string pass2 = old_password;
  if(verifyPasswordFormat(pass1)&&(pass2==password)) {
    password = pass1;
    return 1;
  }
  else return 0;
}
bool User::setPhone(const char *new_phone){
  std::string phone1 = new_phone;
  if(verifyPhoneFormat(phone1)) {
    phone = phone1;
    return 1;
  }
  else return 0;
}
bool User::setGender(Gender::Gender new_gender){
  gender = new_gender;
  return 1;
}
 
std::string User::getUsername(void){
  return username;
}
std::string User::getPhone(void){
  return phone;
}
alipay::Gender::Gender User::getGender(void){
  alipay::Gender::Gender gender1;
  gender1 = gender;
  return gender1;
}
long long int User::getMoneyAmount(const char *password1){
  std::string pass1 = password1;
  if(pass1==password) return balance;
  else return 0;
}
bool User::deposit(long long int amount){
  balance += amount;
  return 1;
}
bool User::withdraw(long long int amount, const char *password1){
  std::string pass1 = password1;
  if(amount <= 0) return 0;
  if(pass1==password&&balance >= amount) {
    balance -= amount;
    return 1;
  }
  return 0;
}