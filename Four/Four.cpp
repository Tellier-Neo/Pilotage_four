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
    consigne = (double)value;  // Mettre � jour la consigne de temp�rature
    ui.consigneValue->setText(QString("%1�C").arg(consigne));
    ui.consigneStatLabel->setText(QString("Consigne: %1�C").arg(consigne));
}

void Four::EchantillonageTemperature()
{
    // Lire la temp�rature actuelle du four (en �C)
    temp = controlFour.getTemperature();

    // Afficher la temp�rature actuelle
    ui.tempStatLabel->setText(QString("Temp�rature actuelle: %1�C").arg(temp));

    // Ajouter la temp�rature au graphique
    ui.graphicBox->addItem(QString::number(temp));

    // R�gulation simple : si la temp�rature actuelle est inf�rieure � la consigne, chauffer, sinon, arr�ter
    if (temp < consigne) {
        // Logique de r�gulation simple : augmenter la puissance
        puissance = 100; // R�glage brut de la puissance
        controlFour.setPower(puissance);
    }
    else {
        // Arr�ter la chauffe si la consigne est atteinte ou d�pass�e
        puissance = 0;
        controlFour.setPower(puissance);
    }
}
