#ifndef DATE_H 
#define DATE_H 

#include <string> 
#include <sstream>
using std::string;
 
class Date { 
public: 
  Date(){}
  Date(int y, int m, int d, int h, int mi){
  	year_ = y;
  	month_ = m;
  	day_ = d;
  	hour_ = h;
  	minute_ = mi;
  }
  int getYear(void) const{
  	return year_;
  }
  void setYear(int year){
  	year_ = year;
  }
  int getMonth(void) const{
  	return month_;
  }
  void setMonth(int month){
  	month_ = month;
  } 
  int getDay(void) const;{
  	return day_;
  } 
  void setDay(int day){
  	day_ = day;
  } 
  int getHour(void) const{
  	return hour_;
  } 
  void setHour(int hour){
  	hour_ = hour;
  } 
  int getMinute(void) const{
  	return minute_;
  } 
  void setMinute(int minute){
  	minute_ = minute;
  } 
  static bool isValid(Date date){
  	if(date.getYear()<1000||date.getYear>9999) return 0;
  	if(date.getMonth()<=0||date.getMonth()>12) return 0;
  	switch(date.getMonth()){
  		case 2: if(date.getYear()/4==0&&date.getYear()/100!=0||date.getYear()/400==0) 
  			        if(!(date.getDay()>=1&&date.getDay()<=29)) return 0;
  			    else {
  			    	if(!(date.getDay()>=1&&date.getDay()<=28)) return 0;
  			    }
  			    break;
  	    case 4:
  	    case 6:
  	    case 9:
  	    case 11: if(!(date.getDay()>=1&&date.getDay()<=30)) return 0;
  	             break;
  	    default: if(!(date.getDay()>=1&&date.getDay()<=31)) return 0;
  	}
  	if(!(date.getHour()>=1&&date.getHour()<=23)) return 0;
  	if(!(date.getMinute()>=1&&date.getMinute()<=59)) return 0;
  	return 1;
  } 
  static Date stringToDate(string dateString){
  	stringstream ss;
  	ss << dateString;
  	char c;
  	int year, month, day, hour, min;
  	ss >> year >> c >> month >> c >> day >> c >> hour >> c >> min;
  	return Date(year, month, day, hour, min);
  } 
  static string dateToString(Date date){
  	stringstream ss;
  	ss << date.getYear() << '-' << addZero(date.getMonth()) << '-'
  	   << addZero(date.getDay()) << '/' << addZero(date.getHour()) << ':'
  	   << addZero(date.getMinute());
  	return ss.str();
  } 
  Date& operator=(const Date& date){
  	year_ = date.getYear();
  	month_ = date.getMonth();
  	day_ = date.getDay();
  	hour_ = date.getHour();
  	minute_ = date.getMinute();
  	return *this;
  } 
  bool operator==(const Date& date) const{
  	if(year_==date.getYear()&&month_==date.getMonth()
  		     &&day_==date.getDay()&&hour_==date.getHour()
  		           &&minute_==date.getMinute()) 
  		return 1;
  	else return 0;
  }
  bool operator>(const Date& date) const{
  	if(year_ > date.getYear()) return 1;
  	else if(year_ < date.getYear()) return 0;
  	  else {
  	  	if(month_ > date.getMonth()) return 1;
  	  	else if(month_ < date.getMonth()) return 0;
  	  	  else {
  	  	  	if(day_ > date.getDay()) return 1;
  	  	    else if(day_ < date.getDay()) return 0;
  	  	      else {
  	  	      	if(hour_ > date.getHour()) return 1;
  	  	        else if(hour_ < date.getHour()) return 0;
  	  	          else {
  	  	          	if(minute_ > date.getMinute()) return 1;
  	  	          	else return 0;
  	  	          }
  	  	      }
  	  	  }
  	  }
  } 
  bool operator<(const Date& date) const{
  	if((*this>date)||*this==date) return 0;
  	else return 1;
  }
  bool operator>=(const Date& date) const{
  	return !(*this<date);
  } 
  bool operator<=(const Date& date) const{
  	return !(*this>date);
  } 

 
private: 
  int year_; 
  int month_; 
  int day_; 
  int hour_; 
  int minute_;
  static string addZero(int var){
  	stringstream ss;
  	if(var < 10)   ss << '0' << var;
  	else ss << var;
  	return ss.str();
  } 
}; 
 
#endif 
