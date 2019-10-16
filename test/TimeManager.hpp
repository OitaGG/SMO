#ifndef TIMEMANAGER_HPP
#define TIMEMANAGER_HPP

#include <list>

class TimeManager
{
public:
  TimeManager(int amount);
  ~TimeManager();

  void next();
  bool done();

  int getCurrentTime();
  void addNewTime(int t);
  void sent();
  void created();
  void refused();
  
private:
  int sourcesAmount_;
  int currentTime_;

  std::list<int> sent_;
  std::list<int> created_;
  std::list<int> time_;
  std::list<int> refused_;
};


#endif // !TIMEMANAGER_HPP
