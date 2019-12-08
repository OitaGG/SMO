#include "../include/StatManager.hpp"
#include <string>

StatManager::StatManager(int F, int S, int D, int B) : F_(F), S_(S), D_(D), B_(B) {
  this->refused_ = new int[this->S_];
  this->timeoj_ = new double[this->S_];
  this->timepr_ = new double[this->S_];
  this->squaredTimeoj_ = new double[this->S_];
  this->squaredTimepr_ = new double[this->S_];
  this->amountOnBuffers = new int[this->B_];
  for (size_t i = 0; i < this->B_; i++){
    this->amountOnBuffers = 0;
  }
  for (size_t i = 0; i < this->S_; i++){
    this->refused_[i] = 0;
    this->timeoj_[i] = 0;
    this->timepr_[i] = 0;
    this->squaredTimeoj_[i] = 0;
    this->squaredTimepr_[i] = 0;
  }  
  this->generated_ = std::multimap<int,double>();
  this->sent_ = std::multimap<int,double>();
  this->Events_ = std::list<std::string>();
}

void StatManager::pushTimePr(int k, double t){
  this->timepr_[k] += t;
  this->squaredTimepr_[k] += t*t;
}

void StatManager::pushTimeOj(int k,double t){
  this->timeoj_[k] += t;
  this->squaredTimeoj_[k] += t*t;
}

int StatManager::generatedSize(){
  return this->generated_.size();
}

int StatManager::sentSize(){
  return this->sent_.size();
}

int StatManager::refusedSize(){
  int refSum = 0;
  for (size_t i = 0; i < this->S_; i++){
    refSum += this->refused_[i];
  }
  return refSum;
}


void StatManager::bufferGetFromSource(int i, double t){
  std::string str = "Buffer get from Source №" + std::to_string(i);
  std::cout<<str<<std::endl;
  this->Events_.push_back(str);
}

void StatManager::deviceGetFromBuffer(int i, double wait){
  std::string str = "Device get from Buffer with Source №" + std::to_string(i);
  std::cout<<str<<std::endl;
  this->Events_.push_back(str);
}

void StatManager::deviceDone(int i, double t){
  std::string str = "Device №" + std::to_string(i) +" done";
  std::cout<<str<<std::endl;
  this->Events_.push_back(str);
  this->sent_.insert(std::make_pair(i,t));  
}

void StatManager::bufferForced(int i, int k){ 
  std::string str = "Buffer get from Source № " + std::to_string(i) + "and forced it instead " + std::to_string(k);
  std::cout<<str<<std::endl;
  this->Events_.push_back(str);
  this->refused_[k]++;
}

void StatManager::sourceGenerate(int i, double t){
  this->generated_.insert(std::make_pair(i,t));
  std::string str = "Source " + std::to_string(i) + " generated"; 
  std::cout<<str<<std::endl;
  this->Events_.push_back(str);
} 

double StatManager::statForMultimap(int i){
  std::pair <std::multimap<int,double>::iterator, std::multimap<int,double>::iterator> ret;
  ret = sent_.equal_range(i); 
  double average = 0.0;
  for(auto it = ret.first; it != ret.second; ++it){
    average += it->second;
  }
  return average;
}

void StatManager::printResult(double time){
  // std::cout<<"Requsests value == "<<this->generatedSize()<<std::endl;
  // std::cout<<"-----------------------------------"<<std::endl;
  // double Kisp = 0;
  // for(auto i = 0; i < this->S_; i++){
  //   std::cout<<"SOURCE № "<<i<<"| ALL: "<<this->generated_.count(i)<<"| REF: "<< this->refused_[i];
  //   std::cout<<std::fixed<<std::setprecision(2)<<"| Potk: "<<((double)this->refused_[i]/(double)this->generated_.count(i));
  //   std::cout<<std::fixed<<std::setprecision(2)<<"| Tis: "<<(this->timeoj_[i] + this->timepr_[i])/(double)this->generated_.count(i);
  //   std::cout<<std::fixed<<std::setprecision(2)<<"| Toj: "<<this->timeoj_[i]/(double)this->generated_.count(i);
  //   std::cout<<std::fixed<<std::setprecision(2)<<"| Tobs: "<<this->timepr_[i]/(double)this->sent_.count(i);
  //   std::cout<<std::endl;
  // }
  // for (size_t i = 0; i < D_; i++){
  //   std::cout<<"DEVICE № "<<i;
  //   std::cout<<std::fixed<<std::setprecision(2)<<"| Kisp: "<<statForMultimap(i)/time<<std::endl;
  // }
  // std::cout<<"Sent value == "<<this->sentSize()<<std::endl;
  // std::cout<<"-----------------------------------"<<std::endl;
} 

StatsTableData *StatManager::getStats(double time){
  StatsTableData *toGive = new StatsTableData();
    for (int i = 0; i < this->S_; i++)
    {
        toGive->N.push_back(this->generated_.count(i));
        toGive->failureProb.push_back((double)this->refused_[i]/(double)this->generated_.count(i));
        toGive->avgTimeBeing.push_back((this->timeoj_[i] + this->timepr_[i])/(double)this->generated_.count(i));
        toGive->avgTimeWaiting.push_back(this->timeoj_[i]/(double)this->generated_.count(i));
        toGive->avgTimeProccessing.push_back(this->timepr_[i]/(double)this->sent_.count(i));
        toGive->dispTimeBeing.push_back(this->dispTimeBeing(i));
        toGive->dispTimeProccessing.push_back(dispTimeProcessing(i));
    }

    for (int i = 0; i < D_; i++)
    {
        toGive->K.push_back(statForMultimap(i)/time);
    }
    return toGive;
}

double StatManager::dispTimeBeing(int i){
  double time = (this->squaredTimeoj_[i])/(double)this->generated_.count(i) - (this->timeoj_[i]/this->generated_.count(i) * this->timeoj_[i]/this->generated_.count(i));
  return time;
}

double StatManager::dispTimeProcessing(int i){
  double time =(this->squaredTimepr_[i])/(double)this->sent_.count(i) -(this->timepr_[i]/(double)this->sent_.count(i) * this->timepr_[i]/(double)this->sent_.count(i));
  return time;
}

void StatManager::updateEvents(std::string str){
  this->Events_.push_back(str);
}

std::string StatManager::getEvents(){  
  std::string str = this->Events_.front();
  this->Events_.pop_front();
  return str;
}

void StatManager::clearEvents(){
  Events_.clear();
}

int StatManager::sizeEvents(){
  return Events_.size();
}

void StatManager::pushingAmount(int i, int k){
  // this->amountOnBuffers[i] 
}

StatManager::~StatManager(){
  delete[] this->refused_;
  delete[] this->timeoj_;
  delete[] this->timepr_;
  delete[] this->squaredTimeoj_;
  delete[] this->squaredTimepr_;
  delete[] this->amountOnBuffers;
}