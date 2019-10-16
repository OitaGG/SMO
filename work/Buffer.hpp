#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "TimeManager.hpp"
#include <list>
#include <iostream>

class Buffer
{
public:
  Buffer(TimeManager* timeManager, int N);

  void set(int i);
  void get(int i);
  bool isReady();
  void force(int i);
  bool isEmpty();

  ~Buffer();
private:
  int amount_;
  std::list<int> bufferList_;
  TimeManager* timeManager_;
};

#endif // !BUFFER_HPP
