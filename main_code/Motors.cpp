#include "Motors.h"
#include "LineSensors.h"
#include <Zumo32U4.h>
#include <Wire.h>

//#define wordt gedaan zodat er KP, KD en KI gebruikt kan worden en makkelijk de waardes kunnen veranderen waar nodig.
#define KP 0.4  // Waarde voor de kp, hiermee wordt de P regelaar beinvloed.
#define KD 0.6  // Waarde voor de kd, hiermee wordt de D regelaar beinvloed.
#define KI 0.0  // Waarde voor de ki, hiermee wordt de I regelaar beinvloed (Deze hebben wij niet nodig gehad voor de Zumo.).

// De waarde voor turnDelay heeft Timo handmatig getest met volle batterijen. Dit is de tijd die nodig is voor het volledig draaien van de Robot op 300 speed.
#define turnDelay 1050
#define defaultDelay 1000

// Default constructor met een aantal standaard waardes, dit voorkomt dat de waardes ergens anders nog bepaald moeten worden.
Motors::Motors()
  : speedLeft(0), speedRight(0), userSpeed(0), lastError(0), integral(0), command(0), errorLeft(false), errorRight(false), countsLeft(0), countsRight(0) {}

// Dit is de main functie voor het volgen van de lijn, er wordt gebruikt gemaakt van een PID-controller om de veranderingen in de snelheid te bepalen.

int Motors::lineFollow(int maxSnelh, int lineValues, bool allWhite) {

  // Hier wordt de PID regelaar ingesteld met uitgerekende waardes, deze waardes zijn voornamelijk meetwaardes die wij meegeven.
  int position = lineValues;
  error = position - 2000;  // Dit zou afhankelijk moeten zijn van de breedte van de lijnsensoren
  integral += error;
  int derivative = error - lastError;
  int motorSpeed = KP * error + KD * derivative + KI * integral;

  // Dit is de functie voor wanneer de Zumo robot alleen wit ziet, zodat de robot enkel vooruit blijft rijden.
  if (allWhite) {
    straight();
  }
  // Hier wordt de snelheid van de robot aangepast naar de juiste waarde per motor.
  lastError = error;
  int leftSpeed = maxSnelh + motorSpeed;
  int rightSpeed = maxSnelh - motorSpeed;
  leftSpeed = constrain(leftSpeed, -400, 400);
  rightSpeed = constrain(rightSpeed, -400, 400);
  motors.setLeftSpeed(leftSpeed);
  motors.setRightSpeed(rightSpeed);
  delay(20);
  return 0;
}
int Motors::lineFollow(int maxSnelh, int lineValues, bool allWhite, String kleur) {

  // Hier wordt de PID regelaar ingesteld met uitgerekende waardes, deze waardes zijn voornamelijk meetwaardes die wij meegeven.
  int position = lineValues;
  error = position - 2000;  // Dit zou afhankelijk moeten zijn van de breedte van de lijnsensoren
  integral += error;
  int derivative = error - lastError;
  int motorSpeed = KP * error + KD * derivative + KI * integral;

  // Dit is de functie voor wanneer de Zumo robot alleen wit ziet, zodat de robot enkel vooruit blijft rijden.
  if (allWhite) {
    straight();
  }
  // Hier wordt de snelheid van de robot aangepast naar de juiste waarde per motor.
  lastError = error;
  int leftSpeed = maxSnelh + motorSpeed;
  int rightSpeed = maxSnelh - motorSpeed;
  leftSpeed = constrain(leftSpeed, -400, 400);
  rightSpeed = constrain(rightSpeed, -400, 400);
  motors.setLeftSpeed(leftSpeed);
  motors.setRightSpeed(rightSpeed);
  delay(20);

  return 0;
}

// Hier is de default snelheid die gebruikt wordt wanneer de robot zwart ziet.
int Motors::speedBlack() {
  return 400;
}
// Hier is de default snelheid die gebruikt wordt wanneer de robot groen ziet.
int Motors::speedGreen() {
  return 200;
}

// Dit is een debug functie, deze hebben we gebruikt om te kunnen controlleren wat de snelheid is op bepaalde momenten.
void Motors::printSpeed() {
  Serial.print("Left speed: ");
  Serial.print(speedLeft);
  Serial.print("\tRight speed: ");
  Serial.println(speedRight);
}

// Dit is de handmatige aansturing van de robot. Deze controlleert de serial monitor op een char en bepaald welke functie er aangeroepen moet worden.
// Hier kunnen meer functies aan toegevoegd worden, voor meer controle over de robot in de handmatige modus.
void Motors::handleUserCommands() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'F':
        straight();
        break;
      case 'B':
        stop();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        stop();
        break;
    }
  }
}
// Default functie voor rechts sturen.
void Motors::turnRight() {
  motors.setSpeeds(200, -200);
  delay(turnDelay);
  stop();
}
// Default functie voor links sturen.
void Motors::turnLeft() {
  motors.setSpeeds(0, 200);
  delay(turnDelay);
  stop();
}
// Default functie voor rechtdoor rijden.
void Motors::straight() {
  motors.setSpeeds(200, 200);
}
// Default functie voor stoppen met rijden.
void Motors::stop() {
  motors.setSpeeds(0, 0);
}
// Default functie voor rechtsom draaien.
void Motors::circleClockwise() {
  motors.setSpeeds(200, -200);
}
// Default functie voor linksom draaien.
void Motors::circleCounterClockwise() {
  motors.setSpeeds(-200, 200);
}
void Motors::Left() {
  motors.setSpeeds(0, 200);
}
void Motors::Right() {
  motors.setSpeeds(200, 0);
}
void Motors::HardLeft() {
  motors.setSpeeds(0, 400);
}
void Motors::HardRight() {
  motors.setSpeeds(400, 0);
}
void Motors::HardStraight() {
  motors.setSpeeds(400, 400);
}
void Motors::Back() {
  motors.setSpeeds(-200, -200);
}
void Motors::HardBack() {
  motors.setSpeeds(-400, -400);
}
