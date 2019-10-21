#include "StatManager.hpp"

StatManager::StatManager(int F, int S, int D) : F_(F), S_(S), D_(D) {
  refused_ = std::list<int>();
  generated_ = std::multimap<int,double>();
  sent_ = std::multimap<int,double>();
}

int StatManager::generatedSize(){
  return generated_.size();
}

int StatManager::sentSize(){
  return sent_.size();
}

int StatManager::refusedSize(){
  return refused_.size();
}

void StatManager::sourceChecked(int i){
  // std::cout<<"-Source №" << i << " checked."<<std::endl;
}

void StatManager::bufferGetFromSource(int i){
  std::cout<<"->Buffer get request from Source №"<<i<<std::endl;
}

void StatManager::deviceGetFromBuffer(int i, double wait){
  std::cout<<"->->Device get request №"<<i<<" For "<<wait<<" seconds"<<std::endl;
}

void StatManager::deviceDone(int i, double t){
  std::cout<<"->->**Device done with request №"<<i<<" at time "<<t<<std::endl;
  sent_.insert(std::make_pair(i,t));  
}

void StatManager::bufferForced(int i, int k){ 
  std::cout<<"->*Buffer get request from Source №"<<i<<" and forced it instead request №"<<k<<std::endl;  
  refused_.push_back(k);
}
void StatManager::sourceGenerate(int i, double t){
  std::cout<<"--Source №" << i << " will created at "<< t <<std::endl;
  generated_.insert(std::make_pair(i,t));
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
  std::cout<<"Requsests value == "<<generatedSize()<<std::endl;
  std::cout<<"-----------------------------------"<<std::endl;
  for(auto i = 0; i < S_; i++){
    std::cout<<"Request from "<<i<<" source == "<<generated_.count(i)<<std::endl;
    std::cout<<"Average for "<<i<<" source == "<<statForMultimap(i, 0)/generated_.count(i)<<std::endl;
  }
  std::cout<<"-----------------------------------"<<std::endl;
  std::cout<<"Sent value == "<<sentSize()<<std::endl;
  for(auto i = 0; i < D_; i++){
    std::cout<<"Request from "<<i<<" source == "<<sent_.count(i)<<std::endl;
    std::cout<<"Average Time on "<<i<<" device == "<<statForMultimap(i, 1)/sent_.count(i)<<std::endl;
  }

}