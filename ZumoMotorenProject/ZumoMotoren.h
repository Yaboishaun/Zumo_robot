#ifndef ZUMOMOTOREN_H
#define ZUMOMOTOREN_H

#include <Zumo32U4.h>

class ZumoMotoren
{
public:
    ZumoMotoren();
    void init();
    
    // Handmatige besturingsfuncties
    void setSnelheden(int linkerSnelheid, int rechterSnelheid);
    void stop();
    void vooruit();
    void achteruit();
    void draaiLinks();
    void draaiRechts();

    // Seriële besturing
    void handleSerialInput();
    void pasSnelheidAan(int nieuweSnelheid);

    // Sensorenfuncties
    void followLineSensor();
    void avoidObstacles();
    void readLine();

private:
    Zumo32U4Motors motoren;
    Zumo32U4LineSensors lineSensor;
    Zumo32U4ProximitySensors proximitySensor;
    int snelheid;  // Variabele om de snelheid op te slaan

    void readLineSensor();
    void readProximitySensor();
};

#endif // ZUMOMOTOREN_H
