#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std; 
namespace Alipay1 {
class user {
  private:
  char username[21];
  char password[21];
  double balance;
 
 public:
  user(const char* username, const char* password);
  ~user();
  const char* getUsername() const;
  const char* getPassword() const;
  const void setUsername(const char* username);
  const void setPassword(const char* password);
 
  double getBalance();
 
  bool withdraw(double amount);
  bool deposite(double amount);
};
}
using namespace Alipay1; 
user::user(const char* username_, const char* password_){
	int i = 0;
	for(i=0;username_[i]!='\0';i++)
		username[i] = username_[i];
	username[i] = '\0';
	for(i=0;password_[i]!='\0';i++)
		password[i] = password_[i];
	password[i] = '\0';
	balance = 0;
}
user::~user(){
	balance = 0;
}
const char* user::getUsername() const{
	return username;
}
const char* user::getPassword() const{
	return password;
}
const void user::setUsername(const char* new_username){
	int i = 0;
	for(i=0;new_username[i]!='\0';i++)
		username[i] = new_username[i];
	username[i] = '\0';
}
const void user::setPassword(const char* new_password){
	int i = 0;
	for(i=0;new_password[i]!='\0';i++)
		password[i] = new_password[i];
	password[i] = '\0';
}
 
double user::getBalance(){
	return balance;
}
bool user::withdraw(double amount){
	if(amount>=0&&balance>=amount) {
		balance -= amount;
	    return 1;
}
	else return 0;
}
bool user::deposite(double amount){
	if(amount>=0) {
		balance += amount;
		return 1;
}
	else return 0;
}
namespace Alipay2 {
#define boss "Mayun"
#define MAX_USER 10000
enum GENDER { MALE = 0, FEMALE = 1 };
 
const double PRECISION = 0.000001;
}
namespace Alipay3 {
class userController {
 private:
  double interest_rate;
  user* users[MAX_USER];
  int usercount;
  int getUserIndex(const char* username) const;
 
 public:
  userController(double interest_rate);
  ~userController();
  bool createUser(const char* username, const char* password);
  bool deposite(const char* username, double amount);
  bool withdraw(const char* username, double amount);
  std::string getUserInfoByName(const char* username) const;
  int getUserCount(void) const;
  bool removeUserByUsername(const char* username);
  bool setInterest(double interest);
  void payInterest(void);
};
}
using namespace Alipay2;
using namespace Alipay3;
int userController::getUserIndex(const char* username_) const{
	int i = 0;
	for(i=0;i<usercount;i++)
		if(strcmp(users[i]->getUsername(), username_)==0) break;
	return i;
}
userController::userController(double _interest_rate){
	interest_rate = _interest_rate;
	usercount = 0;
}
userController::~userController(){
	if(users!=NULL) {
		for(int i=0;i<usercount;i++){
		  user* point = users[i];
		  delete  point;
	}
	}
}
bool userController::createUser(const char* username_, const char* password_){
	string s1 = username_, s2 = password_;
    if(s1.size()>=6&&s1.size()<=20&&s2.size()>=8&&s2.size()<=20&&usercount<=MAX_USER) {
    	users[usercount] = new user(username_, password_) ;
    	usercount++;
    	return 1;
    }
    else return 0;
}
bool userController::deposite(const char* username_, double amount){
	int i = 0;
	for(i=0;i<usercount;i++)
		if(strcmp(username_, users[i]->getUsername())==0) break;
	if(i<usercount&&amount>=0) {
		users[i]->deposite(amount); 
		return 1;
	}
	else return 0;
}
bool userController::withdraw(const char* username_, double amount){
	int i = 0;
	for(i=0;i<usercount;i++)
		if(strcmp(username_, users[i]->getUsername())==0) break;
	if(i<usercount&&amount>=0&&users[i]->getBalance()>=amount) {
		users[i]->withdraw(amount);
		return 1;
	}
	else return 0;
}
std::string userController::getUserInfoByName(const char* username_) const{
	string s1 = username_;
	int i = 0, j = 0;
	for(i=0;i<usercount;i++)
		if(strcmp(username_, users[i]->getUsername())==0) break;
	string s2 = users[i]->getPassword();
	char buff[100];
	float p = users[i]->getBalance();
	if(p==0.0) sprintf(buff, "%d", p);
	else sprintf(buff, "%g", p);
	string s3 = buff;
	string info = "username:" + s1 + '\n' + "password:*********" + '\n' + "balance:" + s3;
	return info;
}
int userController::getUserCount(void) const{
	return usercount;
}
bool userController::removeUserByUsername(const char* username_){
	int i = 0, j = 0;
	for(i=0;i<usercount;i++)
		if(strcmp(username_, users[i]->getUsername())==0) break;
	if(i>=usercount) return 0;
	else {
		for(j=i;j<usercount-1;j++){
			users[j]->setUsername(users[j+1]->getUsername());
			users[j]->setPassword(users[j+1]->getPassword());
			double cut = users[j]->getBalance() - users[j+1] -> getBalance();
			if(cut>=0)
			   users[j]->withdraw(cut);
			else users[j]->deposite(-cut);
		}
		delete users[usercount-1];
		usercount--;
		return 1;
	}
}
bool userController::setInterest(double interest){
	if(interest>=0) {
		interest_rate = interest;
		return 1;
	}
	else return 0;
}
void userController::payInterest(void){
	int i = 0;
	for(i=0;i<usercount;i++)
	users[i]->deposite(users[i]->getBalance()*interest_rate);
}
void help() {
  cout << "Welcome to Alipay Managament System" << endl;
  cout << "Please select your service using the number:" << endl;
  cout << "[1] Create an user" << endl;
  cout << "[2] Get an user's info by username" << endl;
  cout << "[3] Get total user count" << endl;
  cout << "[4] Remove one user" << endl;
  cout << "[5] Set interest" << endl;
  cout << "[6] Pay interest" << endl;
  cout << "[7] withdraw(for one account)" << endl;
  cout << "[8] deposite(for one account)" << endl;
  cout << "[9] Display help info" << endl;
  cout << "[0] Quit" << endl;
}
int main() {
  help();
  Alipay3::userController controller(0.005);
  while (true) {
    cout << "Alipay $ ";
    int choose;
    cin >> choose;
    switch (choose) {
      case 1:
        if (true) {
          char username[21];
          char password[21];
          cout << "please input [username] [password]" << endl;
          cin >> username >> password;
          if (controller.createUser(username, password)) {
            cout << "create user successfully!" << endl;
          } else {
            cout << "fail to create user with username:" << username
                 << " password:" << password << endl;
          }
          break;
        }
      case 2:
        if (true) {
          char username[21];
          cout << "please input username" << endl;
          cin >> username;
          cout << "user info:" << endl;
          cout << controller.getUserInfoByName(username) << endl;
          break;
        }
      case 3:
        cout << "Total user count: " << controller.getUserCount() << endl;
        break;
      case 4:
        if (true) {
          char username[21];
          cout << "please input username" << endl;
          cin >> username;
          if (controller.removeUserByUsername(username)) {
            cout << "remove user successfully!" << endl;
          } else {
            cout << "fail to reomove user with username:" << username << endl;
          }
          break;
        }
      case 5:
        if (true) {
          double newRate;
          cout << "please input the new interest rate:" << endl;
          cin >> newRate;
          if (controller.setInterest(newRate)) {
            cout << "set interest successfully" << endl;
          } else {
            cout << "set interest falied with interest rate:" << newRate
                 << endl;
          }
          break;
        }
      case 6:
        if (true) {
          controller.payInterest();
          cout << "pay interest compelete" << endl;
          break;
        }
      case 7:
        if (true) {
          cout << "please input [username] [withdraw_amount]" << endl;
          char username[21];
          double amount;
          cin >> username >> amount;
          if (controller.withdraw(username, amount)) {
            cout << "withdraw successfully!" << endl;
          } else {
            cout << "withdraw falied with amount:" << amount << endl;
          }
          break;
        }
      case 8:
        if (true) {
          cout << "please input [username] [deposite_amount]" << endl;
          char username[21];
          double amount;
          cin >> username >> amount;
          if (controller.deposite(username, amount)) {
            cout << "deposite successfully!" << endl;
          } else {
            cout << "deposite falied with amount:" << amount << endl;
          }
          break;
        }
      case 0:
        cout << "Tanks for using Alipay, Bye!" << endl;
        return 0;
      case 9:
        help();
        break;
      default:
        cout << "No suchu command! Please input again" << endl;
        help();
    }
  }
 
return 0;
}
 
