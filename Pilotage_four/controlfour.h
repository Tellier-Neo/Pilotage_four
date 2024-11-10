#ifndef CONTROLFOUR_H
#define CONTROLFOUR_H

class ControlFour
{
public:
    ControlFour();
    void setPower(int power);   // Ajuste la puissance du four
    double getTemperature();    // Retourne la température actuelle

private:
    int power;  // Puissance actuelle du four (0-100%)
    double temperature;  // Température actuelle du four simulée
};

#endif // CONTROLFOUR_H
