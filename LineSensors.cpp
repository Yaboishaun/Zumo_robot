#include "LineSensors.h"
#include <Zumo32U4.h>

Zumo32U4ButtonB buttonB;
Zumo32U4LineSensors lineSensors;

// initialiseer 3 sensoren
LineSensors::LineSensors() : LaatsteGelezenUitvoer(0) {
    for (int i = 0; i < 3; ++i) {
        lineSensorValues[i] = 0;
    }
}

// Setup methode voor het initialiseren van de sensoren en kalibratie
void LineSensors::startup() {
    lineSensors.initThreeSensors();
    pinMode(5, OUTPUT);
    calibrateLineSensor();
    Serial.begin(9600);
}

// Loop methode voor het lezen en printen
int LineSensors::checkWaardesLS() {
    if ((uint16_t)(millis() - LaatsteGelezenUitvoer) >= 100) {
        LaatsteGelezenUitvoer = millis();
        lineSensors.readCalibrated(lineSensorValues);
        printReadingsToSerial(); 
    }
    if (buttonB.isPressed()){
        calibrateLineSensor();
    }
}

// Methode om de lijnsensoren te kalibreren
int LineSensors::calibrateLineSensor() {
    digitalWrite(5, LOW); // Zet de groene LED uit
    for (uint16_t i = 0; i < 200; i++) {
        lineSensors.calibrate(); // Kalibreer de sensoren 200 keer
    }
    digitalWrite(5, HIGH); // Zet de groene LED aan
    return 0;
}



// Methode om de waarden naar de seriële monitor te printen
void LineSensors::printReadingsToSerial() {
    Serial.print("Line sensoren output: ");
    for (uint8_t i = 0; i < 3; i++) {
        Serial.print(lineSensorValues[i]); 
        Serial.print(" ");
    }
    Serial.println(); 
}

//  Methode om te controleren hoe ver de lijn is
int LineSensors::checkLijnen() {
  DonkersteSensor = 0;
    LSSensorwaarde = lineSensorValues[0];

    for (int i = 1; i < 3; ++i) {
        if (lineSensorValues[i] < LSSensorwaarde) {
            LSSensorwaarde = lineSensorValues[i];
            DonkersteSensor = i;
        }
    }
    return DonkersteSensor;
}

// Methode om te zien hoe ver de zumo van de lijn is
int LineSensors::berekenFout() {
    if (DonkersteSensor == 0) {
        // links  ??Zumo32U4.rijd_vooruit(???);
    } 
    if (DonkersteSensor == 2) {
        //rechts  ??Zumo32U4.rijd_vooruit(???);
    } 
    else {
        return false;
    }

    return DonkersteSensor;
}
int LineSensors::KleurCheck() {
  for (int i = 0; i < 3; ++i) {
        if (lineSensorValues[i] > 50 && lineSensorValues[i] < 950) {
            LSKleur = i;
        }
    } 
    // Nog geen idee van de waarden voor kleuren
    if (LSKleur > 50 && LSKleur < 200) {
      //Zumo32U4.rijd_vooruit(---);
    }
    if (LSKleur > 200 && LSKleur < 300) {
      //Zumo32U4.rijd_vooruit(---);
    }
    if (LSKleur > 400 && LSKleur < 500) {
      //Zumo32U4.rijd_vooruit(---);
    }
    if (LSKleur > 600 && LSKleur < 700) {
      //Zumo32U4.rijd_vooruit(---);
    }
    if (LSKleur > 800 && LSKleur < 950) {
      //Zumo32U4.rijd_vooruit(---);
    }
}

