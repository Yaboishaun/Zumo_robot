#include "HardwareSerial.h"
#include <Arduino.h>
//#include <cstdio> // Voor sprintf
#include <stdint.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include "ProxySensor.h"

ProxySensor::ProxySensor() {}
ProxySensor::~ProxySensor() {}

Zumo32U4Motors motors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonA buttonA;

const uint16_t turnSpeedMax = 300;
const uint16_t turnSpeedMin = 150;
const uint16_t deceleration = 10;
const uint16_t acceleration = 10;

#define LEFT 0
#define RIGHT 1

bool senseDir = RIGHT;
bool turningLeft = false;
bool turningRight = false;
uint16_t turnSpeed = turnSpeedMax;

void turnRight() {
  motors.setSpeeds(turnSpeed, -turnSpeed);
  turningLeft = false;
  turningRight = true;
}

void turnLeft() {
  motors.setSpeeds(-turnSpeed, turnSpeed);
  turningLeft = true;
  turningRight = false;
}

void stop() {
  motors.setSpeeds(0, 0);
  turningLeft = false;
  turningRight = false;
}

void ProxySensor::setup() {
  initFrontSensor();
  buttonA.waitForButton();
}

bool ProxySensor::ZieObject() {
  read();
  uint8_t leftValue = countsFrontWithLeftLeds();
  uint8_t rightValue = countsFrontWithRightLeds();
  bool objectSeen = leftValue >= sensorThreshold || rightValue >= sensorThreshold;
  bool zekerweten = leftValue == rightValue;

  if (objectSeen) {
    turnSpeed -= deceleration;
  } else {
    turnSpeed += acceleration;
  }

  turnSpeed = constrain(turnSpeed, turnSpeedMin, turnSpeedMax);

  if (objectSeen) {
    ledYellow(1);

    if (leftValue < rightValue) {
      turnRight();
      senseDir = RIGHT;
    } else if (leftValue > rightValue) {
      turnLeft();
      senseDir = LEFT;
    } else if (zekerweten) {
      bool zien = true;
      while (zien) {
        motors.setSpeeds(175, 175);
        delayMicroseconds(1000000);
        read();
        leftValue = countsFrontWithLeftLeds();
        rightValue = countsFrontWithRightLeds();
        zekerweten = leftValue == rightValue;
        if (!zekerweten) {
          zien = false;
        }
      }
    }
  } else {
    ledYellow(0);

    if (senseDir == RIGHT) {
      turnRight();
    } else {
      turnLeft();
    }
  }
}

void ProxySensor::printReadingsToSerial() {
  read();
  leftValue = countsFrontWithLeftLeds();
  rightValue = countsFrontWithRightLeds();
  Readings[0] = leftValue;
  Readings[1] = rightValue;
  proxFrontActive = readBasicFront();
  static char buffer[80];
  sprintf(buffer, "%d %d  %d\n",
          Readings[0],
          Readings[1],
          proxFrontActive);
  Serial.print(buffer);
}
