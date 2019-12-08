#ifndef INTERFACE_AUTO_HPP
#define INTERFACE_AUTO_HPP

#include <QWidget>
#include <QTableWidget>
#include "../ModulingUnit.hpp"

class Auto : public QWidget
{
public:
    Auto(int nSources, int nDevices, ModulingUnit *unit);
private:
    QTableWidget *tables[2];
    ModulingUnit *unit;
};

#endif