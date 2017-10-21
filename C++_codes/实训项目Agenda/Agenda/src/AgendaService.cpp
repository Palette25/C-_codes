#include "AgendaService.hpp"
using namespace std;
#include <iostream>

AgendaService::AgendaService(){
	startAgenda();
}
AgendaService::~AgendaService(){
	quitAgenda();
}
bool AgendaService::userLogIn(const std::string &userName, const std::string &password){
	auto filter = [userName, password](const User& user){
		return (user.getName()==userName&&user.getPassword()==password);
	};
	if(m_storage->queryUser(filter).size()==0) return 0;
	else return 1;
}
bool AgendaService::userRegister(const std::string &userName, const std::string &password,
                    const std::string &email, const std::string &phone){
	auto filter = [userName, password, email, phone](const User& user){
		return (userName==user.getName());
	};
	if(m_storage->queryUser(filter).size()>0) return 0;
	User new_user(userName, password, email, phone);
	m_storage->createUser(new_user);
	return 1;
}
bool AgendaService::deleteUser(const std::string &userName, const std::string &password){
	auto filter = [userName, password](const User& user){
		return user.getName()==userName&&user.getPassword()==password;
	};
	if(m_storage->deleteUser(filter)==0) return 0;
	auto filter1 = [userName](const Meeting& meet){return meet.getSponsor()==userName;};
	m_storage->deleteMeeting(filter1);
	auto filter2 = [userName](const Meeting& meet){return meet.isParticipator(userName);};
	auto filter3 = [userName](Meeting& meet){meet.removeParticipator(userName);};
	m_storage->updateMeeting(filter2, filter3);
	auto filter4 = [](const Meeting& meet){return meet.getParticipator().size()==0;};
	m_storage->deleteMeeting(filter4);
	return 1;
}
std::list<User> AgendaService::listAllUsers(void) const{
	auto filter = [](const User& user){return 1;};
	return m_storage->queryUser(filter);
}
bool Valid_creating(const string& startDate, const string& endDate, const Meeting& meet){
	Date date1 = Date::stringToDate(startDate);
	Date date2 = Date::stringToDate(endDate);
	if((date1>=meet.getEndDate()&&date2>meet.getEndDate())
		||(date1<meet.getStartDate()&&date2<=meet.getStartDate()))
		return 1;
	else return 0;
}
bool AgendaService::createMeeting(const std::string &userName, const std::string &title,
                     const std::string &startDate, const std::string &endDate,
                     const std::vector<std::string> &participator){
	auto filter = [userName](const User& user){
		return user.getName()==userName;
	};
	if(m_storage->queryUser(filter).size()!=1) return 0;
	for(auto i:participator){
		if(i==userName) return 0;
	}
	Date date1 = Date::stringToDate(startDate);
	Date date2 = Date::stringToDate(endDate);
	if(!Date::isValid(date1)||!Date::isValid(date2)||date1>=date2||participator.size()==0) return 0;
	list<Meeting> list1 = listAllMeetings(userName);
	for(auto i:list1){
		if(!Valid_creating(startDate, endDate, i)) return 0;
	}
	list<Meeting> list2;
	for(auto i:participator){
		list2 = listAllMeetings(i);
		for(auto j:list2){
			if(!Valid_creating(startDate, endDate, j)) return 0;
		}
	}
	auto filter1 = [title](const Meeting& meet){
		return meet.getTitle()==title;
	};
	if(m_storage->queryMeeting(filter1).size()>0) return 0;
	auto filter2 = [participator](const User& user){
		for(auto i:participator){
			if(i==user.getName()) return 1;
		}
		return 0;
	};
	if(m_storage->queryUser(filter2).size()!=participator.size()) return 0;
	m_storage->createMeeting(Meeting(userName, participator, date1, date2, title));
	return 1;
}
bool AgendaService::addMeetingParticipator(const std::string &userName,
                              const std::string &title,
                              const std::string &participator){
	int flag = 0;
	if(userName==participator) return 0;
	for(auto i:listAllUsers()){
		if(i.getName()==participator) flag = 1;
	}
	if(flag==0) return 0;
	auto filter0 = [userName, title](const Meeting& meet){
		return meet.getTitle()==title&&meet.getSponsor()==userName;
	};
	list<Meeting> list1 = listAllMeetings(participator);
	list<Meeting> list2 = m_storage->queryMeeting(filter0);
	if(list2.size()==0) return 0;
	Meeting temp = list2.front();
	string start = Date::dateToString(temp.getStartDate()), end = Date::dateToString(temp.getEndDate());
	for(auto i:list1){
		if(!Valid_creating(start, end, i)) return 0;
	}
	auto filter = [userName, title, participator](const Meeting& meet){
		return meet.getSponsor()==userName&&meet.getTitle()==title&&
				meet.isParticipator(participator);
	};
	if(m_storage->queryMeeting(filter).size()>0) return 0;
	auto filter1 = [userName, title](const Meeting& meet){
		return meet.getSponsor()==userName&&meet.getTitle()==title;
	};
	auto filter2 = [participator](Meeting& meet){
		meet.addParticipator(participator);
	};
	if(m_storage->updateMeeting(filter1, filter2)>0) return 1;
	else return 0;
}
bool AgendaService::removeMeetingParticipator(const std::string &userName,
                                 const std::string &title,
                                 const std::string &participator){
	auto filter1 = [userName, title, participator](const Meeting& meet){
		for(auto i:meet.getParticipator()){
			if(i==participator){
				if(userName==meet.getSponsor()&&title==meet.getTitle())
					return 1;
			}
		}
		return 0;
	};
	auto filter2 = [participator](Meeting& meet){
		meet.removeParticipator(participator);
	};
	auto filter3 = [](const Meeting& meet){
		if(meet.getParticipator().size()==0)
			return 1;
		else return 0;
	};
	if(m_storage->updateMeeting(filter1, filter2)>0) {
		m_storage->deleteMeeting(filter3);
		return 1;
	}
	else return 0;
}

bool AgendaService::quitMeeting(const std::string &userName, const std::string &title){
	auto filter1 = [userName, title](const Meeting& meet){
		for(auto i:meet.getParticipator()){
			if(i==userName&&meet.getTitle()==title) return 1;
		}
		return 0;
	};
	auto filter2 = [userName](Meeting& meet){
		meet.removeParticipator(userName);
	};
	auto filter3 = [](const Meeting& meet){
		if(meet.getParticipator().size()==0)
			return 1;
		else return 0;
	};
	if(m_storage->updateMeeting(filter1, filter2)>0) {
		m_storage->deleteMeeting(filter3);
		return 1;
	}
	else {
		m_storage->deleteMeeting(filter3);
		return 0;
	}
}
std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                                  const std::string &title) const{
	auto filter = [userName, title](const Meeting& meet){
		return (meet.getSponsor()==userName||meet.isParticipator(userName))&&meet.getTitle()==title;
	};
	return m_storage->queryMeeting(filter);
}
std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                                  const std::string &startDate,
                                  const std::string &endDate) const{
	Date date1 = Date::stringToDate(startDate);
	Date date2 = Date::stringToDate(endDate);
	list<Meeting> result;
	if(!Date::isValid(date1)||!Date::isValid(date2)||date1>date2) return result;
	auto filter = [userName, date1, date2](const Meeting& meet){
		if(userName==meet.getSponsor()||meet.isParticipator(userName)){
			if(meet.getStartDate()<=date1){
				if(meet.getEndDate()>=date1) return 1;
			}
			if(meet.getStartDate()>=date1){
				if(meet.getStartDate()<=date2) return 1;
			}
		}
		return 0;
	};
	return m_storage->queryMeeting(filter);
}
std::list<Meeting> AgendaService::listAllMeetings(const std::string &userName) const{
	auto filter = [userName](const Meeting& meet){
		if(meet.getSponsor()==userName) return 1;
		for(auto i:meet.getParticipator()){
			if(i==userName) return 1;
		}
		return 0;
	};
	return m_storage->queryMeeting(filter);
}
std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string &userName) const{
	auto filter = [userName](const Meeting& meet){
		return meet.getSponsor()==userName;
	};
	return m_storage->queryMeeting(filter);
}
std::list<Meeting> AgendaService::listAllParticipateMeetings(
     const std::string &userName) const{
	auto filter = [userName](const Meeting& meet){
		for(auto i:meet.getParticipator()){
			if(i==userName) return 1;
		}
		return 0;
	};
	return m_storage->queryMeeting(filter);
}
bool AgendaService::deleteMeeting(const std::string &userName, const std::string &title){
	auto filter = [userName, title](const Meeting& meet){
		return (meet.getSponsor()==userName&&meet.getTitle()==title);
	};
	if(m_storage->deleteMeeting(filter)>0) return 1;
	else return 0;
}
bool AgendaService::deleteAllMeetings(const std::string &userName){
	auto filter = [userName](const Meeting& meet){
		if(meet.getSponsor()==userName) return 1;
	};
	if(m_storage->deleteMeeting(filter)>0) return 1;
	else return 0;
}
void AgendaService::startAgenda(void){
	m_storage = Storage::getInstance();
}
void AgendaService::quitAgenda(void){
	m_storage->sync();
}
