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
    int LSSensorwaarde;
    int LSKleur  =0 ;
    int LSKleur1 =0;
    int LSKleur2 =0;
    int LSKleur3 =0;
    int LSKleur4 =0;
    int status = 0;
    unsigned int blackThreshold;
    unsigned int greenThreshold;
    unsigned int whiteThreshold;

public:
    LineSensors(); // Constructor
    int calibrateLineSensor();
    int startup();
    int checkWaardesLS();
    void printReadingsToSerial();
    int checkLijnen(bool &allWhite);
    int berekenFout();
    String LSrouteVersturen();
    int KleurCheck();
    int SensorenE();
    void initSensors();
    int readLineSensors();
    void updateThresholds();
    bool detectColor(int sensorIndex, unsigned int thresholdLow, unsigned int thresholdHigh);
};

#endif // LINESENSORS_H
