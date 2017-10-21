#ifndef STORAGE_H 
#define STORAGE_H 
 
 
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&) 

 
#include <list> 
#include <string> 
#include <functional> 
#include <fstream>
#include <sstream>

#include "User.h" 
#include "Meeting.h" 
using std::list;
class Storage { 
   private: 
     static Storage *instance_; 
     DISALLOW_COPY_AND_ASSIGN(Storage); 
     Storage(){
     	readFromFile("agenda.data");
     } 
     // storage structure with list, or you have better structures 
     // e.g. balanced tree 
    list<User> userList_; 
    list<Meeting> meetingList_; 
     // File IO 
    bool readFromFile(const char *fpath){
    	ifstream file_in(fpath);
    	if(!file_in.is_open())
    		return 0;
    	int user_num = 0;
    	int meeting_num = 0;
    	string temp;
        file_in >> temp;
        temp = temp.substr(24, 1);
    	user_num = temp[0] - '0';
    	for(int i=0;i<user_num;;i++){
    		file_in >> temp;
    		userList_.push_back(Data_to_User(temp));
    	}
    	file_in >> temp;
    	temp = temp.substr(27, 1);
    	meeting_num = temp[0] - '0';
    	for(int i=0;i<meeting_num;;i++){
    		file_in >> temp;
    		meetingList_.push_back(Data_to_Meeting(temp));
    	}
    	return 1;
	}
    bool writeToFile(const char *fpath){
    	ofstream file_out(fpath);
    	if(!file_out.is_open())
    		return 0;
    	file_out << "{colletion:\"User\",total:" << userList_.size() << "}\n";
    	list<User>::iterator u_iter;
    	for(u_iter=userList_.begin();u_iter!=userList_.end();u_iter++)
    		file_out << User_to_Data(*u_iter);
    	file_out << "{colletion:\"Meeting\",total:" << meetingList_.size() << "}\n";
    	list<Meeting>::iterator m_iter;
    	for(m_iter=userList_.begin();m_iter!=userList_.end();m_iter++)
    		file_out << Meeting_to_Data(*m_iter);
    	return 1;
    }
    User Data_to_User(string data){
    	string name, pass, email, phone;
    	int loc1 = data.find("password:\"");
    	int loc2 = data.find("email:\"");
    	int loc3 = data.find("phone:\"");
    	int loc_end = data.find("\"}");
    	name = data.substr(7, loc1-9);
    	pass = data.substr(loc1+10, loc2-loc1-12);
    	email = data.substr(loc2+7, loc3-loc2-9);
    	phone = data.substr(loc3+7, loc_end-loc3-7);
    	return User(name, pass, email, phone);
    }
    Meeting Data_to_Meeting(string data){
    	string spo, par, title, sdate, edate;
    	int loc1 = data.find("partipator:\"");
    	int loc2 = data.find("sdate:\"");
    	int loc3 = data.find("edate:\"");
    	int loc4 = data.find("title:\"");
    	int loc_end = data.find("\"}");
    	spo = data.substr(10, loc1-12);
    	par = data.substr(loc1+12, loc2-loc1-14);
    	sdate = data.substr(loc2+7, loc3-loc2-9);
    	edate = data.substr(loc3+7, loc4-loc3-9);
    	title = data.substr(loc4+7, loc_end-loc4-7);
        return Meeting(spo, par, Date::stringtoDate(sdate), Date::stringtoDate(edate), title);
    }
    string User_to_Data(User& user){
    	string result;
    	stringstream ss;
    	ss << "{name:\"" << user.getName() << "\",password:\"" << user.getPassword() << "\",email:\""
    	   << user.getEmail() << "\",phone:\"" << user.getPhone() << "\"}\n";
    	ss >> result;
    	return result; 
    }
    string Meeting_to_Data(Meeting& meeting){
    	string result;
    	stringstream ss;
    	ss << "{sponsor:\"" << meeting.getSponsor() << "\",partipator:\"" << meeting.getParticipator() << "\",sdate:\""
    	   << meeting.getStartDate() << "\",edate:\"" << meeting.getEndDate() << "\",title:\"" << meeting.getTitle() 
    	   << "\"}\n";
    	ss >> result;
    	return result; 
    }
   public: 
     // singleton 
    static Storage *getInstance(void){
    	if(instance_==NULL) instance_ = new Storage;
    	return instance_;
    } 
     ~Storage(){}
     // CRUD for User & Meeting 
    // using C++11 Function Template and Lambda Expressions 
    void createUser(const User& user){
    	userList_.push_back(user);
    }
    list<User> queryUser(std::function<bool(const User&)> filter){
    	list<User> result;
    	list<User>::iterator iter;
        for (iter = userList_.begin(); iter != userList_.end(); iter++)
        	if(filter(*iter)) result.push_back(*iter);
        return result;
    }
    int updateUser(std::function<bool(const User&)> filter, 
        std::function<void(User&)> switcher){
    	int num = 0;
    	list<User>::iterator iter;
    	for(iter = userList_.begin();iter != userList_.end();iter++){
    		if(filter(*iter)) {
    			num++;
    			switcher(*iter);
    		}
    	}
    	return num;
    }
    int deleteUser(std::function<bool(const User&)> filter){
        int num = 0;
    	list<User>::iterator iter;
        for (iter = userList_.begin(); iter != userList_.end(); iter++)
        	if(filter(*iter)) {
        		userList_.erase(*iter);
        		num++;
        	}
        return num;
    }
    void createMeeting(const Meeting& meet){
    	meetingList_.push_back(meet);
    }
    list<Meeting> queryMeeting(std::function<bool(const Meeting&)> filter){
    	list<Meeting> result;
    	list<Meeting>::iterator iter;
        for (iter = meetingList_.begin(); iter != meetingList_.end(); iter++)
        	if(filter(*iter)) result.push_back(*iter);
        return result;
    } 
    int updateMeeting(std::function<bool(const Meeting&)> filter, 
         std::function<void(Meeting&)> switcher){
    	int num = 0;
    	list<Meeting>::iterator iter;
    	for(iter = meetingList_.begin();iter != meetingList_.end();iter++){
    		if(filter(*iter)) {
    			num++;
    			switcher(*iter);
    		}
    	}
    	return num;
    }
    int deleteMeeting(std::function<bool(const Meeting&)> filter){
    	int num = 0;
    	list<Meeting>::iterator iter;
        for (iter = meetingList_.begin(); iter != meetingList_.end(); iter++)
        	if(filter(*iter)) {
        		meetingList_.erase(*iter);
        		num++;
        	}
        return num;
    }
    bool sync(void){
    	return writeToFile("agenda.data")
    }
}; 
Storage* Storage::instance_ = NULL;
#endif 
