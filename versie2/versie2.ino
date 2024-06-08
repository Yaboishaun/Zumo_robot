#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;

// Array om sensorwaarden op te slaan
unsigned int sensorValues[5];
bool running = true; // Variabele om de status van de motoren bij te houden
int lastError = 0; // Variabele om de laatste bekende fout op te slaan
int baseSpeed = 250; // Basis snelheid voor zwarte lijn

// Drempelwaarden voor zwarte, groene en witte lijnen
unsigned int blackThreshold;
unsigned int greenThreshold;
unsigned int whiteThreshold;

void setup() {
  // Initialiseer de seriële communicatie
  Serial.begin(9600);
  
  // Initialiseer de lijnsensoren
  lineSensors.initFiveSensors();
  
  // Wacht tot knop A wordt ingedrukt om te kalibreren
  Serial.println("Druk op knop A om te kalibreren...");
  while (!buttonA.isPressed()) {
    // Wacht op knop A
    delay(100);
  }

  // Kalibreer de lijnsensoren door meerdere rondjes te draaien
  Serial.println("Kalibreren...");
  for (int j = 0; j < 3; j++) { // Aantal rondjes verlaagd naar 3
    for (int i = 0; i < 40; i++) { // Iteraties verlaagd naar 40
      lineSensors.calibrate();
      motors.setLeftSpeed(300);
      motors.setRightSpeed(-300);
      delay(20);
    }
  }
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  Serial.println("Kalibratie voltooid.");

  // Lees de waarden voor zwart en wit
  Serial.println("Kalibratie zwart/wit waarden...");
  int minValues[5] = {1000, 1000, 1000, 1000, 1000};
  int maxValues[5] = {0, 0, 0, 0, 0};
  for (int i = 0; i < 40; i++) { // Iteraties verlaagd naar 40
    lineSensors.readCalibrated(sensorValues);
    for (int j = 0; j < 5; j++) {
      if (sensorValues[j] < minValues[j]) {
        minValues[j] = sensorValues[j];
      }
      if (sensorValues[j] > maxValues[j]) {
        maxValues[j] = sensorValues[j];
      }
    }
    delay(20);
  }
  blackThreshold = (minValues[0] + minValues[1] + minValues[2] + minValues[3] + minValues[4]) / 5 + 50; // Verhoog zwart threshold voor nauwkeurigheid
  whiteThreshold = (maxValues[0] + maxValues[1] + maxValues[2] + maxValues[3] + maxValues[4]) / 5 - 50; // Verlaag wit threshold voor nauwkeurigheid
  greenThreshold = (blackThreshold + whiteThreshold) / 2;

  Serial.print("Zwart: "); Serial.println(blackThreshold);
  Serial.print("Wit: "); Serial.println(whiteThreshold);
  Serial.print("Groen: "); Serial.println(greenThreshold);

  // Wacht tot knop B wordt ingedrukt om met het volgen van de lijn te beginnen
  Serial.println("Druk op knop B om de lijn te volgen...");
  while (!buttonB.isPressed()) {
    // Wacht op knop B
    delay(100);
  }
}

void loop() {
  // Controleer of knop C is ingedrukt om de motorstatus te wisselen
  if (buttonC.isPressed()) {
    running = !running; // Wissel de status van de motoren
    while (buttonC.isPressed()) {
      // Wacht tot knop C wordt losgelaten om te voorkomen dat de status meerdere keren wisselt
      delay(100);
    }
  }

  // Lees de waarden van de lijnsensoren
  int position = lineSensors.readLine(sensorValues);

  // Druk de sensorwaarden af naar de seriële monitor
  Serial.print("Sensorwaarden: ");
  for (int i = 0; i < 5; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

  // Detecteer of de lijn groen is op basis van de sensorwaarden
  bool isGreen = false;
  bool isBlack = false;
  bool isWhite = true;
  for (int i = 0; i < 5; i++) {
    if (sensorValues[i] > blackThreshold && sensorValues[i] < greenThreshold) { // Groene lijn drempelwaarde
      isGreen = true;
      isWhite = false;
      break;
    }
    if (sensorValues[i] < blackThreshold) { // Zwarte lijn drempelwaarde
      isBlack = true;
      isWhite = false;
      break;
    }
    if (sensorValues[i] < whiteThreshold) {
      isWhite = false;
    }
  }

  // Geef prioriteit aan de middelste sensor
  if (sensorValues[2] < blackThreshold) {
    isBlack = true;
    isGreen = false;
  } else if (sensorValues[2] > blackThreshold && sensorValues[2] < greenThreshold) {
    isGreen = true;
    isBlack = false;
  }

  if (isGreen) {
    // Als de lijn groen is, stel de snelheid in op halve snelheid
    baseSpeed = 125;
  } else if (isBlack) {
    // Als de lijn zwart is, stel de basis snelheid voor de zwarte lijn
    baseSpeed = 250;
  } else if (isWhite) {
    // Als alleen wit wordt gedetecteerd, ga rechtdoor
    motors.setLeftSpeed(baseSpeed);
    motors.setRightSpeed(baseSpeed);
    return; // Terugkeren naar het begin van de loop
  } else {
    // Als er geen lijn wordt gedetecteerd, stop de motoren
    baseSpeed = 0;
  }

  if (running) {
    // Bereken de fout (hoe ver we van de lijn af zijn)
    int error = position - 2000;

    // Als er geen lijn wordt gedetecteerd, gebruik de laatste bekende fout
    if (sensorValues[0] > whiteThreshold && sensorValues[1] > whiteThreshold && sensorValues[2] > whiteThreshold && sensorValues[3] > whiteThreshold && sensorValues[4] > whiteThreshold) {
      error = lastError;
    } else {
      lastError = error; // Update de laatste bekende fout
    }

    // Bereken de motorcorrectie
    int speedDifference = error / 6; // Verlaag de correctie om soepeler te rijden

    // Bereken de snelheden voor beide motoren
    int leftSpeed = baseSpeed + speedDifference;
    int rightSpeed = baseSpeed - speedDifference;

    // Beperk snelheden tot de maximale snelheid van 400
    leftSpeed = constrain(leftSpeed, 0, 400);
    rightSpeed = constrain(rightSpeed, 0, 400);

    // Stel de motorsnelheden in
    motors.setLeftSpeed(leftSpeed);
    motors.setRightSpeed(rightSpeed);
  } else {
    // Stop de motoren als de status niet actief is
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
  }
}
