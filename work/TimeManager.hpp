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
private:
  int sourceAmount_;
  int currentTime_;

  std::list<int> sent_;
  std::list<int> created_;
  std::list<int> time_;
  std::list<int> refused_;
};


#endif // !TIMEMANAGER_HPP
