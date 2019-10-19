#include "StatManager.hpp"

StatManager::StatManager(int F) : F_(F) {
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
  std::cout<<"-Source №" << i << " checked."<<std::endl;
}

void StatManager::bufferGetFromSource(int i){
  std::cout<<"->Buffer get request from Source №"<<i<<std::endl;
}

void StatManager::deviceGetFromBuffer(int i){
  std::cout<<"->->Device get request №"<<i<<std::endl;
}

void StatManager::deviceDone(int i, double t){
  std::cout<<"->->**Device done with request №"<<i<<" and time "<<t<<std::endl;
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

void StatManager::printResult(){
  std::cout<<"Created: "<<generated_.size()<<std::endl;
  std::cout<<"Sent: "<<sent_.size()<<std::endl;
  std::cout<<"Refused: "<<refused_.size()<<std::endl;
}