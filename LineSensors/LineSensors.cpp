#include "LineSensors.h"
#include <Zumo32U4.h>

// Maak een object aan voor de Zumo32U4ButtonB en Zumo32U4LineSensors
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonA buttonA;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;

// initialiseer 3 sensoren
LineSensors::LineSensors() : LaatsteGelezenUitvoer(0) {
    for (int i = 0; i < 3; ++i) {
        lineSensorValues[i] = 0;
    }
}

// Setup methode voor het initialiseren van de sensoren en kalibratie
void LineSensors::startup() {
  if (status==0){
    if (buttonA.getSingleDebouncedPress()){
      Serial.println("Knop A is ingedrukt!");
      delay(1000);
      lineSensors.initThreeSensors();
      pinMode(5, OUTPUT); // Zet groene led op pin 5 op output
      calibrateLineSensor();
      Serial.begin(9600);
      status=1;
      Serial.println(status);
    }
  }
}

// Loop methode voor het lezen en printen
int LineSensors::checkWaardesLS() {
    if ((uint16_t)(millis() - LaatsteGelezenUitvoer) >= 100) {
        LaatsteGelezenUitvoer = millis();
        lineSensors.readCalibrated(lineSensorValues);
        printReadingsToSerial(); 
    }
    if (buttonB.isPressed()){
        delay(1000);
        calibrateLineSensor();
    }
}

// Methode om de lijnsensoren te kalibreren
int LineSensors::calibrateLineSensor() {
    digitalWrite(5, LOW); // Zet de groene LED uit
    for (uint16_t i = 0; i < 400; ++i) {
        lineSensors.calibrate(); // Kalibreer de sensoren 400 keer
        motors.setSpeeds(150, -165); // Vooruit met links, achteruit met rechts voor draaien
        delay(10); // Korte delay voor een vloeiende beweging
    }
    digitalWrite(5, HIGH); // Zet de groene LED aan
    motors.setSpeeds(0, -0);
    return 0;
}



// Methode om de waarden naar de seriële monitor te printen
void LineSensors::printReadingsToSerial() {
    Serial.print("Line sensoren output: ");
    for (uint8_t i = 0; i < 3; i++) {
        int mappedValue = map(lineSensorValues[i], 0, 1000, 0, 10000);
        Serial.print(mappedValue);
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
        Serial.print(" Dit is de donkerste sensor : ");
        Serial.print(DonkersteSensor);
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
// int LineSensors::KleurCheck() {
//   for (int i = 0; i < 3; ++i) {
//         if (lineSensorValues[i] > 50 && lineSensorValues[i] < 950) {
//             LSKleur = i;
//         }
//     } 
int LineSensors::KleurCheck() {
  for (int i = 0; i < 3; ++i) {
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
}
}

    void LineSensors::LSrouteVersturen() {
    if (LSKleur1 > 600 && LSKleur1 < 1100) {
      //Zumo32U4.rijd_vooruit(---);
      //Groen
    }
    if (LSKleur > 2400 && LSKleur < 2700) {
      //Zumo32U4.rijd_vooruit(---);
      //Grijs voor Links
    }
    if (LSKleur2 > 2100 && LSKleur2 < 2500) {
      //Zumo32U4.rijd_vooruit(---);
      // Grijs voor Rechts
    }
    if (LSKleur > 2700 && LSKleur < 4500) {
      //Zumo32U4.rijd_vooruit(---);
      //Bruin voor Links
    }
    if (LSKleur2 > 2700 && LSKleur2 < 4500) {
      //Zumo32U4.rijd_vooruit(---);
      //Bruin voor Rechts
    }
}

