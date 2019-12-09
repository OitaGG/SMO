#ifndef INTERFACE_MANUAL_HPP
#define INTERFACE_MANUAL_HPP

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include "../ModulingUnit.hpp"

class Manual : public QWidget
{
public:
    Manual(int nSources, int nBuffer, int nDevices, ModulingUnit *unit);
    void updateTables();
private:
    void check();
    QPushButton *button;
    ModulingUnit *unit;
    QTableWidget *tables[3];
    QGroupBox *formGroupBox;
    QLabel *lineEdits[2];
    int nDev;
    int nBuff;
};

#endif
