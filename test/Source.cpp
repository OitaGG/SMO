#include "Source.hpp"

Source::Source(TimeManager* timeManager, int N) :
  timeManager(timeManager), amount_(N), time_(0) {
    sourcesArray_ = new int[amount_];
    for(int i = 0; i < amount_; i++){
      sourcesArray_[i] = -1;
    }
}