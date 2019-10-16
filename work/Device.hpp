#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "Buffer.hpp"
#include "TimeManager.hpp"
#include <math.h>
#include <cmath>
#include <iostream>

class Device
{
public:
  Device(TimeManager* timeManager, int N);

  void work();
  void get(int i);
  int getFreePlaces();
  void getTime();
  void free();
  int fxRule();
  bool done();

  ~Device();  
private:
  TimeManager* timeManager_;
  Buffer* buffer_;
  int amount_;
  int time_;
  int* devicesArray_;
  int* wait_;
};


#endif // !DEVICE_HPP
