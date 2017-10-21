#include "User.hpp"
#include "Mediator.hpp"
#include <iostream>
#include <string>
using std::string;
int User::Count = 0;
User::User(const string & name_, const int & money_, const vector<pair<string, int> > & dresses_){
	name = name_;
	money = money_;
	id = Count;
	for (int i = 0; i < dresses_.size(); i++)
		dresses.push_back(Dress(dresses_[i].first, dresses_[i].second));
	Count++;
}
void User::BuyBeautifulDress(const int & id, const int & pay, const string & name_) {
	if (pay > money) {
		cout << name << " : " << "Forget to Check Wallet!" << endl;
		return;
	}
	else {
		pair<int, string> result = Mediator::getInstance()->TradeHandler(id, pay, name_);
		if (result.second == "fail1") cout << name << " : " << "I'm so sorry maybe just because I love it so much." << endl;
		else if (result.second == "fail2") cout << name << " : " << "OMG! Why it is so Expensive!" << endl;
		else {
			cout << name << " : " << "So happy to get new Dress!" << endl;
			dresses.push_back(Dress(result.second, result.first));
			money -= pay;
		}
	}
}
void User::GetDressInfo(const int & id){
	cout << name << " : " << "I wanna see your beautiful suits!" << endl;
	Mediator::getInstance()-> DressInfoHandler(id);
}
pair<int, string> User::SellBeautifulDress(const int & pay, const string & dname){
	int flag = 0, i = 0;
	for(i=0;i<dresses.size();i++)
		if(dresses[i].getName()==dname) {
			flag = 1;
			break;
        }
    if(flag==0) {
    	cout << name <<" : " << "I never have this Dress stupid!" << endl;
    	return pair<int, string>(-1, "fail1");
    }
    else if(pay<dresses[i].getPrice()) {
    	cout << name << " : " <<  "No monry then no talking" << endl; 
    	return pair<int, string>(-1, "fail2");
    }
    else {
    	cout << name << " : " << "What a good taste you have !" << endl;
		dresses.erase(dresses.begin() + i);
		money += pay;
    	return pair<int, string>(dresses[i].getPrice(), dname);
    }

}
void User::SendMessage(const int & to, const string & msg){
	Mediator::getInstance()-> ChatHandler(to, msg);
}
void User::GetMessage(const string & msg){
	cout << name << " : I got a Msg - " << msg << endl;
}
void User::ShowMyCuteDresses(){
	cout << name << " : ok,these are all I have : " << endl;
	for(int i=0;i<dresses.size();i++)
		cout << dresses[i].getName() << "-" << dresses[i].getPrice() << endl;
}