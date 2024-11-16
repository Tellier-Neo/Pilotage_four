//*********************************************************************************************
//* Programme : Four.cpp                                                 Date : 16/11/2024 
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 16/11/2024 
//*
//* Programmeurs : Yann Fauquembergue                          Classe : BTS CIEL 2
//*                Valentin Rosier 
//*--------------------------------------------------------------------------------------------
//* But : Contr�ler un four via une interface Qt, avec gestion de la temp�rature et affichage
//        d�un graphique en temps r�el.
//* Programmes associ�s : Four.h, main.cpp
//*********************************************************************************************

#include "Four.h"
#include <QTimer>


//---------------------------------------------------------------------------------------------
//* Constructeur de la classe `Four`.
//* Initialise les variables, configure l'IHM et la sc�ne graphique, et pr�pare le timer pour 
//  les mises � jour cycliques.
//* Param�tres :
//*  - QWidget* parent : widget parent (nullptr par d�faut pour une fen�tre principale).
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
//* Param�tres : aucun.
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
//* Param�tres : aucun.
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
//* Lit la temp�rature � partir de la tension mesur�e, l'affiche dans l'IHM et met � jour le 
//  graphique en cons�quence. Arr�te le chauffage si la temp�rature d�passe une limite critique.
//* Param�tres : aucun.
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

            // Limite la temp�rature � 65�C
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
//* G�re le clic sur le bouton de contr�le du chauffage. Active ou d�sactive le chauffage selon
//  l'�tat actuel.
//* Param�tres : aucun.
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
//* Active le chauffage en ajustant la tension appliqu�e selon la puissance d�finie. Lance le 
//  timer pour les mises � jour cycliques si la carte est correctement initialis�e.
//* Param�tres : aucun.
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
//* D�sactive le chauffage en ramenant la tension � z�ro. Arr�te le timer de mises � jour
//  cycliques.
//* Param�tres : aucun.
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
//* D�finit la puissance de chauffage et ajuste la tension appliqu�e si le chauffage est actif.
//* Param�tres :
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
//* D�finit la consigne de temp�rature et met � jour les affichages correspondants dans l'IHM.
//* Param�tres :
//*  - int value : nouvelle valeur de la consigne (en degr�s Celsius).
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
//* Met � jour les donn�es de temp�rature et de tension en les lisant sur la carte d'acquisition.
//* Param�tres : aucun.
//* Valeur de retour : aucune.
//---------------------------------------------------------------------------------------------
void Four::UpdateStatutChauffage()
{
    ReadTemperature();
    ReadTension();
}


//---------------------------------------------------------------------------------------------
//* Fonction `UpdateGraph`.
//* Met � jour le graphique en ajoutant un nouveau point de temp�rature. Redessine le graphique
//  avec les axes et les unit�s, et trace les nouvelles donn�es.
//* Param�tres :
//*  - double temperature : temp�rature actuelle � ajouter au graphique (en degr�s Celsius).
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
        QPointF currentPoint(margin + (dataPoints[i].x() / 60.0) * 60, graphHeight - margin - dataPoints[i].y() * 3); // Position �chelle

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
//* Lib�re les ressources allou�es, arr�te le chauffage et le timer, et nettoie la sc�ne 
//  graphique.
//* Param�tres : aucun.
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
