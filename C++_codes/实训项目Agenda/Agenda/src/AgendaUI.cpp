#include "../include/AgendaUI.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

AgendaUI::AgendaUI(){
	startAgenda();
}
void AgendaUI::OperationLoop(void){
	string temp = "";
	while(temp[0]!='q'){
	cout << "-------------------------------------Agenda-------------------------------------" << endl;
	cout << "Action :" << endl;
	cout << "l    - log in Agenda by user name and password\n"
	     << "r    - register an Agenda account\n"
	     << "q    - quit Agenda\n"
	     << "--------------------------------------------------------------------------------\n\n"
	     << "Agenda :~$ ";
	cin >> temp;
	switch(temp[0]){
		case 'l':
			userLogIn();
			break;
		case 'r':
			userRegister();
			break;
		case 'q':
			quitAgenda();
			break;
		default:
			cout << "[Input error] Bad Request!\n" << endl;
			break;
	}
}
}
void AgendaUI::startAgenda(void){
	m_agendaService.startAgenda();
}
std::string AgendaUI::getOperation(){
	string temp = "";
	cout << "-------------------------------------Agenda-------------------------------------\n"
		 << "Action :\n"
		 << "o    - log out Agenda\n"
		 << "dc   - delete Agenda account\n"
		 << "lu   - list all Agenda user\n"
		 << "cm   - create a meeting\n"
		 << "amp  - add meeting participator\n"
		 << "rmp  - remove meeting participator\n"
		 << "rqm  - request to quit meeting\n"
		 << "la   - list all meetings\n"
		 << "las  - list all sponsor meetings\n"
		 << "lap  - list all participator meetings\n"
		 << "qm   - query meeting by title\n"
		 << "qt   - query meeting by time interval\n"
		 << "dm   - delete meeting by title\n"
		 << "da   - delete all meetings\n";
	cout << "--------------------------------------------------------------------------------\n\n";
	cout << "Agenda@" << m_userName << " :~# ";
	cin >> temp;
	return temp;
}
bool AgendaUI::executeOperation(const std::string &t_operation){
	if(t_operation=="o"){
		userLogOut();
		return 0;
	}
	if(t_operation=="dc"){
		deleteUser();
		userLogOut();
		return 0;
	}
	if(t_operation=="lu"){
		listAllUsers();
		return 1;
	}
	if(t_operation=="cm"){
		createMeeting();
		return 1;
	}
	if(t_operation=="amp"){
		addMeetingParticipator();
		return 1;
	}
	if(t_operation=="rmp"){
		removeMeetingParticipator();
		return 1;
	}
	if(t_operation=="rqm"){
		quitMeeting();
		return 1;
	}
	if(t_operation=="la"){
		listAllMeetings();
		return 1;
	}
	if(t_operation=="las"){
		listAllSponsorMeetings();
		return 1;
	}
	if(t_operation=="lap"){
		listAllParticipateMeetings();
		return 1;
	}
	if(t_operation=="qm"){
		queryMeetingByTitle();
		return 1;
	}
	if(t_operation=="qt"){
		queryMeetingByTimeInterval();
		return 1;
	}
	if(t_operation=="dm"){
		deleteMeetingByTitle();
		return 1;
	}
	if(t_operation=="da"){
		deleteAllMeetings();
		return 1;
	}
	else cout << "[Input error] Bad Request!\n" << endl;
	return 1;
}
void AgendaUI::userLogIn(void){
	string username, password;
	cout << "[log in] [username] [password]" << endl;
	cout << "[log in] ";
	cin >> username >> password;
	if(m_agendaService.userLogIn(username, password)){
		m_userName = username;
		m_userPassword = password;
		cout << "[log in] succeed!" << endl;
		cout << endl;
		while(executeOperation(getOperation())){}
	}
	else {
		cout << "[log in] Password error or user doesn't exist" << endl;
	}
	cout << endl;
}
void AgendaUI::userRegister(void){
	string username, password, email, phone;
	cout << "[register] [username] [password] [email] [phone]" << endl;
	cout << "[register] ";
	cin >> username >> password >> email >> phone;
	if(m_agendaService.userRegister(username, password, email, phone)){
		m_userName = username;
		m_userPassword = password;
		cout << "[register] succeed!" << endl;
		cout << endl;
		while(executeOperation(getOperation())){}
	}
	else {
		cout << "[register] This username has been registered!" << endl;
	}
	cout << endl;
}
void AgendaUI::userLogOut(void){
	m_userName = "";
	m_userPassword = "";
}
void AgendaUI::quitAgenda(void){
	m_agendaService.quitAgenda();
}
void AgendaUI::deleteUser(void){
	m_agendaService.deleteUser(m_userName, m_userPassword);
	m_userName = "";
	m_userPassword = "";
	cout << "[delete agenda account] succeed!" <<endl;
	cout << endl;
}
void AgendaUI::listAllUsers(void){
	cout << "[list all users]" << endl;
	cout << endl;
	cout.setf(ios::left);
	cout << setw(20) << "name" << setw(25) << "email" << "phone\n";
	for(auto i:m_agendaService.listAllUsers()){
		cout << setw(20) << i.getName() << setw(25)
			 << i.getEmail() << i.getPhone() << endl;
	}
	cout << endl;
}
void AgendaUI::createMeeting(void){
	vector<string> temp;
	string str = "";
	int num = 0;
	cout << "[create meeting] [the number of participators]" << endl;
	cout << "[create meeting] ";
	cin >> num;
	for(int i=0;i<num;i++){
		cout << "[create meeting] [please enter the participator " << i+1 << " ]\n[create meeting] ";
		cin >> str;
		temp.push_back(str);
	}
	cout << "[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
	string title, start, end;
	cin >> title >> start >> end;
	if(m_agendaService.createMeeting(m_userName, title, start, end, temp)){
		cout << "[create meeting] succeed!" << endl;
	}
	else {
		cout << "[create meeting] Meeting creating fail!" << endl;
	}
	cout << endl;
}
void AgendaUI::addMeetingParticipator(void){
	cout << "[add participator] [meeting title] [participator username]" << endl;
	cout << "[add participator] ";
	string title, name;
	cin >> title >> name;
	if(m_agendaService.addMeetingParticipator(m_userName, title, name)){
		cout << "[add participator] succeed!" << endl;
	}
	else cout << "[add participator] Add participator fail!" << endl;
	cout << endl;
}
void AgendaUI::removeMeetingParticipator(void){
	cout << "[remove participator] [meeting title] [participator username]" << endl;
	cout << "[remove participator] ";
	string title, name;
	cin >> title >> name;
	if(m_agendaService.removeMeetingParticipator(m_userName, title, name)){
		cout << "[remove participator] succeed!" << endl;
	}
	else cout << "[remove participator] Remove participator fail!" << endl;
	cout << endl;
}
void AgendaUI::quitMeeting(void){
	cout << "[quit meeting] [meeting title]" << endl;
	cout << "[quit meeting] " << endl;
	string title;
	cin >> title;
	if(m_agendaService.quitMeeting(m_userName, title)){
		cout << "[quit meeting] succeed!" << endl;
	}
	else {
		cout << "[quit meeting] Quit meeting fail!" << endl;
	}
	cout << endl;
}
void AgendaUI::listAllMeetings(void){
	cout << "[list all meetings]" << endl;
	printMeetings(m_agendaService.listAllMeetings(m_userName));
}
void AgendaUI::listAllSponsorMeetings(void){
	cout << "[list all sponsor meetings]" << endl;
	printMeetings(m_agendaService.listAllSponsorMeetings(m_userName));
}
void AgendaUI::listAllParticipateMeetings(void){
	cout << "[list all participator meetings]" << endl;
	printMeetings(m_agendaService.listAllParticipateMeetings(m_userName));
}
void AgendaUI::queryMeetingByTitle(void){
	cout << "[query meeting] [title]" << endl;
	string title;
	cout << "[query meeting] ";
	cin >> title;
	printMeetings(m_agendaService.meetingQuery(m_userName, title));
}
void AgendaUI::queryMeetingByTimeInterval(void){
	cout << "[query meetings] [start time (yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd)/hh:mm)]" << endl;
	string start, end;
	cout << "[query meetings] ";
	cin >> start >> end;
	cout << "[query meetings]" << endl;
	printMeetings(m_agendaService.meetingQuery(m_userName, start, end));
}
void AgendaUI::deleteMeetingByTitle(void){
	cout << "[delete meeting] [title]" << endl;
	cout << "[delete meeting] ";
	string title;
	cin >> title;
	if(m_agendaService.deleteMeeting(m_userName, title)){
		cout << "[delete meeting] succeed!" << endl;
	}
	else{
		cout << "delete meeting] Delete meeting fail!" << endl;
	}
	cout << endl;
}
void AgendaUI::deleteAllMeetings(void){
	m_agendaService.deleteAllMeetings(m_userName);
	cout << "[delete all meeting] succeed!" << endl;
	cout << endl;
}
void AgendaUI::printMeetings(const std::list<Meeting> &t_meetings){
	int len = 0;
	vector<string> str;
		cout.setf(ios::left);
	cout << setw(15) << "title" << setw(15) << "sponsor"
		 << setw(18) << "start time" << setw(18) << "end time"
		 << "participators\n";
	for(auto i:t_meetings){
		cout << setw(15) << i.getTitle() << setw(15) << i.getSponsor() << setw(18) <<
			 Date::dateToString(i.getStartDate()) << setw(18) <<
			 Date::dateToString(i.getEndDate());
		len = i.getParticipator().size();
		str = i.getParticipator();
		for(int j=0;j<len;j++){
			if(j!=len-1) cout << str[j] << ",";
			else cout << str[j] << endl;
		}
	}
	cout << endl;
}
