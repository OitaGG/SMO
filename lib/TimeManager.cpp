#include "../include/TimeManager.hpp"

TimeManager::TimeManager(int amount, StatManager* statManager) : sourcesAmount_(amount), 
  statManager_(statManager), currentTime_(0.0) {
  time_ = std::list<double>();
}

// текущее время
double TimeManager::getCurrentTime(){
  return currentTime_;
}

// добавление времени в календарь событий
void TimeManager::addNewTime(double i){
  time_.push_back(i);
}

// сгенерировались ли все заявки
bool TimeManager::done(){
  if(statManager_->generatedSize() < this->sourcesAmount_)
    return false;
  return true;
}

// проход по календарю
void TimeManager::work(){
  if(time_.empty()){
    return;
  } 
  time_.sort();
  currentTime_ = time_.front();
  time_.pop_front();
}