#ifndef AGENDASERVICE_H 
#define AGENDASERVICE_H 
 
#include "Storage.h" 
#include <list> 
#include <string> 
using std::string;
using std::list;

class AgendaService { 
public: 
  AgendaService(){
  	storage_ = new Storage;
  }
  ~AgendaService(){
  	if(storage_!=NULL) delete storage_;
  	storage_ = NULL;
  }
  bool userLogIn(string userName, string password); 
  bool userRegister(string userName, string password, 
                     string email, string phone){

  }
  bool deleteUser(string userName, string password); 
	// a user can only delete itself 
  list<User> listAllUsers(void){
  }

 
  bool createMeeting(string userName, string title, 
                    string participator, 
                     string startDate, string endDate); 
  list<Meeting> meetingQuery(string userName, string title); 
  list<Meeting> meetingQuery(string userName, string startDate, 
                                  string endDate); 
  list<Meeting> listAllMeetings(string userName); 
  list<Meeting> listAllSponsorMeetings(sstring userName); 
  list<Meeting> listAllParticipateMeetings(string userName); 
  bool deleteMeeting(string userName, string title); 
  bool deleteAllMeetings(tring userName); 

 
  void startAgenda(void); 
  void quitAgenda(void); 

 
private: 
  Storage *storage_; 
}; 

 
#endif 