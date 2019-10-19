#ifndef STATMANAGER_HPP
#define STATMANAGER_HPP

#include "iostream"

#include <map>
#include <list>

class StatManager
{
public:
  StatManager(int F);

  void sourceChecked(int i);
  void sourceGenerate(int i, double t);
  void bufferGetFromSource(int i);
  void bufferForced(int i, int k);
  void deviceGetFromBuffer(int i);
  void deviceDone(int i, double t);

  int generatedSize();
  int refusedSize();
  int sentSize();

  void printResult();
  ~StatManager() = default;
private:
  std::multimap<int,double> generated_;
  std::list<int> refused_;
  std::multimap<int,double> sent_;
  int F_;
};

#endif // !STATMANAGER_HPP