#ifndef MEETING_H 
#define MEETING_H 

#include "Date.h" 

class Meeting { 
public: 
  Meeting(){}
  Meeting(string sponsor, string participator, 
          Date startTime, Date endTime, string title){
    sponsor_ = sponsor; 
    participator_ = participator; 
    startDate_ = startTime;
    endDate_ = endTime; 
    title_ = title; 
  } 
   string getSponsor(void) const{
   	return sponsor_;
   } 
   void setSponsor(string sponsor){
   	sponsor_ = sponsor;
   } 
  string getParticipator(void) const{
  	return participator_;
  } 
  void setParticipator(string participator){
  	participator_ = participator;
  } 
   Date getStartDate(void) const{
   	return startDate_
   } 
  void setStartDate(Date startTime){
  	startDate_ = startTime;
  } 
   Date getEndDate(void) const{
   	return endDate_;
   } 
  void setEndDate(Date endTime){
  	endDate_ = endTime;
  } 
  string getTitle(void) const{
  	return title_
  } 
  void setTitle(string title){
  	title_ = title;
  } 

 
private: 
  string sponsor_; 
  string participator_; 
  Date startDate_; 
  Date endDate_; 
  string title_; 
}; 
#endif 
