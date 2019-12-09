#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "./TimeManager.hpp"
#include "./StatManager.hpp"
#include <list>
#include <iostream>
#include <vector>

class Buffer
{
public:
  Buffer(TimeManager* timeManager, StatManager* statManager, int N);

  void set(int i, double t);
  void force(int i, double t);

  int get();
  
  bool isReady();
  bool isEmpty();


  int getFreePlaceForSet();
  int getPlaceForForce();
  int getPlaceForDevice();
  void clearPlace(int i);
  
  // для пошагового режима
  double getBuffInfo(int i);
  int getRequestInBuff(int i);

private:
  int amount_;
  std::vector<int> BufferArray_;
  std::vector<double> BufferTime_;
  
  TimeManager* timeManager_;
  StatManager* statManager_;
};

#endif // !BUFFER_HPP
