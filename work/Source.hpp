#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "Buffer.hpp"
#include "TimeManager.hpp"
#include "StatManager.hpp"
#include <math.h>
#include <iostream>
#include <cmath>

class Source
{
public:
  Source(TimeManager* timeManager, Buffer* buffer, StatManager* statManager, int N);
  
  void generate();
  void send(int i);

  double fxRule();
  void set(int i);
  void free(int i);
  void work();
  void check();
  bool done();
  
  ~Source();
private:
  TimeManager* timeManager;
  Buffer* buffer_;
  StatManager* statManager_;

  int sourceNumber_;
  double* sourcesArray_;
  int amount_;
  double time_;
};

#endif // !SOURCE_HPP
