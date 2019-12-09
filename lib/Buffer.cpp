#include "../include/Buffer.hpp"
#include <limits>
#include <cstddef>

Buffer::Buffer(TimeManager* timeManager, StatManager* statManager, int N) : timeManager_(timeManager), 
statManager_(statManager), amount_(N) {
  // BufferArray_ - индекс это номер буфера, зн-е это номер заявки
  this->BufferArray_ = std::vector<int>(this->amount_, -1);
  // this->BufferArray_ = new int[amount_];
  // BufferTime_ - индекс - это номер буфера, зн-е это время заявки
  // this->BufferTime_ = new double[amount_];
  this->BufferTime_ = std::vector<double>(this->amount_, -1);
}

void Buffer::set(int i, double t){
  int place = this->getFreePlaceForSet();
  // ставим на свободное место в буфере заявку и ее время
  BufferArray_[place] = i;
  BufferTime_[place] = t;
  // отправляем статистику об успешном пуше
  this->statManager_->bufferGetFromSource(i,t);
}

int Buffer::get(){
  // если буфер не пустой
  if(!this->isEmpty()){
    int place = this->getPlaceForDevice();
    if(place == -1)
      return -1;
    // берем заявку с указанного места в буфере
    int RequestForDev = this->BufferArray_[place];
    double RequestTime = this->timeManager_->getCurrentTime() - this->BufferTime_[place];
    // отправляем статистику о времени ожидания
    this->statManager_->pushTimeOj(RequestForDev,RequestTime);
    // освобождаем место в буфереы
    this->clearPlace(place);
    // отправляем на девайс номер заявки
    return RequestForDev;
  }
  // если пустой отправляем на девайс -1
  return(-1);
}

// есть ли свободные места в буфере
bool Buffer::isReady(){
  int count = 0;
  for (size_t i = 0; i < this->amount_; i++){
    if(this->BufferArray_[i] != -1)
      count++;
  }
  if(count < this->amount_)
    return true;
  return false;  
}

void Buffer::force(int i, double t){
  int place = this->getPlaceForForce();
  // Берем заявку из буфера, которая уходит в отказ по заданному месту
  int forcedRequest = this->BufferArray_[place];
  int forcedTime = this->BufferTime_[place];
  // форсим ее пришедшой заявкой
  this->BufferArray_[place] = i;
  this->BufferTime_[place] = t;
  // отправляем статистику о форсе, времени ожидания
  // this->statManager_->pushingAmount(place, i);
  this->statManager_->bufferForced(i, forcedRequest);
  this->statManager_->pushTimeOj(forcedRequest,this->timeManager_->getCurrentTime() - forcedTime);
}

// пустой ли буфер
bool Buffer::isEmpty(){
  int count = 0;
  for (size_t i = 0; i < this->amount_; i++){
    if(this->BufferArray_[i] == -1 && this->BufferTime_[i] == -1)
      count++;
  }
  if(count == this->amount_)
    return true;
  return false;
}

// ищет первое свободное место в буфере для новой заявки(постановка в порядке поступления)
// иначе возвращает -1
int Buffer::getFreePlaceForSet(){
  int index = 0;
  for (size_t i = 0; i < this->amount_; i++){
    if(this->BufferArray_[i] == -1){
      index = i;
      break;
    }
  }
  return index;
}

// ищет заявку, которую будем форсить(самую старую в буфере)
int Buffer::getPlaceForForce(){
  int place = 0;
  double max = this->BufferTime_[0];
  for (size_t i = 0; i < this->amount_; i++)
  {
    if(this->BufferTime_[i] > max){
      max = this->BufferTime_[i];
      place = i;
    }
  }
  return place;  
}

// ищет заявку, которую отправит на девайс(самую новую в буфере)
int Buffer::getPlaceForDevice(){
  double min = std::numeric_limits<double>::max();
  int place = -1;
  for (size_t i = 0; i < this->amount_; i++){
    if(this->BufferTime_[i] < min && this->BufferArray_[i] != -1 && this->BufferTime_[i] != -1){
      min = this->BufferTime_[i];
      place = i;
    }
  }
  return place;
}

// освобождает место в буфере
void Buffer::clearPlace(int i){
  this->BufferTime_[i] = -1.0;
  this->BufferArray_[i] = -1;
}

// для статистики
double Buffer::getBuffInfo(int i){
  return BufferTime_[i];
}

int Buffer::getRequestInBuff(int i){
  return BufferArray_[i];
}