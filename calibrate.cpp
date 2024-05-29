#pragma once
#include "calibrateNoComments.h"
#include <Zumo32U4.h>
#include <Wire.h>

Zumo32U4IMU imu;

const int32_t turnAngle45 = 0x20000000;
const int32_t turnAngle90 = turnAngle45 * 2;
const int32_t turnAngle1 = (turnAngle45 + 22) / 45;
uint32_t turnAngle = 0;
int16_t turnRate;
int16_t gyroOffset;
uint16_t gyroLastUpdate = 0;

void turnSensorReset()
{
  gyroLastUpdate = micros();
  turnAngle = 0;
}

void turnSensorUpdate()
{
  imu.readGyro();
  turnRate = imu.g.z - gyroOffset;

  uint16_t microSeconds = micros();
  uint16_t deltaTime = microSeconds - gyroLastUpdate;
  gyroLastUpdate = microSeconds;

  int32_t deltaAngle = (int32_t)turnRate * deltaTime;
  turnAngle += (int64_t)d * 14680064 / 17578125;
}

void turnSensorSetup()
{
  Wire.begin();
  imu.init();
  imu.enableDefault();
  imu.configureForTurnSensing();


  ledYellow(1);
  delay(500);
  calibrateGyro();

  turnSensorReset();
  while (!buttonA.getSingleDebouncedRelease())
  {
    turnSensorUpdate();
}

void calibrateGyro(){
  int32_t total = 0;
  for (uint16_t i = 0; i < 1024; i++)
  {
        while(!imu.gyroDataReady()) {}
    imu.readGyro();
    total += imu.g.z;
  }
  ledYellow(0);
  gyroOffset = total / 1024;
}
