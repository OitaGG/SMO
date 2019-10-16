#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "Buffer.hpp"
#include "TimeManager.hpp"
#include <math.h>
#include <iostream>
#include <cmath>

class Source
{
public:
  Source(TimeManager* timeManager, int N);
  
  void generate();
  void send(int i);

  int fxRule();
  void set(int i);
  void free(int i);
  void work();
  void check();
  void getTime();
  bool done();
  
  ~Source();
private:
  TimeManager* timeManager;
  Buffer* buffer_;

  int sourceNumber_;
  int* sourcesArray_;
  int amount_;
  int time_;
};

#endif // !SOURCE_HPP
