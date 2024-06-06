#include "Motors.h"
#include "LineSensors.h"
#include <Zumo32U4.h>
#include <Wire.h>

#define turnDelay 1050
#define defaultDelay 800
#define LINE_SENSOR_CENTER 500;
LineSensors linesensor;

const char encoderErrorLeft[] PROGMEM = "!<c2";
const char encoderErrorRight[] PROGMEM = "!<e2";

Motors::Motors() : speedLeft(0), speedRight(0), userSpeed(0), maxSpeed(300), kp(0.1), kd(0.05), ki(0), lastError(0), integral(0){

}
int Motors::speedBlack() {
    maxSpeed = 300;  // Set the maximum speed for black lines
    return maxSpeed;
}

int Motors::speedGreen() {
    delay(500);
    maxSpeed = 200;  // Set the maximum speed for green lines
    printSpeed();
    return maxSpeed; // Return the selected speed
}

// Function to print selected speed to serial
void Motors::printSpeed() {
    Serial.print("Max Speed: ");
    Serial.println(maxSpeed);
    delay(500);
}

// Function to handle user commands via serial
void Motors::handleUserCommands() {
  if (Serial.available() > 0) {
    command = Serial.read();
    Serial.println("jahoor denk"); // Placeholder, remove if not needed
    if (command == 'l') {
      circleCounterClockwise();
    } else if (command == 'r') {
      circleClockwise();
    }
    checkEncoderErrors(); // Check for encoder errors
    if (command == '0') {
      readEncoderCounts(); // Read encoder counts
    }
  }
}

void Motors::lineFollow() {
    int position = lineSensors.readLine(sensors); // Get the line position
    int error = position - LINE_SENSOR_CENTER;

    integral += error;
    int derivative = error - lastError;

    int adjustment = kp * error + ki * integral + kd * derivative;

    speedLeft = maxSpeed - adjustment;
    speedRight = maxSpeed + adjustment;

    // Ensure speeds are within bounds
    if (speedLeft > maxSpeed) speedLeft = maxSpeed;
    if (speedRight > maxSpeed) speedRight = maxSpeed;
    if (speedLeft < -maxSpeed) speedLeft = -maxSpeed;
    if (speedRight < -maxSpeed) speedRight = -maxSpeed;

    motors.setSpeeds(speedLeft, speedRight);

    lastError = error;
}

// Function to check for encoder errors
void Motors::checkEncoderErrors() {
  errorLeft = encoders.checkErrorLeft();
  errorRight = encoders.checkErrorRight();

  if (errorLeft) {
    buzzer.playFromProgramSpace(encoderErrorLeft);
  }

  if (errorRight) {
    buzzer.playFromProgramSpace(encoderErrorRight);
  }
}

// Function to read encoder counts and display with error status
void Motors::readEncoderCounts() {
  countsLeft = encoders.getCountsLeft();
  countsRight = encoders.getCountsRight();
  errorLeft = encoders.checkErrorLeft();
  errorRight = encoders.checkErrorRight();

  snprintf_P(report1, sizeof(report1),
            PSTR("%6d %6d %1d %1d"),
            countsLeft, countsRight, errorLeft, errorRight);
  Serial.println(report1);
}


void Motors::turnRight() {
  motors.setSpeeds(400, -400);
  delay(turnDelay);
  motors.setSpeeds(0, 0);
}

void Motors::turnLeft() {
  motors.setSpeeds(-400, 400);
  delay(turnDelay);
  motors.setSpeeds(0, 0);
}

void Motors::straight() {
  motors.setSpeeds(400, 400);
  delay(defaultDelay);
  motors.setSpeeds(0, 0);
}

void Motors::stop() {
  motors.setSpeeds(0, 0);
  delay(defaultDelay);
}

// Movement routines (remained unchanged)
void Motors::circleClockwise() {
  digitalWrite(LED_BUILTIN, HIGH);

  for (int i = 1; i < 5; ++i) {
    straight();
    turnRight();
  }
  stop();
}

void Motors::circleCounterClockwise() {
  digitalWrite(LED_BUILTIN, HIGH);

  for (int i = 1; i < 5; ++i) {
    straight();
    turnLeft();
  }
  stop();
}

