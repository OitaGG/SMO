#include "Device.hpp"

Device::Device(TimeManager* timeManager, int N) : timeManager_(timeManager), amount_(N), time_(0) {
    devicesArray_ = new int[amount_];
    wait_ = new int[amount_];

    for(size_t i = 0; i < amount_; i++){
      devicesArray_[i] = -1;
      wait_[i] = -1;
    }
}

void Device::get(int i){
  buffer_->get(i);
}

int Device::getFreePlaces(){
  int count = 0;
  for(int i = 0; i < amount_; i ++){
    if(devicesArray_[i] = -1)
      count++;
  }
  return count;
}

void Device::work(){
  time_ = timeManager_->getCurrentTime();
  free();//Освобождает готовое
  int freePlaces = getFreePlaces();
  get(freePlaces);//Смотрит, сколько можно взять и вставить в девайс.
}

void Device::free(){
  for (size_t i = 0; i < amount_; i++){
    if(wait_[i] == time_){
      devicesArray_[i] = -1;
      wait_[i] = -1;
    }
  }
}

int Device::fxRule(){
  return (-1.0 / 1.5*log(rand()/(double)RAND_MAX));
}

Device::~Device(){
  delete devicesArray_;
  delete wait_;
}
