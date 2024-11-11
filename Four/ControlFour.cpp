#include "controlfour.h"
#include <QRandomGenerator>

ControlFour::ControlFour() : power(0), temperature(20) {}

void ControlFour::setPower(int power)
{
    this->power = power;
    // Simulation de l'effet de la puissance sur la temp�rature
    if (power > 0)
        temperature += 0.5;  // Temp�rature augmente si la puissance est > 0
    else
        temperature -= 0.1;  // Temp�rature diminue si la puissance est arr�t�e
}

double ControlFour::getTemperature()
{
    return temperature;
}
