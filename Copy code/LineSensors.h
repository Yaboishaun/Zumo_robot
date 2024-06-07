#ifndef LINESENSORS_H
#define LINESENSORS_H

#include <Wire.h>
#include <Zumo32U4.h>
#include "Motors.h"

class LineSensors {
private:
    uint16_t LaatsteGelezenUitvoer;
    uint16_t lineSensorValues[5];
    int DonkersteSensor = 0;
    int  LSSensorwaarde;
    int LSKleur  =0 ;
    int LSKleur1 =0;
    int LSKleur2 =0;
    int LSKleur3 =0;
    int LSKleur4 =0;
    int status = 0;
    // Motors motors;

public:
    LineSensors(); // Constructor
    int calibrateLineSensor();
    int startup();
    int checkWaardesLS();
    void printReadingsToSerial();
    int checkLijnen();
    int berekenFout();
    String LSrouteVersturen();
    int KleurCheck();
    int SensorenE();
};

#endif // LINESENSORS_H
