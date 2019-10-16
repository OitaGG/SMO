#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "BaseElement.hpp"

class Device: public BaseElement
{
public:
  Device(/* args */);
  ~Device();

  void init(BaseElement * buffer) override;
  void get(int i) override;
  void send(int i) override;
  void getInfo() override;
  bool empty() override;
  
  void generate();

private:
  /* data */
};


#endif // !DEVICE_HPP