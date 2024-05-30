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

//  the Reset method resets the timer and sets the turnAngle to 0.
void Reset() 
{
  gyroLastUpdate = micros();
  turnAngle = 0;
}

//  the Update method updates the turnrate based on the gyro readings, it calculates
//  turnrate based off of the z-axis on the gyro - the gyroOffset (which is changed in the calibrateGyro() function)
//  it calculates the turnangle using a preset formula using microSeconds, deltaTime, gyroLastUpdate, deltaAngle and turnRate
void Update()  
{
  imu.readGyro();
  turnRate = imu.g.z - gyroOffset;

  uint16_t microSeconds = micros();
  uint16_t deltaTime = microSeconds - gyroLastUpdate;
  gyroLastUpdate = microSeconds;

  int32_t deltaAngle = (int32_t)turnRate * deltaTime;
  turnAngle += (int64_t)d * 14680064 / 17578125;
}
//  in the setup the default settings for the object imu from the library Zumo32U4IMU is getting its default settings and is being enabled.
//  the yellow led is turned on to indicate that the calibration process is happening.
//  calibrateGyro() is a function that takes the average value over 1024 readings using a for loop.
//  it waits for the buttonA to be pressed in order to update the turnrate and turnangle.
void Setup()
{
  Wire.begin();
  imu.init();
  imu.enableDefault();
  imu.configureForTurnSensing();
  ledYellow(1);
  delay(500);
  calibrateGyro();
  Reset();
  while (!buttonA.getSingleDebouncedRelease())
  {
    Update();
  }
}
//  the calibrateGyro function goes through the .readGyro() method 1024 times and devides that by the amount of readings and writes that to the gyroOffset.  

void calibrateGyro(){
  int32_t total = 0;
  for (uint16_t i = 0; i < 1024; i++)
  {
        while(!imu.gyroDataReady()) {}
    imu.readGyro();

// add the Z axis reading to the total.
    total += imu.g.z;
  }
  ledYellow(0);
  gyroOffset = total / 1024;
}
