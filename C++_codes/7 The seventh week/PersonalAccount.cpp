#include "PersonalAccount.h"
#include <string>
#include <cstdio>
int PersonalAccount::_total_per_account = 0;
int PersonalAccount::_acc_id_ptr = 12010000;
PersonalAccount::PersonalAccount() {
	_id = _acc_id_ptr;
	_balance = 10;
	_valid = true;
	_acc_id_ptr++;
	_total_per_account++;
}
PersonalAccount::~PersonalAccount() {
	_total_per_account--;
}
std::string PersonalAccount::profile() const {
	std::string str;
	str += "ID:";
	char arr[20] = { 0 };
	snprintf(arr, sizeof(arr), "%d", _id);
	str += arr;
	str += "\nBALANCE:";
	snprintf(arr, sizeof(arr), "%.6lf", _balance);
	str += arr;
	str += "\nVALID:Y\nTYPE:PERSONAL\n";
	return str;
}
void PersonalAccount::reset() {
	_balance = 10;
	_valid = true;
}
int PersonalAccount::get_total_per_account() {
	return _total_per_account;
}