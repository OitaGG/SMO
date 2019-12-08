#include "../../include/interface/Manual.hpp"
#include <QGridLayout>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

Manual::Manual(int nSources, int nBuffer, int nDevices, ModulingUnit *unit)
{
    this->unit = unit;
    this->nDev = nDevices;
    this->nBuff = nBuffer;
    this->button = new QPushButton(tr("Сделать шаг"));
    QGridLayout *mainLayout = new QGridLayout();
    

    this->tables[0] = new QTableWidget(nBuffer, 4);
    // //Заполнение
    this->tables[0]->setHorizontalHeaderLabels(
        QStringList()<< "Состояние"
        << "Время заявки"
        << "С какого ист."
        << "Кол-во заявок с него");
    mainLayout->addWidget(this->tables[0], 0, 0);
    for (int i = 0; i < nBuffer; i++)
    {
        this->tables[0]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Free")));
        this->tables[0]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg("NaN")));
        this->tables[0]->setItem(i, 2, new QTableWidgetItem(tr("%1").arg("NaN")));
        this->tables[0]->setItem(i, 3, new QTableWidgetItem(tr("%1").arg("NaN")));
    }
    
    this->tables[1] = new QTableWidget(nDevices, 2);
    this->tables[1]->setHorizontalHeaderLabels(
        QStringList()<< "Состояние"
        << "Время заявки");
    for (int i = 0; i < nDevices; i++)
    {
        this->tables[1]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Free")));
        this->tables[1]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg("NaN")));
    }
    mainLayout->addWidget(this->tables[1], 0, 1);
    

    this->tables[2] = new QTableWidget(1, 1);
    this->tables[2]->setHorizontalHeaderLabels(
        QStringList()<< "Событие");
    for (int i = 0; i < nBuffer; i++)
    {
        this->tables[2]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Nothing")));
    }
    mainLayout->addWidget(this->tables[2],1,0);

    this->formGroupBox = new QGroupBox(tr("Текущее состояние"));
    QFormLayout *layout = new QFormLayout;

    this->lineEdits[0] = new QLabel("0.0");
    this->lineEdits[1] = new QLabel("0");

    layout->addRow(new QLabel(tr("Время:")), this->lineEdits[0]);
    layout->addRow(new QLabel(tr("Шаг:")), this->lineEdits[1]);

    this->formGroupBox->setLayout(layout);

    mainLayout->addWidget(this->formGroupBox,1,1);

    mainLayout->addWidget(this->button,2,0,2,2);

    connect(this->button,
            &QPushButton::clicked, this, &Manual::check);

    this->setLayout(mainLayout);
}

void Manual::check()
{
    this->lineEdits[0]->setText(QString::fromStdString(std::to_string(this->unit->getTime())));
    this->unit->singularStep();
    this->updateTables();
    // this->unit->clearEvents();
}

void Manual::updateTables(){
    int k = unit->getSizeEvents();
    this->tables[2]->setRowCount(k);

    for(int i = 0; i < k; i++){
        this->tables[2]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg(QString::fromStdString(this->unit->updateInfo()))));
    }

    for (size_t i = 0; i < this->nDev; i++){
        double tmp = this->unit->getDevInfo(i);
        if(tmp == -1){
            this->tables[1]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Free")));
            this->tables[1]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg("NaN")));
        } else {
            this->tables[1]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Busy")));
            this->tables[1]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg(QString::fromStdString(std::to_string(tmp)))));
        }
    }

    for (size_t i = 0; i < this->nBuff; i++){
        double tmp = this->unit->getBuffInfo(i);
        std::cout<<"TMP"<<tmp<<std::endl;
        if(tmp == -1){
            this->tables[0]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Free")));
            this->tables[0]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg("NaN")));
            this->tables[0]->setItem(i, 2, new QTableWidgetItem(tr("%1").arg("NaN")));
            this->tables[0]->setItem(i, 3, new QTableWidgetItem(tr("%1").arg("NaN")));
        } else {
            this->tables[0]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Busy")));
            this->tables[0]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg(QString::fromStdString(std::to_string(tmp)))));
            this->tables[0]->setItem(i, 2, new QTableWidgetItem(tr("%1").arg(QString::fromStdString(std::to_string(this->unit->getRequestInBuff(i))))));
        }
    }
    
    
}

