#include "Account.h"
#include <string>
#include <cstdio>
int Account::_total_account = 0;
Account::Account() {
	_id = _balance = 0;
	_valid = false;
	_total_account++;
}
Account::~Account() {
	_total_account--;
}
int Account::id() const {
	return _id;
}
double Account::balance() const {
	return _balance;
}
bool Account::valid() const {
	return _valid;
}
std::string Account::profile() const {
	std::string str;
	str += "ID:";
	char arr[20] = { 0 };
	snprintf(arr, sizeof(arr), "%d", _id);
	str += arr;
	str += "\nBALANCE:";
	snprintf(arr, sizeof(arr), "%.6lf", _balance);
	str += arr;
	str += "\nVALID:N\n";
	return str;
}
void Account::reset() {
	_balance = 0;
}
bool Account::deposit(const double &num) {
	if (num<0) return 0;
	_balance += num;
	return 1;
}
bool Account::draw(const double &num) {
	double count = _balance - num;
	if (num<0 || count<0.01) return 0;
	_balance -= num;
	return 1;
}
int Account::get_total_account() {
	return _total_account;
}