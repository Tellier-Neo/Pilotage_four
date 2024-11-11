#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Four.h"
#include "ControlFour.h"

class Four : public QMainWindow
{
    Q_OBJECT

public:
    Four(QWidget *parent = nullptr);

private:
    Ui::FourClass ui;
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
