#include "../include/Date.hpp"
#include <sstream>
#include <iostream>
using namespace std;

Date::Date(){
 m_year = m_month = m_day = m_hour = m_minute = 0;
}
Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute){
 m_year = t_year;
 m_month = t_month;
 m_day = t_day;
 m_hour = t_hour;
 m_minute = t_minute;
}
bool str_Valid(const string& str){
	if(str[4]!='-'||str[7]!='-'||str[10]!='/'||str[13]!=':'||str.size()!=16) return 0;
	for(int i=0;i<str.size();i++){
		if(i==4||i==7||i==10||i==13) continue;
		if(str[i]<'0'||str[i]>'9') return 0;
	}
	return 1;
}
Date::Date(const std::string &dateString){
 if(!str_Valid(dateString)){
  *this = Date();
 return;
 }
 stringstream ss;
 char ch;
 ss << dateString;
 ss >> m_year >> ch >> m_month >> ch >> m_day >> ch
    >> m_hour >> ch >> m_minute;
}
int Date::getYear(void) const{
 return m_year;
}
void Date::setYear(const int t_year){
 m_year = t_year;
}
int Date::getMonth(void) const{
 return m_month;
}
void Date::setMonth(const int t_month){
 m_month = t_month;
}
int Date::getDay(void) const{
 return m_day;
}
void Date::setDay(const int t_day){
 m_day = t_day;
}
int Date::getHour(void) const{
 return m_hour;
}
void Date::setHour(const int t_hour){
 m_hour = t_hour;
}
int Date::getMinute(void) const{
 return m_minute;
}
void Date::setMinute(const int t_minute){
 m_minute = t_minute;
}
std::string add0(int temp){
 stringstream result;
 if(temp<10) result << '0';
 result << temp;
 return result.str();
}
bool Date::isValid(const Date &t_date){
 if(t_date.getYear()<1000||t_date.getYear()>9999) return 0;
 if(t_date.getMonth()<1||t_date.getMonth()>12) return 0;
 switch(t_date.getMonth()){
  case 2: if(t_date.getYear()%4==0&&t_date.getYear()%100!=0||t_date.getYear()%400==0){
   if(!(t_date.getDay()>=1&&t_date.getDay()<=29)) return 0;
  }
  else {
   if(!(t_date.getDay()>=1&&t_date.getDay()<=28)) return 0;
  }
      break;
  case 4:
  case 6:
  case 9:
  case 11: if(!(t_date.getDay()>=1&&t_date.getDay()<=30)) return 0;
      break;
  default: if(!(t_date.getDay()>=1&&t_date.getDay()<=31)) return 0;
 }
 if(!(t_date.getHour()>=0&&t_date.getHour()<=23)) return 0;
 if(!(t_date.getMinute()>=0&&t_date.getMinute()<=59)) return 0;
 return 1;
}

Date Date::stringToDate(const std::string &t_dateString){
 if(str_Valid(t_dateString)){
 stringstream ss;
 char ch;
 int year, mon, day, hour, min;
 ss << t_dateString;
 ss >> year >> ch >> mon >> ch >> day
    >> ch >> hour >> ch >> min;
 return Date(year, mon, day, hour, min);
}
    else return Date();
}
std::string Date::dateToString(const Date &t_date){
 if(isValid(t_date)){
 stringstream result;
 result << t_date.getYear() << '-' << add0(t_date.getMonth()) << '-' << add0(t_date.getDay())
        << '/' << add0(t_date.getHour()) << ':' << add0(t_date.getMinute());
 return result.str();
}
    else return "0000-00-00/00:00";
}
Date& Date::operator=(const Date &t_date){
 m_year = t_date.getYear();
 m_month = t_date.getMonth();
 m_day = t_date.getDay();
 m_hour = t_date.getHour();
 m_minute = t_date.getMinute();
 return *this;
}
bool Date::operator==(const Date &t_date) const{
 if(m_year==t_date.getYear()&&m_month==t_date.getMonth()&&m_day==t_date.getDay()
  &&m_hour==t_date.getHour()&&m_minute==t_date.getMinute())
  return 1;
 else return 0;
}
bool Date::operator>(const Date &t_date) const{
 if(m_year>t_date.getYear()) return 1;
 else if(m_year<t_date.getYear()) return 0;
 else {
  if(m_month>t_date.getMonth()) return 1;
  else if(m_month<t_date.getMonth()) return 0;
  else {
   if(m_day>t_date.getDay()) return 1;
   else if(m_day<t_date.getDay()) return 0;
   else {
    if(m_hour>t_date.getHour()) return 1;
    else if(m_hour<t_date.getHour()) return 0;
    else {
     if(m_minute>t_date.getMinute()) return 1;
     else return 0;
    }
   }
  }
 }
}
bool Date::operator<(const Date &t_date) const{
 if(*this==t_date||*this>t_date) return 0;
 else return 1;
}
bool Date::operator>=(const Date &t_date) const{
 return !(*this<t_date);
}
bool Date::operator<=(const Date &t_date) const{
 return !(*this>t_date);
}
