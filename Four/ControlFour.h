#ifndef CONTROLFOUR_H
#define CONTROLFOUR_H

class ControlFour
{
public:
    ControlFour();
    void setPower(int power);   // Ajuste la puissance du four
    double getTemperature();    // Retourne la temp�rature actuelle

private:
    int power;  // Puissance actuelle du four (0-100%)
    double temperature;  // Temp�rature actuelle du four simul�e
};

#endif // CONTROLFOUR_H
