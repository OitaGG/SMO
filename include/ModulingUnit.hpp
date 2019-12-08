#ifndef MODULING_UNIT
#define MODULING_UNIT

#include "StatManager.hpp"
#include "Buffer.hpp"
#include "Source.hpp"
#include "Device.hpp"
#include "TimeManager.hpp"


class ModulingUnit
{
private:
    double sourceTime;
    double deviceTime;
    bool mode;
    int amount;
    StatManager *manager;

    Device *device;
    Source *source;
    Buffer *buffer;
    StatManager *statManager;
    TimeManager *timeManager;

public:
    ModulingUnit(int nSources, int nBuffer, int nDevices, int amount, double labmda, double a, double b);
    void singularStep();
    StatsTableData *getStats();
    void fullyModulate();
    std::string updateInfo();
    void clearEvents();
    double getTime();
    int getSizeEvents();
    double getDevInfo(int i);
    double getBuffInfo(int i);
    int getRequestInBuff(int i);
};

#endif // MODULING_UNIT
