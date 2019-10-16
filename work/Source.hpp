#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "BaseElement.hpp"
#include "TimeManager.hpp"


class Source: public BaseElement
{
public:
  Source(int n);
  ~Source();

  void init(BaseElement * buffer) override;
  void get(int i) override;
  void send(int i) override;
  void getInfo() override;

private:
  int sourceNumber_;
  int * sourcesArray_;
  int amount_;
  int time_;

  TimeManager * timeManager;
  BaseElement * buffer;
};

#endif // !SOURCE_HPP
