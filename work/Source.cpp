#include "Source.hpp"

Source::Source(TimeManager* timeManager, Buffer* buffer, StatManager* statManager, int N) : timeManager(timeManager),
  buffer_(buffer), statManager_(statManager), amount_(N), time_(0.0) {
    sourcesArray_ = new double[amount_];
    for(size_t i = 0; i < amount_; i++){
      sourcesArray_[i] = -1;
    }
}

void Source::generate(){
  for(size_t i = 0; i < amount_; i++){
    if(timeManager->done())
      return;
    if(sourcesArray_[i] == -1){
      sourcesArray_[i] = time_ + fxRule();
      statManager_->sourceGenerate(i, sourcesArray_[i]);
      timeManager->addNewTime(sourcesArray_[i]);
    }
  } 
}

void Source::check(){
  for(size_t i = 0; i < amount_; i++){
      statManager_->sourceChecked(i);
    if(sourcesArray_[i] == time_){
      send(i);
      free(i);
    }
  }
}

void Source::work(){
  time_ = timeManager->getCurrentTime();
  std::cout<<time_<<std::endl;
  check();
  if(!timeManager->done()){
    generate();
  }
}

double Source::fxRule(){
  int a = 0;
	int b = 1;
	double c = (double)a+(double)(b-a)*(rand()%100)/100;
  return c;
}

void Source::send(int i) {
  if(buffer_->isReady()){
    buffer_->set(i);
  } else {
    buffer_->force(i);
  }
}

void Source::free(int i) {
  sourcesArray_[i] = -1;
}

bool Source::done(){
  int count = 0;
  for(size_t i = 0; i < amount_; i++){
    if(sourcesArray_[i] == -1) 
      count++;
  }
  if(count == amount_)
    return true;
  return false;
}

Source::~Source(){
  delete sourcesArray_;
}