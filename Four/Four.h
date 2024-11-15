#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Four.h"
#include "ControlFour.h"
#include "Include/Dask64.h"
#include <conio.h>
#include <iostream>

class Four : public QMainWindow
{
    Q_OBJECT

public:
    Four(QWidget* parent = nullptr);

    void InitializeCard();
    void readTension();

private:
    Ui::FourClass ui;
    I16 cardId;

    bool isHeating;
    double temp;
    double consigne;
    int puissance;
    int intervalleEchantillon;

    QTimer* sampleTimer;

    ControlFour controlFour;

public slots:

    void OnFourButtonClicked();

    void startHeat();
    void stopHeat();

    void SetPower(int value);
    void SetConsigne(int value);

    void EchantillonageTemperature();
};
