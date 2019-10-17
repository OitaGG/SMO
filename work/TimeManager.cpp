#include "TimeManager.hpp"

TimeManager::TimeManager(int amount) : sourcesAmount_(amount), currentTime_(0.0) {
  created_ = std::list<int>();
  sent_ = std::list<int>();
  time_ = std::list<double>();
  refused_ = std::list<int>();
}

double TimeManager::getCurrentTime(){
  return currentTime_;
}

void TimeManager::addNewTime(double i){
  time_.push_back(i);
}

void TimeManager::sent(int i){
  sent_.push_back(i);
}

void TimeManager::created(int i){
  created_.push_back(i);  
}

void TimeManager::refused(int i){
  refused_.push_back(i);
}

bool TimeManager::done(){
  if(created_.size() < sourcesAmount_)
    return false;
  return true;
}

void TimeManager::work(){
  if(time_.empty()){
    return;
  } 
  printInfo();
  time_.sort();
  currentTime_ = time_.front();
  time_.pop_front();
}

void TimeManager::printInfo(){
  std::cout<<"--------------------"<<std::endl;
  std::cout<<"Created: "<< created_.size() << std::endl;
  std::cout<<"Sent: "<< sent_.size() << std::endl;
  std::cout<<"Refused: "<< refused_.size() << std::endl;
  std::cout<<"Time on TimeManagment "<<currentTime_<<std::endl;
  std::cout<<"-------------------"<<std::endl;
}