#ifndef BASEELEMENT_HPP
#define BASEELEMENT_HPP

class BaseElement{
  virtual void init(BaseElement * obj) = 0;
  virtual void get(int i) = 0;
  virtual void send(int i) = 0;
  virtual void getInfo() = 0;
  virtual bool empty();
};

#endif // !BASEELEMENT_HPP
