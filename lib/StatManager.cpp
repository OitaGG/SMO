#include "../include/StatManager.hpp"
#include <string>

StatManager::StatManager(int amount, int sources, int devices, int buffer) : F_(amount), S_(sources), D_(devices), B_(buffer) {
  // refused - индекс это номер источника, зн-е - кол-во отклоненных
  this->refused_ = std::vector<int>(this->S_, 0);
  // timeoj_ - индекс - это номер источника, зн-е - время ожидания
  this->timeoj_ = std::vector<double>(this->S_, 0);
  // timepr_ - индекс - это номер источника, зн-е - время на приборе
  this->timepr_ = std::vector<double>(this->S_, 0);
  // squaredTimeoj_ - индекс - это номер источника, зн-е - сумма квадратов времени ожидания
  this->squaredTimeoj_ = std::vector<double>(this->S_, 0);
  // squaredTimepr_ - индекс - это номер источника, зн-е - сумма квадратов времени на приборе
  this->squaredTimepr_ = std::vector<double>(this->S_, 0);
  this->generatedCount_ = std::vector<int>(this->S_,0);
  this->generatedTime_ = std::vector<double>(this->S_, 0);
  // 1 зн-е - заявка, 2 - время
  this->generated_ = std::multimap<int,double>();
  this->sent_ = std::multimap<int,double>();
  this->workedTime_ = std::vector<double>(this->D_, 0);
  // для статистики
  this->Events_ = std::list<std::string>();
  this->deviceWorkedTasks_ = std::vector<int>(this->D_,0);
}

// пушим время на приборе и его квадрат для дисперсии
void StatManager::pushTimePr(int k, double t){
  this->timepr_[k] += t;
  this->squaredTimepr_[k] += t*t;
}

// пушим время ожидания и его квадрат для дисперсии
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

// количество отклоненных заявок
int StatManager::refusedSize(){
  int refSum = 0;
  for (size_t i = 0; i < this->S_; i++){
    refSum += this->refused_[i];
  }
  return refSum;
}

// буфер получил заявку с источника
void StatManager::bufferGetFromSource(int i, double t){
  std::string str = "Buffer get from Source №" + std::to_string(i);
  this->Events_.push_back(str);
}

// прибор забрал заявку с буфера
void StatManager::deviceGetFromBuffer(int i, double wait){
  std::string str = "Device get from Buffer with Source №" + std::to_string(i);
  this->Events_.push_back(str);
}

// прибор зарезолвил заявку
void StatManager::deviceDone(int i,int j, double t){
  std::string str = "Device №" + std::to_string(i) +" done";
  this->Events_.push_back(str);
  // по номеру заявки, вставляем зн-е времени
  this->workedTime_[j] += t;
  this->sent_.insert(std::make_pair(i,t));  
}

// заявку зафорсили
void StatManager::bufferForced(int i, int k){ 
  std::string str = "Buffer get from Source № " + std::to_string(i) + "and forced it instead " + std::to_string(k);
  this->Events_.push_back(str);
  this->refused_[k]++;
}

// заявка сгенерировалась
void StatManager::sourceGenerate(int i, double t){
  this->generatedCount_[i] += 1;
  this->generatedTime_[i] += t;
  this->generated_.insert(std::make_pair(i,t));
  std::string str = "Source " + std::to_string(i) + " generated"; 
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

// статистика для автоматического режима
StatsTableData *StatManager::getStats(double time){
  StatsTableData *toGive = new StatsTableData();
    double fail = 0;
    double procc = 0;
    double timein = 0;
    for (int i = 0; i < this->S_; i++){
        toGive->N.push_back(this->generatedCount_[i]);
        toGive->failureProb.push_back((double)this->refused_[i]/(double)this->generated_.count(i));
        fail += (double)this->refused_[i]/(double)this->generated_.count(i);
        toGive->avgTimeBeing.push_back((this->timeoj_[i] + this->timepr_[i])/(double)this->generated_.count(i));
        timein += (this->timeoj_[i] + this->timepr_[i])/(double)this->generated_.count(i);
        toGive->avgTimeWaiting.push_back(this->timeoj_[i]/(double)this->generated_.count(i));
        toGive->avgTimeProccessing.push_back(this->timepr_[i]/(double)this->sent_.count(i));
        toGive->dispTimeBeing.push_back(this->dispTimeBeing(i));
        toGive->dispTimeProccessing.push_back(dispTimeProcessing(i));
    }
    for (int i = 0; i < D_; i++){
        toGive->K.push_back(workedTime_[i]/time);
        procc += workedTime_[i]/time;
    }
    std::cout<<"Отказ"<<fail/this->S_<<std::endl;
    std::cout<<"Коэф занятости"<<procc/this->D_<<std::endl;
    std::cout<<"Время в системе"<<timein/this->S_<<std::endl;
    return toGive;
}
// для подсчета статистики
double StatManager::dispTimeBeing(int i){
  double time = (this->squaredTimeoj_[i])/(double)this->generated_.count(i) - (this->timeoj_[i]/this->generated_.count(i) * this->timeoj_[i]/this->generated_.count(i));
  return time;
}

double StatManager::dispTimeProcessing(int i){
  double time =(this->squaredTimepr_[i])/(double)this->sent_.count(i) -(this->timepr_[i]/(double)this->sent_.count(i) * this->timepr_[i]/(double)this->sent_.count(i));
  return time;
}

// пушим строки событий в календарь событий
void StatManager::updateEvents(std::string str){
  this->Events_.push_back(str);
}

// забираем событие из календаря событий
std::string StatManager::getEvents(){  
  std::string str = this->Events_.front();
  this->Events_.pop_front();
  return str;
}

// очищаем строки календаря событий 
void StatManager::clearEvents(){
  Events_.clear();
}

int StatManager::sizeEvents(){
  return Events_.size();
}

int StatManager::getRequestValue(){
  double count = 0;
  for (size_t i = 0; i < this->S_; i++){
    count += generatedCount_[i];
  }
  return count;
}

int StatManager::getSentValue(){
  return this->sent_.size();
}

int StatManager::getRequestAmount(){
  return this->F_;
}

void StatManager::deviceWorkedWithUpdate(int i){
  this->deviceWorkedTasks_[i] += 1;
}

int StatManager::deviceWorkedWithGet(int i){
  return this->deviceWorkedTasks_[i];
}