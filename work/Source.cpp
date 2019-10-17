#include "Source.hpp"

Source::Source(TimeManager* timeManager, Buffer* buffer, int N) : timeManager(timeManager),
  buffer_(buffer), amount_(N), time_(0.0) {
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
      std::cout<<"Source " << i << " generate at "<< sourcesArray_[i]<<std::endl;
      timeManager->created(i);
      timeManager->addNewTime(sourcesArray_[i]);
    }
  } 
}

void Source::check(){
  for(size_t i = 0; i < amount_; i++){
      std::cout<<"Source " << i <<": "<< sourcesArray_[i] << "->Checked" <<std::endl;
    if(sourcesArray_[i] == time_){
      send(i);
      free(i);
    }
  }
}

void Source::work(){
  time_ = timeManager->getCurrentTime();
  std::cout<<"Current Time For Source : "<< time_ <<std::endl;
  std::cout<<"******************"<<std::endl;  
  check();
  if(!timeManager->done()){
    generate();
  }
  std::cout<<"Succesfully iteration for Source"<<std::endl;
  std::cout<<"******************"<<std::endl;
  std::cout<<std::endl;
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