#include "../include/TimeManager.hpp"

TimeManager::TimeManager(int amount, StatManager* statManager) : sourcesAmount_(amount), 
  statManager_(statManager), currentTime_(0.0) {
  time_ = std::list<double>();
}

double TimeManager::getCurrentTime(){
  return currentTime_;
}

void TimeManager::addNewTime(double i){
  time_.push_back(i);
}

bool TimeManager::done(){
  if(statManager_->generatedSize() < sourcesAmount_)
    return false;
  return true;
}

void TimeManager::work(){
  if(time_.empty()){
    return;
  } 
  time_.sort();
  currentTime_ = time_.front();
  time_.pop_front();
}