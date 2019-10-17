#ifndef TIMEMANAGER_HPP
#define TIMEMANAGER_HPP

#include <list>
#include <iostream>

class TimeManager
{
public:
  TimeManager(int amount);

  void work();
  bool done();

  double getCurrentTime();
  void addNewTime(double t);
  void sent(int i);
  void created(int i);
  void refused(int i);
  void printInfo();

  ~TimeManager() = default;
private:
  int sourcesAmount_;
  double currentTime_;

  std::list<int> sent_;
  std::list<int> created_;
  std::list<double> time_;
  std::list<int> refused_;
};

#endif // !TIMEMANAGER_HPP
