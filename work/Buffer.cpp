#include "Buffer.hpp"

Buffer::Buffer(TimeManager* timeManager, StatManager* statManager, int N) : timeManager_(timeManager), 
statManager_(statManager), amount_(N) {
  this->bufferList_ = std::list<int>();
  this->bufferListTime_ = std::list<double>();
}

void Buffer::set(int i, double t){
  this->bufferList_.push_front(i);
  this->bufferListTime_.push_front(t);
  this->statManager_->bufferGetFromSource(i);
}

int Buffer::get(){
  if(this->bufferList_.size() > 0){
    int k = this->bufferList_.front();
    this->bufferList_.pop_front();
    double f = this->timeManager_->getCurrentTime() - this->bufferListTime_.front();
    std::cout<<"TIMEOJ "<<f<<std::endl;
    this->bufferListTime_.pop_front();
    this->statManager_->pushTimeOj(k,f); 
    return k;
  }
  return(-1);
}

bool Buffer::isReady(){
  if(this->bufferList_.size() >= this->amount_)
    return false;
  return true;
}

void Buffer::force(int i, double t){
  this->statManager_->bufferForced(i, this->bufferList_.back());
  this->statManager_->pushTimeOj(this->bufferList_.back(),this->timeManager_->getCurrentTime() - this->bufferListTime_.back());
  this->bufferList_.pop_back();
  this->bufferList_.push_front(i);
  this->bufferListTime_.pop_back();
  this->bufferListTime_.push_front(t);
}

bool Buffer::isEmpty(){
  if(this->bufferList_.size() == 0){
    return true;
  }
  return false;
}
