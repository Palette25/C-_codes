#include "date.hpp"
void Date::setDate(int year, int month, int day){
	year_ = year;
	month_ = month;
	day_ = day;
}
int Date::year()const{
	return year_;
}
int Date::month()const{
	return month_;
}
int Date::day()const{
	return day_;
}
int Date::daysOfMonth(int year, int month) const{
	switch(month){
 case 2 :
 if(year%4==0&&year%100!=0||year%400==0)
			return 29;
		 return 28;
		case 4:case 6:case 9:case 11:
		return 30;
		default :
		return 31;
	}
}
void Date::increment(){
     day_++;
     if(day_>daysOfMonth(year_,month_)) {day_ = 1;month_++;
     if(month_>12) {
      	month_ = 1;
      	year_++;
     }
}
}
void Date::decrement(){
     day_--;
     if(day_==0) {
     if(month_ ==1) {
       day_ = 31;
       month_ = 12;
       year_--;
         }
     else {
       month_--;
       day_ = daysOfMonth(year_, month_);
        }
    }
}
