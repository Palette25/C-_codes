#include "Mediator.hpp"
Mediator* Mediator::Ins = NULL;
User* iter(const int & to, std::list<User*> list1){
	int time = to;
	list<User*>::iterator temp = list1.begin();
	while(time--){
		temp++;
	}
	User* temp1 = *temp;
	return temp1;
}
void Mediator::RegisterHandler(User * u){
	users.push_back(u);
}
void Mediator::ChatHandler(const int & to, const string & msg){
    if(to > users.size()-1) cout << "Are you kidding ? There is no such a guy!" << endl;
	else iter(to, users)->GetMessage(msg);
}
pair<int,string> Mediator::TradeHandler(const int & to, const int & pay, const string & dressName){
	User* now = iter(to, users);
	pair<int, string>result = (now->SellBeautifulDress(pay, dressName));
	if(result.second=="fail1") return pair<int, string>(-1, "fail1");
	else {
		if (result.second == "fail2") return pair<int, string>(-1, "fail2");
		else return pair<int, string>(result.first, dressName);
	}
}
void Mediator::DressInfoHandler(const int & to){
	iter(to, users)->ShowMyCuteDresses();
}