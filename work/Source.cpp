#include "Source.hpp"

Source::Source(TimeManager* timeManager, Buffer* buffer, StatManager* statManager, int N) : timeManager(timeManager),
  buffer_(buffer), statManager_(statManager), amount_(N), time_(0.0), Lambda(0), Betta(1) {
    this->sourcesArray_ = new double[amount_];
    for(size_t i = 0; i < this->amount_; i++){
      this->sourcesArray_[i] = -1;
    }
}

void Source::generate(){
  for(size_t i = 0; i < this->amount_; i++){
    if(this->timeManager->done())
      return;
    if(this->sourcesArray_[i] == -1){
      this->sourcesArray_[i] = time_ + fxRule();
      this->statManager_->sourceGenerate(i, sourcesArray_[i]);
      this->timeManager->addNewTime(sourcesArray_[i]);
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
  std::cout<<"<<<<<<     TIME: "<<this->time_<<">>>>>>"<<std::endl;
  this->check();
  if(!this->timeManager->done()){
    this->generate();
  }
}

double Source::fxRule(){
  return ((double)rand() / (double)RAND_MAX) * (Betta - Lambda) + Lambda;
}

void Source::send(int i, double t) {
  if(this->buffer_->isReady()){
    this->buffer_->set(i, t);
  } else {
    this->buffer_->force(i, t);
  }
}

void Source::free(int i) {
  this->sourcesArray_[i] = -1;
}

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

Source::~Source(){
  delete this->sourcesArray_;
}