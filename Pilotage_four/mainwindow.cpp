#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "controlfour.h" // Assurez-vous d'avoir une classe qui gère le four
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    temperature(20), // Température initiale (température ambiante)
    consigne(20),     // Consigne initiale (température ambiante)
    puissance(0),     // Puissance initiale à 0%
    samplingInterval(3000) // Fréquence d'échantillonnage de 3 secondes
{
    ui->setupUi(this);

    // Connexion des signaux et slots
    connect(ui->pushButton_start, &QPushButton::clicked, this, &MainWindow::startHeating);
    connect(ui->pushButton_stop, &QPushButton::clicked, this, &MainWindow::stopHeating);
    connect(ui->horizontalSlider_puissance, &QSlider::valueChanged, this, &MainWindow::setPuissance);
    connect(ui->horizontalSlider_consigne, &QSlider::valueChanged, this, &MainWindow::setConsigne);

    // Configuration du graphique
    chart = new QChart();
    series = new QLineSeries();
    chart->addSeries(series);
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    axisX->setRange(0, 24);  // Plage de temps sur l'axe X (en secondes)
    axisY->setRange(0, 70);  // Plage de température sur l'axe Y
    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);

    chartView = new QChartView(chart);
    ui->verticalLayout_graphic->addWidget(chartView);

    // Initialisation du timer d'échantillonnage
    sampleTimer = new QTimer(this);
    connect(sampleTimer, &QTimer::timeout, this, &MainWindow::sampleTemperature);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startHeating()
{
    // Démarrer la chauffe du four en fonction de la puissance sélectionnée
    controlFour.setPower(puissance);
    sampleTimer->start(samplingInterval); // Démarrer l'échantillonnage
}

void MainWindow::stopHeating()
{
    // Arrêter la chauffe
    controlFour.setPower(0);
    sampleTimer->stop();
}

void MainWindow::setPuissance(int value)
{
    puissance = value;  // Mettre à jour la puissance en fonction de la valeur du slider
    ui->label_puissance->setText(QString("Puissance: %1%").arg(puissance));
    controlFour.setPower(puissance);  // Appliquer la puissance au four
}

void MainWindow::setConsigne(int value)
{
    consigne = value;  // Mettre à jour la consigne de température
    ui->label_consigne->setText(QString("Consigne: %1°C").arg(consigne));
}

void MainWindow::sampleTemperature()
{
    // Lire la température actuelle du four (en °C)
    temperature = controlFour.getTemperature();

    // Afficher la température actuelle
    ui->label_temperature->setText(QString("Température actuelle: %1°C").arg(temperature));

    // Ajouter la température au graphique
    series->append(series->count(), temperature);

    // Régulation simple : si la température actuelle est inférieure à la consigne, chauffer, sinon, arrêter
    if (temperature < consigne) {
        // Logique de régulation simple : augmenter la puissance
        puissance = 100; // Réglage brut de la puissance
        controlFour.setPower(puissance);
    } else {
        // Arrêter la chauffe si la consigne est atteinte ou dépassée
        puissance = 0;
        controlFour.setPower(puissance);
    }
}
