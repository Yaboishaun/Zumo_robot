#include "LineSensors.h"
#include <Zumo32U4.h>

Zumo32U4ButtonA buttonA;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;

LineSensors::LineSensors()
    : LaatsteGelezenUitvoer(0) {
    for (int i = 0; i < 5; ++i) {
        lineSensorValues[i] = 0;
    }
}

int LineSensors::startup() {
    if (status == 0) {
        if (buttonA.getSingleDebouncedPress()) {
            delay(1000);
            lineSensors.initFiveSensors();
            pinMode(5, OUTPUT);
            calibrateLineSensor();
            Serial.begin(9600);
            status = 1;
            Serial.println(status);
            return status;
        }
    }
    return status;
}

int LineSensors::checkWaardesLS() {
    if ((uint16_t)(millis() - LaatsteGelezenUitvoer) >= 100) {
        LaatsteGelezenUitvoer = millis();
        lineSensors.readCalibrated(lineSensorValues);
        printReadingsToSerial();
        return 0;
    }
}

int LineSensors::calibrateLineSensor() {
    Serial.println("Kalibreren...");
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 50; i++) {
            lineSensors.calibrate();
            motors.setLeftSpeed(200);
            motors.setRightSpeed(-200);
            delay(10);
        }
    }
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
    return 0;
}

void LineSensors::printReadingsToSerial() {
    for (uint8_t i = 0; i < 5; i++) {
        int mappedValue = map(lineSensorValues[i], 0, 1000, 0, 10000);
        Serial.print(mappedValue);
        Serial.print(" ");
    }
    Serial.println();
}

int LineSensors::checkLijnen(bool &allWhite) {
    int16_t position = lineSensors.readLine(lineSensorValues);
    allWhite = true;
    for (uint8_t i = 0; i < 5; ++i) {
        if (lineSensorValues[i] > 100) {
            allWhite = false;
            break;
        }
    }
    Serial.print("Dit is van de Readline ");
    Serial.print(position);
    Serial.print(" .\n");
    return position;
}

int LineSensors::KleurCheck() {
    for (int i = 0; i < 5; ++i) {
        if (i == 0) {
            LSKleur = map(lineSensorValues[i], 0, 1000, 0, 10000);
        }
        if (i == 1) {
            LSKleur1 = map(lineSensorValues[i], 0, 1000, 0, 10000);
        }
        if (i == 2) {
            LSKleur2 = map(lineSensorValues[i], 0, 1000, 0, 10000);
        }
        if (i == 3) {
            LSKleur3 = map(lineSensorValues[i], 0, 1000, 0, 10000);
        }
        if (i == 4) {
            LSKleur4 = map(lineSensorValues[i], 0, 1000, 0, 10000);
        }
    }
}

String LineSensors::LSrouteVersturen() {
    String kleur;

      if (LSKleur1 > 600 && LSKleur1 < 1500 || LSKleur2 > 600 && LSKleur2 < 1500 || LSKleur3 > 600 && LSKleur3 < 1500) {
        Serial.print("Groen Waar! ");
        kleur = "Groen";
        return kleur;
    } else if ((LSKleur > 1700 && LSKleur < 4500) && (LSKleur4 > 1700 && LSKleur4 < 4500)) {
        Serial.print("Bruin is Waar! ");
        kleur = "Bruin";
        return kleur;
    } else {
        kleur = "Zwart";
        return kleur;
    }
    return kleur;
}

bool LineSensors::detectBrown() {
  if ((LSKleur > 1700 && LSKleur < 4500) && (LSKleur4 > 1700 && LSKleur4 < 4500)) {
  return true; 
  } 
  return false;
}
