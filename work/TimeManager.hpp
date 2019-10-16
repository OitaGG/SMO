#ifndef TIMEMANAGER_HPP
#define TIMEMANAGER_HPP

#include <list>

class TimeManager
{
public:
  TimeManager(int amount);

  void work();
  bool done();

  int getCurrentTime();
  void addNewTime(int t);
  void sent(int i);
  void created(int i);
  void refused(int i);

  ~TimeManager() = default;
private:
  int sourcesAmount_;
  int currentTime_;

  std::list<int> sent_;
  std::list<int> created_;
  std::list<int> time_;
  std::list<int> refused_;
};

#endif // !TIMEMANAGER_HPP
