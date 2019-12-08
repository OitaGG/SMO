#include "../include/Device.hpp"

Device::Device(TimeManager* timeManager, Buffer* buffer, StatManager* statManager, int N, double Lambda) : timeManager_(timeManager), 
    buffer_(buffer), statManager_(statManager), amount_(N), time_(0.0), Lambda_(Lambda) {
    
    this->devicesArray_ = new int[amount_];
    this->waitFor_ = new double[amount_];
    this->wait_ = new double[amount_];

    for(size_t i = 0; i < amount_; i++){
      this->devicesArray_[i] = -1;
      this->waitFor_[i] = -1;
      this->wait_[i] = -1;
    }
}

void Device::get(int i){
  for(size_t k = 0; k < i; k++){
    int numS = this->buffer_->get();
    std::cout<<"TO DEVICE"<<numS<<std::endl;
    if(numS == -1)
      return;
    int place = this->recievePlace();
    this->devicesArray_[place] = numS;
    double timeWait = this->fxRule();
    this->waitFor_[place] = this->time_ + timeWait;
    this->wait_[place] = timeWait;
    this->statManager_->deviceGetFromBuffer(numS, waitFor_[place]);
    this->timeManager_->addNewTime(waitFor_[place]);
    this->getFreePlaces();
  }
}

int Device::getFreePlaces(){
  int count = 0;
  for(int i = 0; i < this->amount_; i++){
    if(this->devicesArray_[i] == -1){
      count++;
    }
  }
  return count;
}

void Device::work(){
  this->time_ = this->timeManager_->getCurrentTime();
  this->free();
  this->get(this->getFreePlaces());
}

void Device::free(){
  for (size_t i = 0; i < this->amount_; i++){
    if(this->waitFor_[i] == this->time_){
      this->statManager_->deviceDone(this->devicesArray_[i],this->wait_[i]);
      this->statManager_->pushTimePr(this->devicesArray_[i], this->wait_[i]);
      this->devicesArray_[i] = -1;
      this->waitFor_[i] = -1;
      this->wait_[i] = -1;
    }
  }
}

double Device::fxRule(){
  return ((-1.0 / Lambda_)*log((double)rand()/(RAND_MAX)));
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

bool Device::done(){
  int count = 0;
  for(size_t i = 0; i < amount_; i++){
    if(this->devicesArray_[i] == -1) 
      count++;
  }
  if(count == this->amount_)
    return true;
  return false;
}

double Device::getDevInfo(int i){
  return wait_[i];
}

Device::~Device(){
  delete[] this->devicesArray_;
  delete[] this->wait_;
  delete[] this->waitFor_;
}