#ifndef STATMANAGER_HPP
#define STATMANAGER_HPP

#include "iostream"
#include <iomanip>
#include <iterator>

#include <map>
#include <list>

class StatManager
{
public:
  StatManager(int F, int S, int D);

  void sourceGenerate(int i, double t);
  void bufferGetFromSource(int i);
  void bufferForced(int i, int k);
  void deviceGetFromBuffer(int i, double wait);
  void deviceDone(int i, double t);
  void pushTimeOj(int k,double t);
  void pushTimePr(int k, double t);

  int generatedSize();
  int refusedSize();
  int sentSize();

  void printResult();
  double statForMultimap(int i, int Flag);
  ~StatManager() = default;
private:
  int S_;
  int D_;
  std::multimap<int,double> generated_;
  std::multimap<int,double> sent_;
  double* timeoj_;
  double* timepr_;
  int* refused_;
  int F_;
};

#endif // !STATMANAGER_HPP