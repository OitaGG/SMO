#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "./Buffer.hpp"
#include "./TimeManager.hpp"
#include "./StatManager.hpp"
#include <math.h>
#include <iostream>
#include <cmath>
#include <vector>
class Source
{
public:
  Source(TimeManager* timeManager, Buffer* buffer, StatManager* statManager, int N, double a, double b);
  void work();

  void generate();
  void send(int i, double t);
  double fxRule();

  void set(int i);
  void free(int i);
  void check();

  bool done();  
  ~Source();
private:
  TimeManager* timeManager;
  Buffer* buffer_;
  StatManager* statManager_;
  int sourceNumber_;
  std::vector<double> sourcesArray_;
  int amount_;
  double time_;
  double Lambda, Betta;
  int currentAmount_;
};

#endif // !SOURCE_HPP
