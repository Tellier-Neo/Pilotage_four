#include "Four.h"
#include <QTimer>

Four::Four(QWidget *parent)
    : QMainWindow(parent)
{
    isHeating = false;
    temp = 20;
    consigne = 20;
    puissance = 0;
    intervalleEchantillon = 3000;

    ui.setupUi(this);

    sampleTimer = new QTimer(this);
}

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

void Four::startHeat()
{
    controlFour.setPower(puissance);
    isHeating = true;
    sampleTimer->start(intervalleEchantillon);
    ui.pushButton->setText("Arret");
}

void Four::stopHeat()
{
    controlFour.setPower(0);
    sampleTimer->stop();
    isHeating = false;
    ui.pushButton->setText("Chauffer");
}

void Four::SetPower(int value)
{
    puissance = value;
    ui.powerValue->setText(QString("%1%").arg(puissance));
    ui.powerStatLabel->setText(QString("Puissance: %1%").arg(puissance));
    controlFour.setPower(puissance);
}

void Four::SetConsigne(int value)
{
    consigne = (double)value;  // Mettre à jour la consigne de température
    ui.consigneValue->setText(QString("%1°C").arg(consigne));
    ui.consigneStatLabel->setText(QString("Consigne: %1°C").arg(consigne));
}

void Four::EchantillonageTemperature()
{
    // Lire la température actuelle du four (en °C)
    temp = controlFour.getTemperature();

    // Afficher la température actuelle
    ui.tempStatLabel->setText(QString("Température actuelle: %1°C").arg(temp));

    // Ajouter la température au graphique
    ui.graphicBox->addItem(QString::number(temp));

    // Régulation simple : si la température actuelle est inférieure à la consigne, chauffer, sinon, arrêter
    if (temp < consigne) {
        // Logique de régulation simple : augmenter la puissance
        puissance = 100; // Réglage brut de la puissance
        controlFour.setPower(puissance);
    }
    else {
        // Arrêter la chauffe si la consigne est atteinte ou dépassée
        puissance = 0;
        controlFour.setPower(puissance);
    }
}
