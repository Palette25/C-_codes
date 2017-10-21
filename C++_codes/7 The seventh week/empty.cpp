#include <iostream>
#include <string>
#include <cstdio>
class Account {
  protected:
    int _id;
    double _balance;
    bool _valid;
    static int _total_account;
  public:
    Account();
    ~Account();
    int id() const;
    double balance() const;
    bool valid() const;
    std::string profile() const;
    void reset();
    bool deposit(const double &num);
    bool draw(const double &num);
    static int get_total_account();
};
int Account::_total_account = 0;
Account::Account(){
	_id = _balance = 0;
	_valid = false;
	_total_account++; 
}
Account::~Account(){
	_total_account--;
}
int Account::id() const{
	return _id;
}
double Account::balance() const{
	return _balance;
}
bool Account::valid() const{
	return _valid;
}
std::string Account::profile() const{
	std::string str;
	char arr[100];
	snprintf(arr, 100, "ID:%d\nBALANCE:%.6lf\nVALID:N\n", _id, _balance);
	str += arr;
	return str;
}
void Account::reset(){
	_balance = 0;
}
bool Account::deposit(const double &num){
	if(num<0) return 0;
	_balance += num;
	return 1;
}
bool Account::draw(const double &num){
	double count = _balance - num;
	if(num<0||count<0.01) return 0;
	_balance -= num;
	return 1;
}
int Account::get_total_account(){
	return _total_account;
}

class PersonalAccount : public Account {
  private:
    static int _total_per_account;
    static int _acc_id_ptr;
  public:
    PersonalAccount();
    ~PersonalAccount();
    // override
    std::string profile() const;
    void reset();
    // static
    static int get_total_per_account();
};
int PersonalAccount::_total_per_account = 0;
int PersonalAccount::_acc_id_ptr = 12010000;
PersonalAccount::PersonalAccount(){
	_id = _acc_id_ptr;
	_balance = 10;
	_valid = true;
	_acc_id_ptr++;
	_total_per_account++;
}
PersonalAccount::~PersonalAccount(){
	_total_per_account--;
}
std::string PersonalAccount::profile() const{
	std::string str;
	char arr[100];
	snprintf(arr, 100, "ID:%d\nBALANCE:%.6lf\nVALID:Y\nTYPE:PERSONAL\n", _id, _balance);
	str += arr;
	return str;
}
void PersonalAccount::reset(){
	_balance = 10;
	_valid = true;
}
int PersonalAccount::get_total_per_account(){
	return _total_per_account;
}

class VIPAccount : public Account {
  private:
    static int _total_vip_account;
    static int _acc_id_ptr;
  protected:
    double _loan;
    double _loan_limit;  // initial as 1k
  public:
    VIPAccount();
    ~VIPAccount();
    bool loan(const double &num);
    bool repay(const double &num);
    // override
    std::string profile() const;
    void reset();
    // static
    static int get_total_vip_account();
};
int VIPAccount::_total_vip_account = 0;
int VIPAccount::_acc_id_ptr = 12050000;
VIPAccount::VIPAccount(){
	_id = _acc_id_ptr;
	_balance = 10;
	_valid = true;
	_loan_limit = 1000;
	_total_vip_account++;
	_acc_id_ptr++;
}
VIPAccount::~VIPAccount(){
	_total_vip_account--;
}
bool VIPAccount::loan(const double &num){
	if(_loan+num>1000) return 0;
	_loan += num;
	_balance += num;
	return 1;
}
bool VIPAccount::repay(const double &num) {
	if (_balance < num) return 0;
	if(num<=_loan){
	_balance -= num;
	_loan -= num;
}
    else if(num>_loan){
    	_balance -= _loan;
    	_loan = 0;
    }
	return 1;
}
std::string VIPAccount::profile() const{
	std::string str;
	char arr[100];
	snprintf(arr, 100, "ID:%d\nBALANCE:%.6lf\nVALID:Y\nTYPE:VIP\nLOAN:%.6lf,LIMIT:%.6lf\n", _id, _balance, _loan, _loan_limit);
	str += arr;
	return str;
}
void VIPAccount::reset(){
    _balance = 10;
    _valid = true;
    _loan = 0;
}
int VIPAccount::get_total_vip_account(){
	return _total_vip_account;
}

using namespace std;
 
void display_count() {
  cout << Account::get_total_account() << ",";
  cout << PersonalAccount::get_total_per_account() << ",";
  cout << VIPAccount::get_total_vip_account() << endl;
}
int main() {
  display_count();
  if (true) {
    Account a0, a1, a2;
    display_count();
    PersonalAccount b0, b1;
    display_count();
  }
  VIPAccount c0, c1, c2, c3;
  display_count();
 
  Account *bptr = new Account();
  cout << bptr->profile() << endl;
  cout << bptr->id() << bptr->balance() << bptr->valid() << endl;
  delete bptr;
 
  PersonalAccount *pptr = new PersonalAccount();
  cout << pptr->profile() << endl;
  for (int i = 0; i < 5; ++i) {
    double t;
    int op;
    cin >> op >> t;
    if (op < 5) {
      cout << pptr->deposit(t) << ", ";
    } else {
      cout << pptr->draw(t) << ", ";
    }
    cout << pptr->balance() << endl;
  }
  cout << pptr->profile() << endl;
  pptr->reset();
  cout << pptr->profile() << endl;
  delete pptr;
 
  VIPAccount *vptr = new VIPAccount();
  cout << vptr->profile() << endl;
  for (int i = 0; i < 5; ++i) {
    double t;
    int op;
    cin >> op >> t;
    if (op < 5) {
      cout << vptr->loan(t);
    } else {
      cout << vptr->repay(t);
    }
    cout << "\n" << vptr->profile() << endl;
  }
  vptr->reset();
  cout << vptr->profile() << endl;
  delete vptr;
 
  return 0;
}
