#include "StatManager.hpp"

StatManager::StatManager(int F, int S, int D) : F_(F), S_(S), D_(D) {
  this->refused_ = new int[this->S_];
  this->timeoj_ = new double[this->S_];
  this->timepr_ = new double[this->S_];
  for (size_t i = 0; i < this->S_; i++){
    this->refused_[i] = 0;
    this->timeoj_[i] = 0;
    this->timepr_[i] = 0;
  }  
  this->generated_ = std::multimap<int,double>();
  this->sent_ = std::multimap<int,double>();
}

void StatManager::pushTimePr(int k, double t){
  this->timepr_[k] += t;
}

void StatManager::pushTimeOj(int k,double t){
  this->timeoj_[k] += t;
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

void StatManager::bufferGetFromSource(int i){
  std::cout<<"Source "<<i<<" ---->Buffer"<<std::endl;
}

void StatManager::deviceGetFromBuffer(int i, double wait){
  std::cout<<"Buffer ----> Device @@Source "<<i<<"@@ with time "<<wait<<" seconds"<<std::endl;
}

void StatManager::deviceDone(int i, double t){
  std::cout<<"Device ----> DONE at time "<<t<<std::endl;
  // this->pushTimePr(i,t);
  this->sent_.insert(std::make_pair(i,t));  
}

void StatManager::bufferForced(int i, int k){ 
  std::cout<<"Source "<<i<<" ---->Buffer and forced it instead request №"<<k<<std::endl;  
  this->refused_[k]++;
}
void StatManager::sourceGenerate(int i, double t){
  std::cout<<"Source " << i << "----> Generate at time "<< t <<std::endl;
  this->generated_.insert(std::make_pair(i,t));
} 

double StatManager::statForMultimap(int i, int Flag){
  std::pair <std::multimap<int,double>::iterator, std::multimap<int,double>::iterator> ret;
  Flag == 0 ? ret = generated_.equal_range(i) : ret = sent_.equal_range(i); 
  double average = 0.0;
  for(auto it = ret.first; it != ret.second; ++it){
    average += it->second;
  }
  return average;
}
void StatManager::printResult(){
  std::cout<<"Requsests value == "<<this->generatedSize()<<std::endl;
  std::cout<<"-----------------------------------"<<std::endl;
  double Kisp = 0;
  for(auto i = 0; i < this->S_; i++){
    std::cout<<"SOURCE № "<<i<<"| ALL: "<<this->generated_.count(i)<<"| REF: "<< this->refused_[i];
    std::cout<<std::fixed<<std::setprecision(2)<<"| Potk: "<<((double)this->refused_[i]/(double)this->generated_.count(i));
    std::cout<<std::fixed<<std::setprecision(2)<<"| Tis: "<<(this->timeoj_[i] + this->timepr_[i])/(double)this->generated_.count(i);
    std::cout<<std::fixed<<std::setprecision(2)<<"| Toj: "<<this->timeoj_[i]/(double)this->generated_.count(i);
    std::cout<<std::fixed<<std::setprecision(2)<<"| Tobs: "<<this->timepr_[i]/(double)this->sent_.count(i);
    std::cout<<std::endl;
    Kisp += timepr_[i];
  }
  std::cout<<std::fixed<<std::setprecision(2)<<"| Kisp: "<<Kisp<<std::endl;
  
  
  std::cout<<"Sent value == "<<this->sentSize()<<std::endl;
  std::cout<<"-----------------------------------"<<std::endl;  
}