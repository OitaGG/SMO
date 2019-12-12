#include "../include/Device.hpp"

Device::Device(TimeManager* timeManager, Buffer* buffer, StatManager* statManager, int N, double Lambda) : timeManager_(timeManager), 
    buffer_(buffer), statManager_(statManager), amount_(N), time_(0.0), Lambda_(Lambda) {
    // devicesArray_ - индекс это номер прибора, зн-е - номер заявки
    // waitFor_ - индекс - это номер прибора, зн-е - время, когда заявки зарезолвиться
    // wait_ - индекс - это номер прибора, зн-е - время на приборе
    this->devicesArray_ = std::vector<int>(this->amount_, -1);
    this->waitFor_ = std::vector<double>(this->amount_, -1);
    this->wait_ = std::vector<double>(this->amount_, -1);
}

void Device::get(int i){
  for(size_t k = 0; k < i; k++){
    // берем заявку из буфера, если ее нет, то -1
    int numS = this->buffer_->get();
    if(numS == -1)
      return;
    int place = this->recievePlace();
    // ставим ее на выбранный прибор
    this->devicesArray_[place] = numS;
    double timeWait = this->fxRule();
    this->waitFor_[place] = this->time_ + timeWait;
    this->wait_[place] = timeWait;
    // отправляем статистику об успешной постановке на прибор и добавляем новое время в календарь
    this->statManager_->deviceGetFromBuffer(numS, waitFor_[place]);
    this->timeManager_->addNewTime(waitFor_[place]);
  }
}

// смотрим, сколько приборов свободны
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
  // смотрим текущее время
  this->time_ = this->timeManager_->getCurrentTime();
  // освобождаем прибор
  this->free();
  // берем новые заявки с буфера
  this->get(this->getFreePlaces());
}

void Device::free(){
  for (size_t i = 0; i < this->amount_; i++){
    if(this->waitFor_[i] == this->time_){
      // отправляем статистику об успешном резолве заявки, пушим время на приборе
      this->statManager_->deviceDone(this->devicesArray_[i],i, this->wait_[i]);
      this->statManager_->pushTimePr(this->devicesArray_[i], this->wait_[i]);
      this->statManager_->deviceWorkedWithUpdate(i);
      // очищаем прибор
      this->devicesArray_[i] = -1;
      this->waitFor_[i] = -1;
      this->wait_[i] = -1;
    }
  }
}

double Device::fxRule(){
  return ((-1.0 / Lambda_)*log((double)rand()/(RAND_MAX)));
}

// находим свободный прибор, на который поставим заявку
int Device::recievePlace(){
  int place = -1;
  for (size_t i = 0; i < this->amount_; i++){
    if(devicesArray_[i] == -1){
      place = i;
      break;
    }
  }
  return place;
}

// обслужили ли все приборы свои заявки
bool Device::done(){
  int count = 0;
  for(size_t i = 0; i < this->amount_; i++){
    if(this->devicesArray_[i] == -1) 
      count++;
  }
  if(count == this->amount_)
    return true;
  return false;
}

// для статистикиы
double Device::getDevInfo(int i){
  return wait_[i];
}

// освобождение памяти
Device::~Device(){
  // delete[] this->devicesArray_;
  // delete[] this->wait_;
  // delete[] this->waitFor_;
}
