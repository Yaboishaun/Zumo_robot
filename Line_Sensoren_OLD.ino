#include <Wire.h>
#include <Zumo32U4.h>
Zumo32U4ButtonB buttonB;
Zumo32U4LineSensors lineSensors;

uint16_t lineSensorValues[3] = { 0, 0, 0 };

void setup() {
  lineSensors.initThreeSensors();
  pinMode(5, OUTPUT);
  calibrateLineSensors();
  Serial.begin(9600);
}

// Kalibreren van de lijnsensoren + Groene Led gaat aan
void calibrateLineSensors() {
   digitalWrite(5, LOW);
  for (uint16_t i = 0; i < 200; i++) {
    lineSensors.calibrate();
  }
  digitalWrite(5, HIGH);
}
// Roep de printReadingsToSerial functie aan elke 100 ms + Calibrate de sensoren als knop B wordt ingedrukt
void loop() {
  static uint16_t LaatsteGelezenUitvoer = 0;
  if ((uint16_t)(millis() - LaatsteGelezenUitvoer) >= 100) {
    LaatsteGelezenUitvoer = millis();
    lineSensors.readCalibrated(lineSensorValues);
    printReadingsToSerial(); 
  }
  if (buttonB.isPressed()){
  calibrateLineSensors();
 }
}
// Print de output naar de seriële monitor
void printReadingsToSerial() {
  Serial.print("Line sensoren output: ");
  for (uint8_t i = 0; i < 3; i++) {
    Serial.print(lineSensorValues[i]);
    Serial.print(" ");
  }
  Serial.println();
}
