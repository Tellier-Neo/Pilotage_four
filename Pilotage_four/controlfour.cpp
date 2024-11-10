#include "controlfour.h"
#include <QRandomGenerator>

ControlFour::ControlFour() : power(0), temperature(20) {}

void ControlFour::setPower(int power)
{
    this->power = power;
    // Simulation de l'effet de la puissance sur la température
    if (power > 0)
        temperature += 0.5;  // Température augmente si la puissance est > 0
    else
        temperature -= 0.1;  // Température diminue si la puissance est arrêtée
}

double ControlFour::getTemperature()
{
    return temperature;
}
