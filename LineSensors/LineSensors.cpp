#include "LineSensors.h"
#include <Zumo32U4.h>

// Maak een object aan voor de Zumo32U4ButtonB en Zumo32U4LineSensors
Zumo32U4ButtonA buttonA;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;

// initialiseer 3 sensoren
LineSensors::LineSensors() : LaatsteGelezenUitvoer(0){
    for (int i = 0; i < 5; ++i) {
        lineSensorValues[i] = 0;
    }
}

// Setup methode voor het initialiseren van de sensoren en kalibratie
int LineSensors::startup() {
  if (status==0){
    if (buttonA.getSingleDebouncedPress()){
      Serial.println("Knop A is ingedrukt!");
      delay(1000);
      lineSensors.initFiveSensors();
      pinMode(5, OUTPUT); // Zet groene led op pin 5 op output
      calibrateLineSensor();
      Serial.begin(9600);
      status=1;
      Serial.println(status);
      return status;
    }
  }
}

// Loop methode voor het lezen en printen
int LineSensors::checkWaardesLS() {
    if ((uint16_t)(millis() - LaatsteGelezenUitvoer) >= 100) {
        LaatsteGelezenUitvoer = millis();
        lineSensors.readCalibrated(lineSensorValues);
        printReadingsToSerial(); 
        return 0;
    }
}

// Methode om de lijnsensoren te kalibreren
int LineSensors::calibrateLineSensor() {
    digitalWrite(5, LOW); // Zet de groene LED uit
    for (uint16_t i = 0; i < 300; ++i) {
        lineSensors.calibrate(); // Kalibreer de sensoren 400 keer
        motors.setSpeeds(240, -240); // Vooruit met links, achteruit met rechts voor draaien
        delay(10); // Korte delay voor een vloeiende beweging
    }
    digitalWrite(5, HIGH); // Zet de groene LED aan
    motors.setSpeeds(0, -0);
    return 0;

}



// Methode om de waarden naar de seriële monitor te printen
void LineSensors::printReadingsToSerial() {
    Serial.print("Line sensoren output: ");
    for (uint8_t i = 0; i < 5; i++) {
        int mappedValue = map(lineSensorValues[i], 0, 1000, 0, 10000);
        // Serial.print(mappedValue);
        // Serial.print(" ");
    }
    // Serial.println(); 
}

//  Methode om te controleren hoe ver de lijn is
int LineSensors::checkLijnen() {
    int16_t position = lineSensors.readLine(lineSensorValues);
    Serial.print("Dit is van de Readline ");
    Serial.print(position);
    Serial.print(" . ");
    // delay(1000);
    return position;
}
int LineSensors::KleurCheck() {
  for (int i = 0; i < 5; ++i) {
        if (i == 0) {
        lineSensorValues[i];
        LSKleur = i;
}
        if (i == 1) {
        lineSensorValues[i];
        LSKleur1 = i;
}
        if (i == 2) {
        lineSensorValues[i];
        LSKleur2 = i;
}
        if (i == 3) {
        LSKleur3 = lineSensorValues[i];
}
        if (i == 4) {
        lineSensorValues[i];
        LSKleur4 = i;
    }
  }
}
    String LineSensors::LSrouteVersturen() {
      // Serial.print("Dit is waarde: ");
      // Serial.print(LSKleur3);
      // Serial.print(" ");
    if (LSKleur3 > 600 && LSKleur3 < 1100) {
      //Groen
      Serial.print("Groen Waar! ");
      return "Groen";
    }
    if (LSKleur > 2400 && LSKleur < 2700) {
      return "GrijsL";
      Serial.print("GrijsL Waar! ");
      //Grijs voor Links
    }
    if (LSKleur4 > 2100 && LSKleur4 < 2500) {
      // Grijs voor Rechts
      Serial.print("GrijsR Waar! ");
      return "GrijsR";
    }
    if (LSKleur > 2700 && LSKleur < 4500) {
      Serial.print("BruinL Waar! ");
      return "BruinL";
      //Bruin voor Links
    }
    if (LSKleur4 > 2700 && LSKleur4 < 4500) {
      Serial.print("BruinR Waar! ");
      return "BruinR";
      //Bruin voor Rechts
      }
    }

int LineSensors::SensorenE(){
      int tijdelijk = 0 ;
      for (int i = 0; i < 5; ++i) {
       tijdelijk += lineSensorValues[i];
  }
  if (tijdelijk = 0) {
    return 1;
  }
}