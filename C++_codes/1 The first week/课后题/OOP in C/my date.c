#include <stdio.h>
#include <math.h> 
typedef struct {
  int year, month, day;
} Date;

Date* CreateDate(int year, int month, int day){
  Date* ptr = (Date*)malloc(sizeof(Date));
  ptr->year = year;
  ptr->month = month;
  ptr->day = day;
  return ptr;
}
void DestroyDate(Date** p){
  free (*p);
  *p = NULL;
}
Date* CopyDate(const Date* date){
  Date* ptr = (Date*)malloc(sizeof(Date));
  ptr->year = date->year;
  ptr->month = date->month;
  ptr->day = date->day;
  return ptr;
}

int GetYear(const Date* date){
  return (date->year);
}
int GetMonth(const Date* date){
  return (date->month);
}
int GetDay(const Date* date){
  return (date->day);
}
void SetYear(Date* date, int year){
  date->year = year;
}
void SetMonth(Date* date, int month){
  date->month = month;
}
void SetDay(Date* date, int day){
  date->day = day;
}
void SetDate(Date* date, int year, int month, int day){
  date->year = year;
  date->month = month;
  date->day = day;
}

char* GetDateString(const Date* date){
  char* date_str = (char*)malloc(sizeof(char)*11);
  int i, year = date->year;
    for(i=0;i<4;i++){
       if(year!=0) date_str[i] = year/pow(10, 3-i) + 48;
       else date_str[i] = 48;
       year-=pow(10, 3-i) * (date_str[i] - 48);
   }
    date_str[4] = date_str[7] = '-';
    date_str[5] = date->month/10 + 48;
    date_str[6] = date->month%10 + 48;
    date_str[8] = date->day/10 + 48;
    date_str[9] = date->day%10 + 48;
    date_str[10] = '\0';
    return date_str;
}
void DestroyDateString(char** p){
  free (*p);
  *p = NULL;
}
int dayofmonth(int year, int month){
  switch(month){
  case 2:
     if(year%4==0&&year%100!=0||year%400==0) return 29;
     else return 28;
  case 4:case 6:case 9:case 11:
     return 30;
  default : return 31;
}
}
void IncreaseDate(Date* date){
    date->day++;
    if(date->day>dayofmonth(date->year, date->month)){
      date->day = 1;
      date->month++;
      if(date->month>12){
        date->month = 1;
        date->year++;
      }
    }
}
void DecreaseDate(Date* date){
  date->day--;
  if(date->day==0){
    if(date->month==1){
      date->day = 31;
      date->month=12;
      date->year--;
    }
    else {
      date->month--;
      date->day=dayofmonth(date->year, date->month);
    }
  }
}