#include "../include/Buffer.hpp"

Buffer::Buffer(TimeManager* timeManager, StatManager* statManager, int N) : timeManager_(timeManager), 
statManager_(statManager), amount_(N) {
  this->BufferArray_ = new int[amount_];
  this->BufferTime_ = new double[amount_];
  for (size_t i = 0; i < amount_; i++)
  {
    this->BufferArray_[i] = -1;
    this->BufferTime_[i] = -1;
  }
  
}

void Buffer::set(int i, double t){
  int place = this->getFreePlaceForSet();
  std::cout<<"PLACE "<<place<<std::endl;
  BufferArray_[place] = i;
  BufferTime_[place] = t;
  this->statManager_->pushingAmount(place, i);
  this->statManager_->bufferGetFromSource(i,t);
}

int Buffer::get(){
  if(!this->isEmpty()){
    int place = this->getPlaceForDevice();
    int RequestForDev = this->BufferArray_[place];
    double RequestTime = this->timeManager_->getCurrentTime() - this->BufferTime_[place];
    this->statManager_->pushTimeOj(RequestForDev,RequestTime);
    this->clearPlace(place);
    return RequestForDev;
  }
  return(-1);
}

bool Buffer::isReady(){
  int count = 0;
  for (size_t i = 0; i < this->amount_; i++)
  {
    if(this->BufferArray_[i] != -1)
      count++;
  }
  if(count < this->amount_)
    return true;
  return false;  
}

void Buffer::force(int i, double t){
  int place = this->getPlaceForForce();
  std::cout<<"Force-place "<<place<<std::endl;
  int forcedRequest = this->BufferArray_[place];
  int forcedTime = this->BufferTime_[place];
  this->BufferArray_[place] = i;
  this->BufferTime_[place] = t;
  this->statManager_->pushingAmount(place, i);
  this->statManager_->bufferForced(i, forcedRequest);
  this->statManager_->pushTimeOj(forcedRequest,this->timeManager_->getCurrentTime() - forcedTime);
}

bool Buffer::isEmpty(){
  int count = 0;
  for (size_t i = 0; i < amount_; i++)
  {
    if(BufferArray_[i] == -1)
      count++;
  }
  if(count == this->amount_)
    return true;
  return false;
}

int Buffer::getFreePlaceForSet(){
  for (size_t i = 0; i < this->amount_; i++)
  {
    if(this->BufferArray_[i] == -1)
      return i;
  }
  return -1;
}

int Buffer::getPlaceForForce(){
  int place = 0;
  double max = this->BufferTime_[0];
  for (size_t i = 0; i < amount_; i++)
  {
    if(this->BufferTime_[i] > max){
      max = this->BufferTime_[i];
      place = i;
    }
  }
  return place;  
}

int Buffer::getPlaceForDevice(){
  double min = BufferTime_[0];
  int place = 0;
  for (size_t i = 0; i < amount_; i++)
  {
    if(this->BufferTime_[i] < min && this->BufferArray_[i] != -1){
      min = this->BufferTime_[i];
      place = i;
    }
  }
  return place;
}

void Buffer::clearPlace(int i){
  this->BufferTime_[i] = -1;
  this->BufferArray_[i] = -1;
}

double Buffer::getBuffInfo(int i){
  return BufferTime_[i];
}

int Buffer::getRequestInBuff(int i){
  return BufferArray_[i];
}

Buffer::~Buffer(){
  delete[] this->BufferArray_;
  delete[] this->BufferTime_;
}