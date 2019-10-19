#include "Device.hpp"

Device::Device(TimeManager* timeManager, Buffer* buffer, StatManager* statManager, int N) : timeManager_(timeManager), 
    buffer_(buffer), statManager_(statManager), amount_(N), time_(0.0) {
    devicesArray_ = new int[amount_];
    wait_ = new double[amount_];

    for(size_t i = 0; i < amount_; i++){
      devicesArray_[i] = -1;
      wait_[i] = -1;
    }
}

void Device::get(int i){
  for(size_t k = 0; k < i; k++){
    int numS = buffer_->get();
    if(numS == -1)
      return;
    int place = recievePlace();
    devicesArray_[place] = numS;
    wait_[place] = time_ + fxRule();
    statManager_->deviceGetFromBuffer(i);
    timeManager_->addNewTime(wait_[place]);
    getFreePlaces();
  }
}

int Device::getFreePlaces(){
  int count = 0;
  for(int i = 0; i < amount_; i++){
    if(devicesArray_[i] == -1){
      count++;
    }
  }
  return count;
}

void Device::work(){
  time_ = timeManager_->getCurrentTime();
  free();
  int freePlaces = getFreePlaces();
  get(freePlaces);
}

void Device::free(){
  for (size_t i = 0; i < amount_; i++){
    if(wait_[i] == time_){
      statManager_->deviceDone(i,wait_[i]);
      devicesArray_[i] = -1;
      wait_[i] = -1;
    }
  }
}

double Device::fxRule(){
  return (-1.0 / 1.5*log(rand()/(double)RAND_MAX));
}

int Device::recievePlace(){
  int place = -1;
  for (size_t i = 0; i < amount_; i++){
    if(devicesArray_[i] == -1){
      place = i;
      break;
    }
  }
  return place;
}
Device::~Device(){
  delete devicesArray_;
  delete wait_;
}

bool Device::done(){
  int count = 0;
  for(size_t i = 0; i < amount_; i++){
    if(devicesArray_[i] == -1) 
      count++;
  }
  if(count == amount_)
    return true;
  return false;
}
