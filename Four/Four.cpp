//*********************************************************************************************
//* Programme : Four.cpp                                                 Date : 16/11/2024 
//*--------------------------------------------------------------------------------------------
//* Dernière mise à jour : 16/11/2024 
//*
//* Programmeurs : Yann Fauquembergue                          Classe : BTS CIEL 2
//*                Valentin Rosier 
//*--------------------------------------------------------------------------------------------
//* But : Contrôler un four via une interface Qt, avec gestion de la température et affichage
//        d’un graphique en temps réel.
//* Programmes associés : Four.h, main.cpp
//*********************************************************************************************

#include "Four.h"
#include <QTimer>


//---------------------------------------------------------------------------------------------
//* Constructeur de la classe `Four`.
//* Initialise les variables, configure l'IHM et la scène graphique, et prépare le timer pour 
//  les mises à jour cycliques.
//* Paramètres :
//*  - QWidget* parent : widget parent (nullptr par défaut pour une fenêtre principale).
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
Four::Four(QWidget* parent)
    : QMainWindow(parent), card(Carte9111()), timeElapsed(0.0)
{
    isHeating = false;
    temp = 20;
    consigne = 20;
    puissance = 0;
    intervalleEchantillon = 10000;

    ui.setupUi(this);

    graphScene = new QGraphicsScene(this);
    ui.temperatureGraphView->setScene(graphScene);

    graphScene->setSceneRect(0, 0, 600, 300);
    ui.temperatureGraphView->setRenderHint(QPainter::Antialiasing);


    sampleTimer = new QTimer(this);

    connect(sampleTimer, &QTimer::timeout, this, &Four::UpdateStatutChauffage);

    InitializeCard();

}


//---------------------------------------------------------------------------------------------
//* Fonction `InitializeCard`.
//* Initialise la carte d'acquisition PCI et configure les canaux pour lire les tensions.
//* Paramètres : aucun.
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
void Four::InitializeCard()
{
    card = Carte9111();
    if (card.GetNumeroCarte() >= 0) {
        ui.cardLogBox->addItem("Ouverture carte OK");
        card.ConfigurerCarte(TRIG_INT_PACER, P9111_TRGMOD_SOFT);
        ReadTension();
    }
    else {
        ui.cardLogBox->addItem("Erreur d'ouverture de la carte");
    }
}


//---------------------------------------------------------------------------------------------
//* Fonction `ReadTension`.
//* Lit la tension actuelle sur la carte d'acquisition et l'affiche dans l'IHM.
//* Paramètres : aucun.
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
void Four::ReadTension()
{
    if (card.GetNumeroCarte() >= 0) {
        double tension;
        if (card.LireChaine(0, &tension) < 0) {
            ui.cardLogBox->addItem("Erreur tension");
        }
        else {
            ui.cardLogBox->addItem("Tension: " + QString::number(tension));
        }
    }
}


//---------------------------------------------------------------------------------------------
//* Fonction `ReadTemperature`.
//* Lit la température à partir de la tension mesurée, l'affiche dans l'IHM et met à jour le 
//  graphique en conséquence. Arrête le chauffage si la température dépasse une limite critique.
//* Paramètres : aucun.
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
void Four::ReadTemperature()
{
    if (card.GetNumeroCarte() >= 0) {
        double tension;
        if (card.LireChaine(0, &tension) < 0) {
            ui.cardLogBox->addItem("Erreur temperature");
        }
        else {
            double temperature = 43.76 * tension - 58.29;

            ui.tempStatLabel->setText(QString("Temperature actuelle: %1.C").arg(temperature));
            ui.graphicBox->addItem("Temperature: " + QString::number(temperature) + " .C");

            // Limite la température à 65°C
            if (temperature > 65.0) {
                stopHeat();
                ui.cardLogBox->addItem("Temperature trop elevee : Chauffage arrete !");
                return;
            }

            ui.tempStatLabel->setText(QString("Temperature actuelle : %1.C").arg(temperature));

            UpdateGraph(temperature);
        }
    }
}


//---------------------------------------------------------------------------------------------
//* Fonction `OnFourButtonClicked`.
//* Gère le clic sur le bouton de contrôle du chauffage. Active ou désactive le chauffage selon
//  l'état actuel.
//* Paramètres : aucun.
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
void Four::OnFourButtonClicked()
{
    if (!isHeating)
    {
        startHeat();
    }
    else
    {
        stopHeat();
    }
}


//---------------------------------------------------------------------------------------------
//* Fonction `startHeat`.
//* Active le chauffage en ajustant la tension appliquée selon la puissance définie. Lance le 
//  timer pour les mises à jour cycliques si la carte est correctement initialisée.
//* Paramètres : aucun.
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
void Four::startHeat()
{
    if (card.GetNumeroCarte() < 0) {
        ui.cardLogBox->addItem("Erreur carte non initialisee.");
        return;
    }

    double tension = (puissance / 100.0) * 10.0;

    if (card.EcrireChaine(0, tension) < 0) {
        ui.cardLogBox->addItem("Erreur demarrage de chauffage.");
    }
    else {
        ui.cardLogBox->addItem("Chauffage demarre a " + QString::number(tension) + "V");
        isHeating = true;
        sampleTimer->start(intervalleEchantillon);
        ui.pushButton->setText("Arret");
    }
}


//---------------------------------------------------------------------------------------------
//* Fonction `stopHeat`.
//* Désactive le chauffage en ramenant la tension à zéro. Arrête le timer de mises à jour
//  cycliques.
//* Paramètres : aucun.
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
void Four::stopHeat()
{
    if (card.GetNumeroCarte() < 0) {
        ui.cardLogBox->addItem("Erreur carte non initialisee");
        return;
    }

    if (card.EcrireChaine(0, 0.0) < 0) {
        ui.cardLogBox->addItem("Erreur arret de chauffage");
    }
    else {
        ui.cardLogBox->addItem("Chauffage arrete");
        isHeating = false;
        sampleTimer->stop();
        ui.pushButton->setText("Chauffer");
    }
}


//---------------------------------------------------------------------------------------------
//* Fonction `SetPower`.
//* Définit la puissance de chauffage et ajuste la tension appliquée si le chauffage est actif.
//* Paramètres :
//*  - int value : nouvelle valeur de la puissance (en pourcentage).
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
void Four::SetPower(int value)
{
    puissance = value;
    ui.powerValue->setText(QString("%1%").arg(puissance));
    ui.powerStatLabel->setText(QString("Puissance: %1%").arg(puissance));

    if (isHeating) {
        startHeat();
    }
}


//---------------------------------------------------------------------------------------------
//* Fonction `SetConsigne`.
//* Définit la consigne de température et met à jour les affichages correspondants dans l'IHM.
//* Paramètres :
//*  - int value : nouvelle valeur de la consigne (en degrés Celsius).
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
void Four::SetConsigne(int value)
{
    consigne = (double)value;
    ui.consigneValue->setText(QString("%1.C").arg(consigne));
    ui.consigneStatLabel->setText(QString("Consigne: %1.C").arg(consigne));
}

double coef = 5.0;


//---------------------------------------------------------------------------------------------
//* Fonction `UpdateStatutChauffage`.
//* Met à jour les données de température et de tension en les lisant sur la carte d'acquisition.
//* Paramètres : aucun.
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
void Four::UpdateStatutChauffage()
{
    ReadTemperature();
    ReadTension();
}


//---------------------------------------------------------------------------------------------
//* Fonction `UpdateGraph`.
//* Met à jour le graphique en ajoutant un nouveau point de température. Redessine le graphique
//  avec les axes et les unités, et trace les nouvelles données.
//* Paramètres :
//*  - double temperature : température actuelle à ajouter au graphique (en degrés Celsius).
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
void Four::UpdateGraph(double temperature)
{
    dataPoints.emplace_back(timeElapsed, temperature);

    graphScene->clear();

    const int margin = 50;
    const int graphWidth = 600 + margin;
    const int graphHeight = 300 + margin;

    graphScene->addLine(margin, graphHeight - margin, graphWidth, graphHeight - margin, QPen(Qt::black, 2));
    graphScene->addLine(margin, graphHeight - margin, margin, 0, QPen(Qt::black, 2));

    for (int i = 0; i <= 10; ++i) {
        int x = margin + i * 60;
        graphScene->addLine(x, graphHeight - margin, x, graphHeight - margin - 5, QPen(Qt::black));
        graphScene->addText(QString("%1").arg(i))->setPos(x - 10, graphHeight - margin + 5);
    }

    for (int i = 0; i <= 14; ++i) {
        int y = graphHeight - margin - i * 20;
        graphScene->addLine(margin, y, margin + 5, y, QPen(Qt::black));
        graphScene->addText(QString("%1").arg(10 + i * 5))->setPos(margin - 35, y - 10);
    }

    graphScene->addText("Temps en minutes")->setPos((graphWidth - margin) / 2, graphHeight - margin + 20); // Axe X
    QGraphicsTextItem* yAxisLabel = graphScene->addText("Temperature en degre Celsius");
    yAxisLabel->setRotation(-90);
    yAxisLabel->setPos(margin - 50, (graphHeight - margin) / 2 + 20);

    QPointF lastPoint(margin, graphHeight - margin - dataPoints[0].y() * 3);
    for (size_t i = 0; i < dataPoints.size(); ++i) {
        QPointF currentPoint(margin + (dataPoints[i].x() / 60.0) * 60, graphHeight - margin - dataPoints[i].y() * 3); // Position échelle

        if (i > 0) {
            graphScene->addLine(QLineF(lastPoint, currentPoint), QPen(Qt::blue, 2));
        }

        graphScene->addEllipse(currentPoint.x() - 3, currentPoint.y() - 3, 6, 6, QPen(Qt::red), QBrush(Qt::red));
        lastPoint = currentPoint;
    }

    timeElapsed += intervalleEchantillon / 1000.0;
}


//---------------------------------------------------------------------------------------------
//* Destructeur de la classe `Four`.
//* Libère les ressources allouées, arrête le chauffage et le timer, et nettoie la scène 
//  graphique.
//* Paramètres : aucun.
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
Four::~Four()
{
    if (isHeating) {
        stopHeat();
    }

    if (sampleTimer) {
        sampleTimer->stop();
    }

    if (graphScene) {
        delete graphScene;
    }

    delete sampleTimer;
}
