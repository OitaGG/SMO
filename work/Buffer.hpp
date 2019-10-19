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

  void set(int i);
  int get();
  bool isReady();
  void force(int i);
  bool isEmpty();


  ~Buffer() = default;
private:
  int amount_;
  std::list<int> bufferList_;
  TimeManager* timeManager_;
  StatManager* statManager_;
};

#endif // !BUFFER_HPP
