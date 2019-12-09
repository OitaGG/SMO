#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "./Buffer.hpp"
#include "./TimeManager.hpp"
#include "./StatManager.hpp"
#include <math.h>
#include <cmath>
#include <iostream>
#include <vector>

class Device
{
public:
  Device(TimeManager* timeManager, Buffer* buffer, StatManager* statManager, int N, double Lambda);

  void work();
  void get(int i);
  int getFreePlaces();
  void free();
  double fxRule();
  void getTime();
  int recievePlace();

  bool done();
  // для статистики
  double getDevInfo(int i);

  ~Device();
private:
  TimeManager* timeManager_;
  Buffer* buffer_;
  StatManager* statManager_;

  int amount_;
  double time_;
  
  std::vector<int> devicesArray_;
  std::vector<double> waitFor_;
  std::vector<double> wait_;


  double Lambda_;
};

#endif // !DEVICE_HPP
