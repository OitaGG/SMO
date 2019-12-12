#include "iostream"
#include "../include/ModulingUnit.hpp"
#include <QDebug>

ModulingUnit::ModulingUnit(int nSources, int nBuffer, int nDevices, int amount, double labmda, double a, double b)
{
    srand(time(NULL));
    this->amount = amount;
    this->sourceTime = 0;
    this->deviceTime = 0;
    this->statManager = new StatManager(amount, nSources, nDevices, nBuffer);
    this->timeManager = new TimeManager(amount, this->statManager);
    this->buffer = new Buffer(this->timeManager, this->statManager, nBuffer);
    this->source = new Source(this->timeManager, this->buffer, this->statManager, nSources,a,b);
    this->device = new Device(this->timeManager, this->buffer, this->statManager, nDevices, labmda);
}

void ModulingUnit::fullyModulate()
{
    while (!(this->timeManager->done()) || !this->source->done() || !this->buffer->isEmpty() || !this->device->done()) {
		this->source->work();
		this->device->work();
		this->timeManager->work();
	}
}

StatsTableData *ModulingUnit::getStats()
{
    return this->statManager->getStats(this->timeManager->getCurrentTime());
}

bool ModulingUnit::singularStep()
{
    if(!(this->timeManager->done()) || !this->source->done() || !this->buffer->isEmpty() || !this->device->done())
    {
        this->source->work();
        this->device->work();
        this->buffer->updatePreviouslyTime();
        this->timeManager->work();
        // this->updateInfo();
        return true;
    }
    return false;
}

std::string ModulingUnit::updateInfo(){
    return statManager->getEvents();
}

void ModulingUnit::clearEvents(){
    this->statManager->clearEvents();
}

double ModulingUnit::getTime(){
    return timeManager->getCurrentTime();
}

int ModulingUnit::getSizeEvents(){
    return statManager->sizeEvents();
}

double ModulingUnit::getDevInfo(int i){
    return device->getDevInfo(i);
}

double ModulingUnit::getBuffInfo(int i){
    return buffer->getBuffInfo(i);
}

int ModulingUnit::getRequestInBuff(int i){
    return buffer->getRequestInBuff(i);
}

std::string ModulingUnit::getTimeInBuff(int i){
    double time = this->buffer->getTimeInBuff(i);
    if(time != -1)
        return std::to_string(time);
    return "Nan";
}

int ModulingUnit::getRequestValue(){
    return statManager->getRequestValue();
}

int ModulingUnit::getSentValue(){
    return statManager->getSentValue();
}

int ModulingUnit::getWorkedTasksForDevice(int i){
    return this->statManager->deviceWorkedWithGet(i);
}