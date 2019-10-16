#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "Buffer.hpp"
#include "TimeManager.hpp"

class Device
{
public:
  Device(TimeManager* timeManager, int N);

  void work();
  ~Device();  
private:
  /* data */
};


#endif // !DEVICE_HPP