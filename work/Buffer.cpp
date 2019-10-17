#include "Buffer.hpp"

Buffer::Buffer(TimeManager* timeManager, int N) : timeManager_(timeManager), amount_(N) {
  bufferList_ = std::list<int>();
}

void Buffer::set(int i){
  bufferList_.push_front(i);
  std::cout<<"##################"<<std::endl;  
  std::cout<<"Buffer get from source: " << i <<std::endl;
  std::cout<<"##################"<<std::endl;  
}

int Buffer::get(){
  int sizeBuff = amount_ - bufferList_.size();
  std::cout<<"Size of buffer: "<<sizeBuff<<std::endl;
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
  std::cout<<"##################"<<std::endl;  
  std::cout<<"Buffer get from source: " << i << " and forced it in place from source "<< bufferList_.back() <<std::endl;
  std::cout<<"##################"<<std::endl;
  timeManager_->refused(bufferList_.back());  
  bufferList_.pop_back();
  bufferList_.push_front(i);
}

bool Buffer::isEmpty(){
  if(bufferList_.size() == 0){
    return true;
  }
  return false;
}
