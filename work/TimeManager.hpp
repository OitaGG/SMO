#ifndef TIMEMANAGER_HPP
#define TIMEMANAGER_HPP

#include "StatManager.hpp"
#include <list>
#include <iostream>

class TimeManager
{
public:
  TimeManager(int amount, StatManager* statManager);

  void work();
  bool done();

  double getCurrentTime();
  void addNewTime(double t);

  ~TimeManager() = default;
private:
  StatManager* statManager_;
  int sourcesAmount_;
  double currentTime_;

  std::list<double> time_;
};

#endif // !TIMEMANAGER_HPP
