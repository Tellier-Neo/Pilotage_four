#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Four.h"
#include "Include/Dask64.h"
#include <conio.h>
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <vector>

class Four : public QMainWindow
{
    Q_OBJECT

public:
    Four(QWidget *parent = nullptr);

    void InitializeCard();
    void ReadTension();
    void ReadTemperature();
    void UpdateGraph(double temperature);

    ~Four();

private:
    Ui::FourClass ui;
    I16 cardId;

    bool isHeating;
    double temp;
    double consigne;
    int puissance;
    int intervalleEchantillon;

    QTimer* sampleTimer;

    QGraphicsScene* graphScene;  
    std::vector<QPointF> dataPoints;  
    double timeElapsed;

public slots:

    void OnFourButtonClicked();

    void startHeat();
    void stopHeat();

    void SetPower(int value);
    void SetConsigne(int value);

    void UpdateStatutChauffage();
};
