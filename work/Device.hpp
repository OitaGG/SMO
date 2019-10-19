#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "Buffer.hpp"
#include "TimeManager.hpp"
#include "StatManager.hpp"
#include <math.h>
#include <cmath>
#include <iostream>

class Device
{
public:
  Device(TimeManager* timeManager, Buffer* buffer, StatManager* statManager, int N);

  void work();
  void get(int i);
  int getFreePlaces();
  void getTime();
  void free();
  double fxRule();
  int recievePlace();
  bool done();

  ~Device();  
private:
  TimeManager* timeManager_;
  Buffer* buffer_;
  StatManager* statManager_;
  int amount_;
  double time_;
  int* devicesArray_;
  double* wait_;
};


#endif // !DEVICE_HPP
