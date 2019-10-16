#include "Buffer.hpp"

Buffer::Buffer(TimeManager* timeManager, int N) : timeManager_(timeManager), amount_(N) {
}

void Buffer::set(int i){
  bufferList_.push_front(i);
}

void Buffer::get(int i){
  for(size_t k = 0; i < k; i++){
    
  }
}

bool Buffer::isReady(){
  if(bufferList_.size() >= amount_ - 1)
    return false;
  return true;
}

void Buffer::force(int i){
  bufferList_.pop_back();
  bufferList_.push_back(i);
}

bool Buffer::isEmpty(){

}
