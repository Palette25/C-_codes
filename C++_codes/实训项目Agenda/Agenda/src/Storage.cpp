#include "../include/Storage.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "../include/Path.hpp"
using namespace std;
std::shared_ptr<Storage> Storage::m_instance = NULL;
Storage::Storage(){
  readFromFile();
}

User Data_To_User(string temp){
  string name, pass, email, phone;
  int loc1 = temp.find("\",\"", 0);
  int loc2 = temp.find("\",\"", loc1+1);
  int loc3 = temp.find("\",\"", loc2+1);
  name = temp.substr(1, loc1-1);
  pass = temp.substr(loc1+3, loc2-loc1-3);
  email = temp.substr(loc2+3, loc3-loc2-3);
  phone = temp.substr(loc3+3, temp.size()-loc3-4);
  return User(name, pass, email, phone);
}
Meeting Data_To_Meeting(string temp){
  string spo, start, end, title, pa;
  vector<string> participator;
  int loc1 = temp.find("\",\"", 0);
  int loc2 = temp.find("\",\"", loc1+1);
  int loc3 = temp.find("\",\"", loc2+1);
  int loc4 = temp.find("\",\"", loc3+1);
  spo = temp.substr(1, loc1-1);
  pa = temp.substr(loc1+3, loc2-loc1-2);
  start = temp.substr(loc2+3, loc3-loc2-3);
  end = temp.substr(loc3+3, loc4-loc3-3);
  title = temp.substr(loc4+3, temp.size()-loc4-4);
  string str;
  for(auto i:pa){
  	if(i=='\"') participator.push_back(str);
  	if(i!='&') str += i;
  	else {
  		participator.push_back(str);
  		str = "";
  	}
  }
  return Meeting(spo, participator, Date(start), Date(end), title);
}
bool Storage::readFromFile(void){
	ifstream file_user(Path::userPath);
  if(!file_user.is_open())
    return 0;
  string temp;
  while(getline(file_user, temp)){
  	m_userList.push_back(Data_To_User(temp));
  }
  file_user.close();
  ifstream file_meet(Path::meetingPath);
  if(!file_meet.is_open())
    return 0;
  while(getline(file_meet, temp)){
  	m_meetingList.push_back(Data_To_Meeting(temp));
  }
  file_meet.close();
  return 1;
}
string User_To_Data(User& user, int flag){
	stringstream result;
	result << '\"' << user.getName() << "\",\"" << user.getPassword()
	       << "\",\"" << user.getEmail() << "\",\"" << user.getPhone()
	       << '\"';
	if(flag==0) result << '\n';
	return result.str();
}
string Meeting_To_Data(Meeting& meet, int flag){
	stringstream result;
	result << '\"' << meet.getSponsor() << "\",\"";
	for(int i=0;i<meet.getParticipator().size();i++){
		result << meet.getParticipator()[i];
		if(i!=meet.getParticipator().size()-1)  result << '&';
		else result << "\",\"";
	}
	result << Date::dateToString(meet.getStartDate()) << "\",\""
	       << Date::dateToString(meet.getEndDate()) << "\",\""
	       << meet.getTitle() << '\"';
	if(flag==0) result << '\n';
	return result.str();
}
bool Storage::writeToFile(void){
	ofstream file_user(Path::userPath);
	if(!file_user.is_open())
		return 0;
	list<User>::iterator iter;
	list<User>::iterator end1;
	for(iter=m_userList.begin();iter!=m_userList.end();iter++){
		end1 = m_userList.end();
		if(iter!=--end1) file_user << User_To_Data(*iter, 0);
		else file_user << User_To_Data(*iter, 1);
	}
	file_user.close();
	ofstream file_meet(Path::meetingPath);
	if(!file_meet.is_open())
		return 0;
	list<Meeting>::iterator it;
	list<Meeting>::iterator end2;
	for(it=m_meetingList.begin();it!=m_meetingList.end();it++){
		end2 = m_meetingList.end();
		if(it!=--end2) file_meet << Meeting_To_Data(*it, 0);
		else file_meet << Meeting_To_Data(*it, 1);
	}
	file_meet.close();
	return 1;
}
std::shared_ptr<Storage> Storage::getInstance(void){
  if(m_instance==NULL) {
  	Storage* temp = new Storage;
  	shared_ptr<Storage> ptr(temp);
  	m_instance = ptr;
  }
  return m_instance;
}

Storage::~Storage(){
	sync();
}

void Storage::createUser(const User &t_user){
  m_userList.push_back(t_user);
  m_dirty = 1;
}
std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const{
  std::list<User> result;
  for(auto iter:m_userList){
    if(filter(iter)) result.push_back(iter);
  }
  return result;
}
int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher){
  int sum = 0;
  for(auto& iter:m_userList){
    if(filter(iter)) {
      switcher(iter);
      sum++;
    }
  }
  m_dirty = 1;
  return sum;
}
int Storage::deleteUser(std::function<bool(const User &)> filter){
  int sum = 0;
  std::list<User>::iterator iter;
  for(iter=m_userList.begin();iter!=m_userList.end();){
    if(filter(*iter)) {
      m_userList.erase(iter++);
      sum++;
    }
    else iter++;
  }
  m_dirty = 1;
  return sum;
}
void Storage::createMeeting(const Meeting &t_meeting){
  m_meetingList.push_back(t_meeting);
  m_dirty = 1;
}

std::list<Meeting> Storage::queryMeeting(
      std::function<bool(const Meeting &)> filter) const{
  std::list<Meeting> result;
  for(auto iter:m_meetingList){
    if(filter(iter)) result.push_back(iter);
  }
  return result;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher){
  int sum = 0;
  for(auto& iter:m_meetingList){
    if(filter(iter)) {
      switcher(iter);
      sum++;
    }
  }
  m_dirty = 1;
  return sum;
}
int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter){
  int sum = 0;
  std::list<Meeting>::iterator iter;
  for(iter=m_meetingList.begin();iter!=m_meetingList.end();){
    if(filter(*iter)) {
      m_meetingList.erase(iter++);
      sum++;
    }
    else iter++;
  }
  m_dirty = 1;
  return sum;
}
bool Storage::sync(void){
	if(m_dirty==1) {
		writeToFile();
		m_dirty = 0;
		return 1;
	}
	return 0;
}

bool delete1(const Meeting& meet){
	if(meet.getSponsor()=="1"||meet.getSponsor()=="9") return 1;
	else return 0;
}
bool delete2(const User& user){
	if(user.getName()=="1"||user.getName()=="a"||user.getName()=="haha") return 1;
	else return 0;
}
