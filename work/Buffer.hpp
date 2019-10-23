#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "TimeManager.hpp"
#include "StatManager.hpp"
#include <list>
#include <iostream>

class Buffer
{
public:
  Buffer(TimeManager* timeManager, StatManager* statManager, int N);

  void set(int i, double t);
  int get();
  bool isReady();
  void force(int i, double t);
  bool isEmpty();


  ~Buffer() = default;
private:
  int amount_;
  std::list<int> bufferList_;
  std::list<double> bufferListTime_;
  TimeManager* timeManager_;
  StatManager* statManager_;
};

#endif // !BUFFER_HPP
