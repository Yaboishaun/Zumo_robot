#ifndef LINESENSORS_H
#define LINESENSORS_H

#include <Wire.h>
#include <Zumo32U4.h>

class LineSensors {
private:
    uint16_t LaatsteGelezenUitvoer;
    uint16_t lineSensorValues[3];
    int DonkersteSensor;
    int LSSensorwaarde;
    int LSKleur;
    int LSKleur1;
    int LSKleur2;
    int status = 0;

public:
    LineSensors(); // Constructor
    int calibrateLineSensor();
    void startup();
    int checkWaardesLS();
    void printReadingsToSerial();
    int checkLijnen();
    int berekenFout();
    void LSrouteVersturen();
    int KleurCheck();
};

#endif // LINESENSORS_H
