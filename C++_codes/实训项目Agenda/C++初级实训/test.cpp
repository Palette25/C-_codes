#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(){
	ifstream file_in("agenda.data");
    if(!file_in.is_open())
    	return 0;
    int user_num = 3;
    int meeting_num = 3;
    string data;
    file_in >> data;
    string name, pass, email, phone;
    int loc1, loc2, loc3, loc_end;
    for(int i=0;i<user_num;i++){
    	file_in >> data;
    	loc1 = data.find("password:\"");
        loc2 = data.find("email:\"");
        loc3 = data.find("phone:\"");
        loc_end = data.find("\"}");
        name = data.substr(7, loc1-9);
        pass = data.substr(loc1+10, loc2-loc1-12);
        email = data.substr(loc2+7, loc3-loc2-9);
        phone = data.substr(loc3+7, loc_end-loc3-7);
        cout << name << endl;
        cout << pass << endl;
        cout << email << endl;
        cout << phone << endl;
    }
    file_in >> data;
    for(int i=0;i<meeting_num;i++){
    	file_in >> data;
    	cout << data << endl;
    }
    return 0;
}