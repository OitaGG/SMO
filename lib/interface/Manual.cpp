#include "../../include/interface/Manual.hpp"
#include <QGridLayout>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

Manual::Manual(int nSources, int nBuffer, int nDevices, ModulingUnit *unit){
    this->step_ = 0;
    this->successfull = true;
    this->unit = unit;
    this->nDev = nDevices;
    this->nBuff = nBuffer;

    this->button = new QPushButton(tr("Начать"));
    QGridLayout *mainLayout = new QGridLayout();

    // таблица для буфера
    // this->formGroupBoxTableOne = new QGroupBox(tr("Buffer"));
    // QFormLayout *layoutTable = new QFormLayout;

    this->tables[0] = new QTableWidget(nBuffer, 4);
    this->tables[0]->setHorizontalHeaderLabels(
        QStringList()<< "Состояние"
        << "Время заявки"
        << "С какого ист."
        << "Время на буф");
    // layoutTable->addWidget(this->tables[0]);
    // this->formGroupBoxTableOne->setLayout(layoutTable);
    // mainLayout->addWidget(this->formGroupBoxTableOne);
    mainLayout->addWidget(this->tables[0],0,0);

    for (int i = 0; i < nBuffer; i++){
        this->tables[0]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Free")));
        this->tables[0]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg("NaN")));
        this->tables[0]->setItem(i, 2, new QTableWidgetItem(tr("%1").arg("NaN")));
        this->tables[0]->setItem(i, 3, new QTableWidgetItem(tr("%1").arg("NaN")));
    }
    
    // таблица для приборов
    this->tables[1] = new QTableWidget(nDevices, 3);
    this->tables[1]->setHorizontalHeaderLabels(
        QStringList()<< "Состояние"
        << "Время заявки"
        <<"Обработано заявок");
    for (int i = 0; i < nDevices; i++){
        this->tables[1]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Free")));
        this->tables[1]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg("NaN")));
        this->tables[1]->setItem(i, 2, new QTableWidgetItem(tr("%1").arg("NaN")));
    }
    mainLayout->addWidget(this->tables[1], 0, 1);
    
    // таблица "Календарь событий"
    this->tables[2] = new QTableWidget(1, 1);
    this->tables[2]->setHorizontalHeaderLabels(
        QStringList()<< "Событие");
    for (int i = 0; i < nBuffer; i++){
        this->tables[2]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Nothing")));
    }
    mainLayout->addWidget(this->tables[2],1,0);

    // текущее время и шаг
    this->formGroupBox = new QGroupBox(tr("Текущее состояние"));
    QFormLayout *layout = new QFormLayout;
    this->lineEdits[0] = new QLabel("0.0");
    this->lineEdits[1] = new QLabel("0");
    this->lineEdits[2] = new QLabel("0");
    this->lineEdits[3] = new QLabel("0");
    layout->addRow(new QLabel(tr("Время в системе:")), this->lineEdits[0]);
    layout->addRow(new QLabel(tr("Шаг в системе:")), this->lineEdits[1]);
    layout->addRow(new QLabel(tr("Кол-во сгенерированных заявок")), this->lineEdits[2]);
    layout->addRow(new QLabel(tr("Кол-во успешно отправленных заявок")), this->lineEdits[3]);


    this->formGroupBox->setLayout(layout);

    mainLayout->addWidget(this->formGroupBox,1,1);

    mainLayout->addWidget(this->button,2,0,2,2);

    connect(this->button,
            &QPushButton::clicked, this, &Manual::check);

    this->setLayout(mainLayout);
}

void Manual::check()
{
    if(this->successfull){
        currentSystemInfo();
        // один шаг
        this->successfull = this->unit->singularStep();
        // обновление таблиц
        this->updateStep();
        this->updateTables();
        this->lineEdits[2]->setText(QString::fromStdString(std::to_string(this->unit->getRequestValue())));
        this->lineEdits[3]->setText(QString::fromStdString(std::to_string(this->unit->getSentValue())));
    } else {
        this->button->setText("Симуляция окончена!");
    }
}

void Manual::currentSystemInfo(){
    this->lineEdits[0]->setText(QString::fromStdString(std::to_string(this->unit->getTime())));
    this->lineEdits[1]->setText(QString::fromStdString(std::to_string(this->step_)));
}
void Manual::updateTables(){
    this->button->setText("Сделать шаг");
    // смотрим количество событий
    int k = unit->getSizeEvents();
    // устанавливаем количество строк = кол-ву событий и заполняем
    this->tables[2]->setRowCount(k);
    for(int i = 0; i < k; i++){
        this->tables[2]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg(QString::fromStdString(this->unit->updateInfo()))));
    }
//     обновляем таблицу приборов
    for (size_t i = 0; i < this->nDev; i++){
        double tmp = this->unit->getDevInfo(i);
        if(tmp == -1){
            this->tables[1]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Free")));
            this->tables[1]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg("NaN")));
        } else {
            this->tables[1]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Busy")));
            this->tables[1]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg(QString::fromStdString(std::to_string(tmp)))));
        }
        this->tables[1]->setItem(i, 2, new QTableWidgetItem(tr("%1").arg(QString::fromStdString(std::to_string(this->unit->getWorkedTasksForDevice(i))))));
    }
//     обновляем таблицу буфера
    for (size_t i = 0; i < this->nBuff; i++){
        double tmp = this->unit->getBuffInfo(i);
        if(tmp == -1){
            this->tables[0]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Free")));
            this->tables[0]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg("NaN")));
            this->tables[0]->setItem(i, 2, new QTableWidgetItem(tr("%1").arg("NaN")));
            this->tables[0]->setItem(i, 3, new QTableWidgetItem(tr("%1").arg("NaN")));
        } else {
            this->tables[0]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg("Busy")));
            this->tables[0]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg(QString::fromStdString(std::to_string(tmp)))));
            this->tables[0]->setItem(i, 2, new QTableWidgetItem(tr("%1").arg(QString::fromStdString(std::to_string(this->unit->getRequestInBuff(i))))));
            this->tables[0]->setItem(i, 3, new QTableWidgetItem(tr("%1").arg(QString::fromStdString(this->unit->getTimeInBuff(i)))));
        }
    }
        
}

void Manual::updateStep(){
    this->step_++;
}