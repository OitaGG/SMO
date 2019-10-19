#include "Buffer.hpp"

Buffer::Buffer(TimeManager* timeManager, StatManager* statManager, int N) : timeManager_(timeManager), 
statManager_(statManager), amount_(N) {
  bufferList_ = std::list<int>();
}

void Buffer::set(int i){
  bufferList_.push_front(i);
  statManager_->bufferGetFromSource(i);
}

int Buffer::get(){
  int sizeBuff = amount_ - bufferList_.size();
  if(bufferList_.size() > 0){
    int k = bufferList_.front();
    bufferList_.pop_front();
    return k;
  }
  return(-1);
}

bool Buffer::isReady(){
  if(bufferList_.size() >= amount_)
    return false;
  return true;
}

void Buffer::force(int i){
  statManager_->bufferForced(i, bufferList_.back());
  bufferList_.pop_back();
  bufferList_.push_front(i);
}

bool Buffer::isEmpty(){
  if(bufferList_.size() == 0){
    return true;
  }
  return false;
}
