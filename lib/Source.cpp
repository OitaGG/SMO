#include "../include/Source.hpp"

Source::Source(TimeManager* timeManager, Buffer* buffer, StatManager* statManager, int N,double a, double b) : timeManager(timeManager),
  buffer_(buffer), statManager_(statManager), amount_(N), time_(0.0), Lambda(a), Betta(b) {
    // индекс массива - номер источника, значение - время генерации
    // this->sourcesArray_ = new double[amount_];
    this->currentAmount_ = 0;
    this->sourcesArray_ = std::vector<double>(this->amount_, -1);
}

void Source::generate(){
  for(size_t i = 0; i < this->amount_; i++){
    if(this->timeManager->done() )
      return;
    if(this->sourcesArray_[i] == -1){
      // задаем время для источников, которым оно еще не задано
      this->sourcesArray_[i] = time_ + fxRule();
      // std::cout<<"Source "<<i<<" Will generate at "<<sourcesArray_[i]<<std::endl;
      // добавляем новое время в календарь
      this->timeManager->addNewTime(sourcesArray_[i]);
      this->currentAmount_ += 1;
    }
  } 
}

void Source::check(){
  for(size_t i = 0; i < this->amount_; i++){
    if(this->sourcesArray_[i] == this->time_){
      this->send(i, this->sourcesArray_[i]);
      this->free(i);
    }
  }
}

void Source::work(){
  this->time_ = this->timeManager->getCurrentTime();
  // проверяем, можем ли мы запушить заявки в буфер
  this->check();
  // генерируем время для свободных заявок
  if(!this->timeManager->done() && !(this->currentAmount_ == this->statManager_->getRequestAmount())){
    this->generate();
  }
}

// правило генерации времени
double Source::fxRule(){
  return ((double)rand()/(double)RAND_MAX) * (Betta - Lambda) + Lambda;
}

void Source::send(int i, double t) {
  this->statManager_->sourceGenerate(i, sourcesArray_[i]);
  int count = this->statManager_->getRequestValue();
  // если в буфере есть место, пушим, если нет, то форсим
  if(this->buffer_->isReady()){
    this->buffer_->set(i, t);
  } else {
    this->buffer_->force(i, t);
  }
}

void Source::free(int i) {
  this->sourcesArray_[i] = -1;
}

// все ли заявки были сгенерированы и отправлены
bool Source::done(){
  int count = 0;
  for(size_t i = 0; i < this->amount_; i++){
    if(this->sourcesArray_[i] == -1) 
      count++;
  }
  if(count == this->amount_)
    return true;
  return false;
}

// освобождаем память
Source::~Source(){
//  delete[] this->sourcesArray_;
}
