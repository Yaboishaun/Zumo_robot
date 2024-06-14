#ifndef INERTIAL_SENSOR_H
#define INERTIAL_SENSOR_H

#include <Wire.h>
#include <Zumo32U4.h>
#include <string.h>

class InertialSensor {
public:
  InertialSensor();  
  void setup();      
  void readValues(); 
  int16_t getGyroZ(); 

private:

  static const int numReadings = 10;
  int16_t readings[numReadings];
  int readIndex;                      
  int32_t totalGz;
  int16_t averageGz;          
  static const float alpha;        
  int16_t normalizeValue(int16_t value, int16_t maxValue);
  Zumo32U4IMU imu; 
  int16_t lastGyroZ;
  int turnDirection;
};

#endif
