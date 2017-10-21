#include "VIPAccount.h"
#include <string>
#include <cstdio>
int VIPAccount::_total_vip_account = 0;
int VIPAccount::_acc_id_ptr = 12050000;
VIPAccount::VIPAccount() {
	_id = _acc_id_ptr;
	_balance = 10;
	_valid = true;
	_loan_limit = 1000;
	_total_vip_account++;
	_acc_id_ptr++;
}
VIPAccount::~VIPAccount() {
	_total_vip_account--;
}
bool VIPAccount::loan(const double &num) {
	if (_loan + num>1000) return 0;
	_loan += num;
	_balance += num;
	return 1;
}
bool VIPAccount::repay(const double &num) {
	if (_balance < num) return 0;
	if (num <= _loan) {
		_balance -= num;
		_loan -= num;
	}
	else if (num>_loan) {
		_balance -= _loan;
		_loan = 0;
	}
	return 1;
}
std::string VIPAccount::profile() const {
	std::string str;
	str += "ID:";
	char arr[20] = { 0 };
	snprintf(arr, sizeof(arr), "%d", _id);
	str += arr;
	str += "\nBALANCE:";
	snprintf(arr, sizeof(arr), "%.6lf", _balance);
	str += arr;
	str += "\nVALID:Y\nTYPE:VIP\nLOAN:";
	snprintf(arr, sizeof(arr), "%.6lf", _loan);
	str += arr;
	str += ",LIMIT:";
	snprintf(arr, sizeof(arr), "%.6lf", _loan_limit);
	str += arr;
	str += '\n';
	return str;
}
void VIPAccount::reset() {
	_balance = 10;
	_valid = true;
	_loan = 0;
}
int VIPAccount::get_total_vip_account() {
	return _total_vip_account;
}