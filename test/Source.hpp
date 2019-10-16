#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "Buffer.hpp"
#include "TimeManager.hpp"

class Source
{
public:
  Source(TimeManager* timeManager, int N);
  ~Source();
  
  void generate();
  void send(int i);
  void get(int i);
  void getInfo();

  int fxRule();
  void set(int i);
  void free(int i);
  void work();

  bool done();

private:
  int sourceNumber_;
  int* sourcesArray_;
  int amount_;
  int time_;

  TimeManager* timeManager;
};

#endif // !SOURCE_HPP
