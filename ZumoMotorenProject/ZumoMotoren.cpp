#include "ZumoMotoren.h"
#include <Arduino.h>

ZumoMotoren::ZumoMotoren() : snelheid(200)  // Standaard snelheid instellen
{
    // Constructor
}

void ZumoMotoren::init()
{
    lineSensor.initFiveSensors();
    proximitySensor.initThreeSensors();
    Serial.begin(9600);
}

void ZumoMotoren::setSnelheden(int linkerSnelheid, int rechterSnelheid)
{
    motoren.setSpeeds(linkerSnelheid, rechterSnelheid);
}

void ZumoMotoren::stop()
{
    motoren.setSpeeds(0, 0);
}

void ZumoMotoren::vooruit()
{
    setSnelheden(snelheid, snelheid);
}

void ZumoMotoren::achteruit()
{
    setSnelheden(-snelheid, -snelheid);
}

void ZumoMotoren::draaiLinks()
{
    setSnelheden(-snelheid, snelheid);
}

void ZumoMotoren::draaiRechts()
{
    setSnelheden(snelheid, -snelheid);
}

void ZumoMotoren::followLineSensor()
{
    unsigned int sensorgegevens[5];
    lineSensor.read(sensorgegevens);
    unsigned int positie = lineSensor.readLine(sensorgegevens);

    if (positie < 2000)
    {
        draaiLinks();
    }
    else if (positie > 4000)
    {
        draaiRechts();
    }
    else
    {
        vooruit();
    }
}

void ZumoMotoren::avoidObstacles()
{
    readProximitySensor();
    if (proximitySensor.countsFrontWithLeftLeds() > 0 || proximitySensor.countsFrontWithRightLeds() > 0)
    {
        achteruit();
        draaiLinks();
    }
    else
    {
        vooruit();
    }
}

void ZumoMotoren::readLine()
{
    unsigned int sensorgegevens[5];
    lineSensor.read(sensorgegevens);
}

void ZumoMotoren::readProximitySensor()
{
    proximitySensor.read();
}

void ZumoMotoren::pasSnelheidAan(int nieuweSnelheid)
{
    snelheid = nieuweSnelheid;
    Serial.print("Nieuwe snelheid ingesteld op: ");
    Serial.println(snelheid);
}

void ZumoMotoren::handleSerialInput()
{
    if (Serial.available() > 0)
    {
        char input = Serial.read();
        switch (input)
        {
            case 'w':
                vooruit();
                break;
            case 's':
                achteruit();
                break;
            case 'a':
                draaiLinks();
                break;
            case 'd':
                draaiRechts();
                break;
            case 'x':
                stop();
                break;
            case 'e':
                Serial.println("Voer nieuwe snelheid in:");
                while (Serial.available() == 0); // Wacht op invoer
                int nieuweSnelheid = Serial.parseInt();
                pasSnelheidAan(nieuweSnelheid);
                break;
            default:
                stop();
                break;
        }
    }
}
