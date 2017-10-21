include "user.hpp"
#include <string>
 
static bool checkLetterAndNumberString(const std::string &str) {
  for (int i = 0; i < str.length(); i++) {
    if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') ||
        (str[i] >= 'A' && str[i] <= 'Z')) {
      continue;
    } else {
      return false;
    }
  }
  return true;
}
 
bool alipay::User::verifyUsernameFormat(const std::string &username) {
  if (username.length() >= 6 && username.length() <= 20) {
    return checkLetterAndNumberString(username);
  }
  return false;
}
 
bool alipay::User::verifyPasswordFormat(const std::string &new_password) {
  if (new_password.length() >= 8 && new_password.length() <= 20) {
    return checkLetterAndNumberString(new_password);
  }
  return false;
}
 
bool alipay::User::verifyPhoneFormat(const std::string &phone) {
  if (phone.length() == 13) {
    for (int i = 0; i < phone.length(); i++) {
      if (phone[i] >= '0' && phone[i] <= '9') {
        continue;
      } else {
        return false;
      }
    }
    return true;
  }
  return false;
}
 
bool alipay::User::setUsername(const char *username) {
  std::string temp(username);
  if (this->verifyUsernameFormat(temp)) {
    this->username = temp;
    return true;
  }
  return false;
}
 
bool alipay::User::setPassword(const char *new_password,
                               const char *old_password) {
  std::string old_password_s(old_password);
  if (old_password_s == this->password || this->password.length() == 0) {
    std::string new_password_s(new_password);
    if (verifyPasswordFormat(new_password_s)) {
      this->password = new_password_s;
      return true;
    }
    return false;
  }
  return false;
}
 
bool alipay::User::setPhone(const char *new_phone) {
  std::string new_phone_s(new_phone);
  if (this->verifyPhoneFormat(new_phone_s)) {
    // this->phone = new_phone;
    this->phone = new_phone_s;
    return true;
  }
  return false;
}
 
bool alipay::User::setGender(alipay::Gender::Gender gender) {
  if (this->gender == alipay::Gender::Unknown &&
      gender != alipay::Gender::Unknown) {
    this->gender = gender;
    return true;
  }
  return false;
}
 
std::string alipay::User::getUsername(void) { return this->username; }
 
std::string alipay::User::getPhone(void) { return this->phone; }
 
alipay::Gender::Gender alipay::User::getGender(void) { return this->gender; }
 
long long int alipay::User::getMoneyAmount(const char *password) {
  std::string password_s(password);
  if (this->password == password_s) {
    return this->balance;
  }
  return -1;
}
 
bool alipay::User::deposit(long long int amount) {
  if (amount > 0) {
    this->balance += amount;
    return true;
  }
  return false;
}
 
bool alipay::User::withdraw(long long int amount, const char *password) {
  std::string password_s(password);
  if (this->password == password_s) {
    if (amount > 0) {
      if (this->balance - amount >= 0) {
        this->balance -= amount;
        return true;
      }
      return false;
    }
    return false;
  }
  return false;
}