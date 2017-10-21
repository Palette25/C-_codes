#include"date.hpp"
Date::Date(){
     year = 2017;
     month = 1;
     day = 28;
}
Date::Date(int year_, int month_, int day_){
     year = year_;
     month = month_;
     day = day_;
  normalize();
}
bool Date::equals(const Date Date1)const{
     if(Date1.year==year&&Date1.month==month&&Date1.day==day)
      return 1;
     else return 0;
}
bool Date::smallerThan(const Date Date1)const{
     long sum1 = Date1.year*365 + Date1.month*30 + Date1.day;
     long sum2 = year*365 + month*30 + day;
     if(sum1 >= sum2) return 1;
     else return 0; 
}
void Date::normalize(){
  while(month > 12) {
    month = month - 12;
  year++;
  }
  while(day > daysOfMonth(year, month)) {
    day = day - daysOfMonth(year, month);
    month++;
 while(month > 12) {
    month = month - 12;
  year++;
  }
  }
}