#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
int motorSpeed = 200;
void setup() {
Serial.begin(9600);
}

void loop() {
  commands();
}

void commands() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'r') {
      commandR();
    } else if (command == 'l') {
      commandL();
    } else if (command == 'x') {
      motors.setSpeeds(0,0);
    } else if (command == 'e') {
      adjustSpeed();
    } else {
      setMotorSpeed(command);
    }
  }
}

void commandR() {
      motors.setSpeeds(200,200);
      delay(2000);
      motors.setSpeeds(100,200 ); 
      delay(2000);
      motors.setSpeeds(200,200);
      delay(2000);
      motors.setSpeeds(100,200 ); 
      delay(2000);
      motors.setSpeeds(0,0);
}

void commandL() {
      motors.setSpeeds(200, 200);
      delay(2000);
      motors.setSpeeds(200, 100); 
      delay(2000);
      motors.setSpeeds(200, 200);
      delay(2000);
      motors.setSpeeds(200, 100); 
      delay(2000);
      motors.setSpeeds(0,0);
}

void adjustSpeed() {
  Serial.print("Geef de nieuwe snelheid (positief), de huidige snelheid is: ");
  Serial.println(motorSpeed);
  while (Serial.available() == 0);
  int newSpeed = Serial.parseInt();
  if (newSpeed > 0) {
    motorSpeed = newSpeed;
    Serial.print("De nieuwe snelheid is ingesteld op: ");           
    Serial.println(motorSpeed);
  } else {
    Serial.println("Ongeldige invoer");
  }
}

void setMotorSpeed(char command) { 
    if (command == 'w') {
      motors.setSpeeds(motorSpeed, motorSpeed); 
    } else if (command == 's') {
      motors.setSpeeds(-motorSpeed, -motorSpeed);
    } else if (command == 'a') {
      motors.setSpeeds(-motorSpeed,motorSpeed);
    } else if (command == 'd') {
      motors.setSpeeds(motorSpeed, -motorSpeed);
    }
  }
