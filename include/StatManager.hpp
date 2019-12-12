#ifndef STATMANAGER_HPP
#define STATMANAGER_HPP

#include <iostream>
#include <iomanip>
#include <iterator>

#include <map>
#include <list>
#include <vector>


struct StatsTableData
{
    std::vector<int> N;
    std::vector<double> failureProb;
    std::vector<double> avgTimeBeing;
    std::vector<double> avgTimeWaiting;
    std::vector<double> avgTimeProccessing;
    std::vector<double> dispTimeBeing;
    std::vector<double> dispTimeProccessing;
    std::vector<double> K;
};

class StatManager
{
public:
  StatManager(int amount, int sources, int devices, int buffer);

  void sourceGenerate(int i, double t);
  void bufferGetFromSource(int i, double t);
  void bufferForced(int i, int k);
  void deviceGetFromBuffer(int i, double wait);
  void deviceDone(int i, int j, double t);
  void pushTimeOj(int k,double t);
  void pushTimePr(int k, double t);

  int generatedSize();
  int refusedSize();
  int sentSize();

  double statForMultimap(int Flag);
  StatsTableData *getStats(double time);
  void updateEvents(std::string str);
  std::string getEvents();
  int sizeEvents();
  void clearEvents();
  double dispTimeBeing(int i);
  double dispTimeProcessing(int i);
  int getRequestValue();
  int getSentValue();
  int getRequestAmount();
  void deviceWorkedWithUpdate(int i);
  int deviceWorkedWithGet(int i);
  ~StatManager();
private:
  int S_;
  int D_;
  int B_;
  std::vector<double> workedTime_;
  std::multimap<int,double> generated_;
  std::multimap<int,double> sent_;
  std::vector<double> timeoj_;
  std::vector<double> squaredTimeoj_;
  std::vector<double> timepr_;
  std::vector<double> squaredTimepr_;
  std::vector<int> refused_;
  std::vector<int> generatedCount_;
  std::vector<double> generatedTime_;
  std::vector<int> deviceWorkedTasks_;
  int F_;
  std::list<std::string> Events_;
};

#endif // !STATMANAGER_HPP