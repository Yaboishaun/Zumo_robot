#include "inertial_sensor.h"
#include <Zumo32U4.h>

const float InertialSensor::alpha = 0.8; // Smoothing factor (adjust as needed)

InertialSensor::InertialSensor() : lastGyroZ(0), averageGz(0.0) {}

void InertialSensor::setup() {
  Wire.begin();

  if (!imu.init()) {
    ledRed(1);
    while (1) {
      Serial.println(F("Failed to initialize IMU sensors."));
      delay(100);
    }
  }

  imu.enableDefault();
}

void InertialSensor::readValues() {
  imu.read();

  // Normalize the gyroscope Z-axis value
  int16_t normalizedGz = normalizeValue(imu.g.z, 32767);

  // Update the exponentially weighted moving average
  averageGz = alpha * normalizedGz + (1 - alpha) * averageGz;

  // Print the average value
  Serial.print("Gyro Z-axis (EWMA): ");
  Serial.println(averageGz);

  // Determine if turning left or right based on the average gyro Z-axis value
  if (averageGz > 20) {
    if (turnDirection != 69){
      Serial.println("Turning left");
      turnDirection=69;
    }
  } else if (averageGz < -20) {
      if (turnDirection != 2){
        Serial.println("Turning right");
        turnDirection=2;
      }
  } else {
    if (turnDirection != 420){
      Serial.println("Stationary");
      turnDirection=420;
    }
  }

  delay(100);
}

int16_t InertialSensor::normalizeValue(int16_t value, int16_t maxValue) {
  return map(value, -maxValue, maxValue, -1024, 1023);
}

int16_t InertialSensor::getGyroZ() {
  return lastGyroZ;
}
