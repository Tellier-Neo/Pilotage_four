#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QTimer>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      currentTemp(20.0),  // Température initiale (température ambiante)
      consigne(65.0),     // Consigne par défaut
      puissance(0),       // Puissance initiale
      heatTimer(new QTimer(this))
{
    ui->setupUi(this);

    // Connexions de l'interface
    sliderPuissance = ui->sliderPuissance;
    labelTemp = ui->labelTemp;
    labelConsigne = ui->labelConsigne;
    startButton = ui->startButton;
    chartView = ui->chartView;

    // Configuration du graphique
    series = new QLineSeries();
    chart = new QChart();
    chart->addSeries(series);
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);
    axisX->setRange(0, 100);  // Plage pour l'axe X (temps)
    axisY->setRange(0, 100);  // Plage pour l'axe Y (température)
    chartView->setChart(chart);

    // Timer pour la mise à jour de la température
    connect(heatTimer, &QTimer::timeout, this, &MainWindow::updateTemperature);

    // Mise à jour du label de la consigne
    labelConsigne->setText(QString("Consigne : %1°C").arg(consigne));
}

MainWindow::~MainWindow() {
    delete heatTimer;
    delete series;
    delete chart;
    delete axisX;
    delete axisY;
}

void MainWindow::startHeating() {
    // Démarre ou arrête la chauffe selon l'état actuel
    if (heatTimer->isActive()) {
        heatTimer->stop();
        startButton->setText("Start Heating");
    } else {
        heatTimer->start(3000);  // 3 secondes d'échantillonnage
        startButton->setText("Stop Heating");
    }
}

void MainWindow::updateTemperature() {
    // Simule l'augmentation de la température
    double temperatureChange = (puissance / 100.0) * (consigne - currentTemp);
    currentTemp += temperatureChange;

    // Actualisation de l'interface
    labelTemp->setText(QString("Température actuelle : %1°C").arg(currentTemp));
    updateGraph();
}

void MainWindow::updateGraph() {
    // Mise à jour du graphique
    series->append(series->count(), currentTemp);
}

void MainWindow::adjustTemperature() {
    // Ajuste la température en fonction de la puissance
    puissance = sliderPuissance->value();
    labelConsigne->setText(QString("Consigne : %1°C").arg(consigne));
}
