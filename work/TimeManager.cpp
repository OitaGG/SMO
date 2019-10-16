#include "TimeManager.hpp"

TimeManager::TimeManager(int amount) : sourcesAmount_(amount), currentTime_(0) {}

int TimeManager::getCurrentTime(){
  return currentTime_;
}

void TimeManager::addNewTime(int i){
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
  if(created_.size < sourcesAmount_)
    return false;
  return true;
}

void TimeManager::work(){
  if(time_.empty){
    return;
  } 
  time_.sort;
  currentTime_ = time_.front();
  time_.pop_front();
}
