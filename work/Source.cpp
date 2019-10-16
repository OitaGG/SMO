#include "Source.hpp"

Source::Source(TimeManager* timeManager, int N) : timeManager(timeManager), amount_(N), time_(0) {
    sourcesArray_ = new int[amount_];
    for(size_t i = 0; i < amount_; i++){
      sourcesArray_[i] = -1;
    }
}

void Source::getTime(){
}

void Source::generate(){
  for(size_t i = 0; i < amount_; i++){
    if(timeManager->done())
      return;
    if(sourcesArray_[i] = -1){
      sourcesArray_[i] = time_ + fxRule();
      timeManager->created(i);
      timeManager->addNewTime(sourcesArray_[i]);
    }
  } 
}

void Source::check(){
  for(size_t i = 0; i < amount_; i++){
    if(sourcesArray_[i] = time_){
      send(i);
      free(i);
    }
  }
}

void Source::work(){
  time_ = timeManager->getCurrentTime();
  check();
  if(!timeManager->done()){
    generate();
  }
}

int Source::fxRule(){
  int a = 0;
	int b = 1;
	return (double)a+(double)(b-a)*(rand()%100)/100;
}

void Source::send(int i) {
  if(buffer_->isReady()){
    buffer_->set(i);
  } else {
    buffer_->force(i);
  }
  free(i);
}

void Source::free(int i) {
  sourcesArray_[i] = -1;
}
