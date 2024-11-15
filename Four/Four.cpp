#include "Four.h"
#include <QTimer>

Four::Four(QWidget* parent)
    : QMainWindow(parent), cardId(-1)
{
    isHeating = false;
    temp = 20;
    consigne = 20;
    puissance = 0;
    intervalleEchantillon = 3000;

    ui.setupUi(this);

    sampleTimer = new QTimer(this);

    connect(sampleTimer, &QTimer::timeout, this, &Four::UpdateStatutChauffage);

    InitializeCard();
}

void Four::InitializeCard()
{
    cardId = Register_Card(PCI_9111DG, 0);
    if (cardId >= 0) {
        ui.cardLogBox->addItem("Ouverture carte OK");
        AI_9111_Config(cardId, TRIG_INT_PACER, P9111_TRGMOD_SOFT, 0);
        ReadTension();
    }
    else {
        ui.cardLogBox->addItem("Erreur d'ouverture de la carte");
    }
}

void Four::ReadTension()
{
    if (cardId >= 0) {
        double tension;
        if (AI_VReadChannel(cardId, 0, AD_B_10_V, &tension) < 0) {
            ui.cardLogBox->addItem("Erreur tension");
        }
        else {
            ui.cardLogBox->addItem("Tension: " + QString::number(tension));
        }
    }
}

void Four::ReadTemperature()
{
    if (cardId >= 0) {
        double tension;
        if (AI_VReadChannel(cardId, 0, AD_B_10_V, &tension) < 0) {
            ui.cardLogBox->addItem("Erreur temperature");
        }
        else {
            double temperature = 43.76 * tension - 58.29;

            ui.tempStatLabel->setText(QString("Temperature actuelle: %1.C").arg(temperature));
            ui.graphicBox->addItem(QString::number(temperature));

            ui.cardLogBox->addItem("Temperature: " + QString::number(temperature) + " .C");
        }
    }
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
    if (cardId < 0) {
        ui.cardLogBox->addItem("Erreur carte non initialisee.");
        return;
    }

    double tension = (puissance / 100.0) * 10.0;

    if (AO_VWriteChannel(cardId, 0, tension) < 0) {
        ui.cardLogBox->addItem("Erreur demarrage de chauffage.");
    }
    else {
        ui.cardLogBox->addItem("Chauffage demarre a " + QString::number(tension) + "V");
        isHeating = true;
        sampleTimer->start(intervalleEchantillon);
        ui.pushButton->setText("Arret");
    }
}


void Four::stopHeat()
{
    if (cardId < 0) {
        ui.cardLogBox->addItem("Erreur carte non initialisee");
        return;
    }

    if (AO_VWriteChannel(cardId, 0, 0.0) < 0) {
        ui.cardLogBox->addItem("Erreur arret de chauffage");
    }
    else {
        ui.cardLogBox->addItem("Chauffage arrete");
        isHeating = false;
        sampleTimer->stop();
        ui.pushButton->setText("Chauffer");
    }
}

void Four::SetPower(int value)
{
    puissance = value;
    ui.powerValue->setText(QString("%1%").arg(puissance));
    ui.powerStatLabel->setText(QString("Puissance: %1%").arg(puissance));

    // Appliquer la nouvelle puissance si le four chauffe déjà
    if (isHeating) {
        startHeat();
    }
}


void Four::SetConsigne(int value)
{
    consigne = (double)value;
    ui.consigneValue->setText(QString("%1°C").arg(consigne));
    ui.consigneStatLabel->setText(QString("Consigne: %1.C").arg(consigne));
}

void Four::EchantillonageTemperature()
{
    temp = controlFour.getTemperature();
    ui.tempStatLabel->setText(QString("Temperature actuelle: %1.C").arg(temp));
    ui.graphicBox->addItem(QString::number(temp));

    if (temp < consigne) {
        puissance = 100;
        controlFour.setPower(puissance);
    }
    else {
        puissance = 0;
        controlFour.setPower(puissance);
    }
}

void Four::UpdateStatutChauffage()
{
    ReadTemperature();
    ReadTension();
}
