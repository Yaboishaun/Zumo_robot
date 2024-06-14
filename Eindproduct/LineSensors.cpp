#include "LineSensors.h"
#include <Zumo32U4.h>

// Maak een object aan voor de Zumo32U4ButtonA ,Zumo32U4LineSensors en Zumo32U4Motors
Zumo32U4ButtonA buttonA;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;

// initialiseer 5 sensoren
LineSensors::LineSensors()
  : LaatsteGelezenUitvoer(0) {
  for (int i = 0; i < 5; ++i) {
    lineSensorValues[i] = 0;
  }
}

// Checkt of het al eerder is gestart en of knop a is ingedrukt.
// Roept de functie initFiveSensors aan en zet de groene led als output op pin 5
// Roept de functie calibrateLineSensor aan. Start de seriele communicatie en return status
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
}
// Deze functie controleert of er 100 milliseconden zijn verstreken sinds de laatste lezing,
// leest de lijnsensorwaarden en stuurt deze naar de seriële poort.
int LineSensors::checkWaardesLS() {
  if ((uint16_t)(millis() - LaatsteGelezenUitvoer) >= 100) {
    LaatsteGelezenUitvoer = millis();
    lineSensors.readCalibrated(lineSensorValues);
    printReadingsToSerial();
    return 0;
  }
}
// kalibreert de LineSensors door de zumo een rondje te laten rijden.
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
// Mapped de values van de LineSensors tot 10.000 om het makkelijker te maken om de waardes te lezen voor de kleuren.
// Print de mappedvalues
void LineSensors::printReadingsToSerial() {
  for (uint8_t i = 0; i < 5; i++) {
    int mappedValue = map(lineSensorValues[i], 0, 1000, 0, 10000);
    Serial.print(mappedValue);
    Serial.print(" ");
  }
  Serial.println();
}
// Kijkt of een van de sensoren een kleur ziet wat anders is dan wit als die dat ziet dan zet die de bool allWhite op false.
// Geeft de readline waardes op de int16_t position.
// Print de waarde van position en return die.
int LineSensors::checkLijnen(bool &allWhite) {
  int16_t position = lineSensors.readLine(lineSensorValues);
  allWhite = true;
  for (uint8_t i = 0; i < 5; ++i) {
    if (lineSensorValues[i] > 100) {
      allWhite = false;
      break;
    }
    Serial.print("Dit is van de Readline ");
    Serial.print(position);
    Serial.print(" .\n");
    return position;
  }
}
// Zet de mapped waardes van elke sensor op een int LSKleur
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
// Check welke kleuren op de int LSKleur0-4 staan. Als de waardes binnen een van de aangegeven waardes valt return dan een string met de kleur naam.
String LineSensors::LSrouteVersturen() {
  String kleur;
  if ((LSKleur > 1500 && LSKleur < 2000) && (LSKleur4 > 1700 && LSKleur4 < 2200)) {
    Serial.print("GrijsL+R Waar! ");
    kleur = "GrijsLR";
    return kleur;
  } else if (LSKleur > 1500 && LSKleur < 2000) {
    Serial.print("GrijsL Waar! ");
    kleur = "GrijsL";
    return kleur;
  } else if (LSKleur4 > 1700 && LSKleur4 < 2200) {
    Serial.print("GrijsR Waar! ");
    kleur = "GrijsR";
    return kleur;
  } else if (LSKleur1 > 600 && LSKleur1 < 1500 || LSKleur2 > 600 && LSKleur2 < 1500 || LSKleur3 > 600 && LSKleur3 < 1500) {
    Serial.print("Groen Waar! ");
    kleur = "Groen";
    return kleur;
  } else if (LSKleur > 2500 && LSKleur < 3000) {
    Serial.print("BruinL Waar! ");
    kleur = "BruinL";
    return kleur;
  } else if (LSKleur4 > 2700 && LSKleur4 < 3500) {
    Serial.print("BruinR Waar! ");
    kleur = "BruinR";
    return kleur;
  } else {
    kleur = "Zwart";
    return kleur;
  }
  return kleur;
}
