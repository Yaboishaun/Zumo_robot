#include "inertial_sensor.h"
#include <Zumo32U4.h>

// Deze alpha waarde is een waarde die aangepast kan worden, dit zorgt voor een andere weging in het berekenen van het gemiddelde.
const float InertialSensor::alpha = 0.8;

// Default constructor met die twee waardes meekrijgt, zodat deze niet op een andere waarde kunnen starten.
InertialSensor::InertialSensor()
  : lastGyroZ(0), averageGz(0.0) {}

// Dit is de setup functie, hiermee worden de IMU sensoren aangezet. Er is ook een exception toegevoegd voor het geval de initialize niet lukt hierbij wordt de rode led aangezet.
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

// Dit is de functie die de waardes van de IMU sensoren leest, normaliseerd en uitrekend. Deze functie wordt ook gebruikt om in de serial monitor te kunnen printen welke kant de Zumo op stuurt.
void InertialSensor::readValues() {
  imu.read();
  int16_t normalizedGz = normalizeValue(imu.g.z, 32767);
  averageGz = alpha * normalizedGz + (1 - alpha) * averageGz;
  Serial.print("Gyro Z-axis: ");
  Serial.println(averageGz);
  if (averageGz > 20) {
    if (turnDirection != 69) {
      Serial.println("Turning left");
      turnDirection = 69;
    }
  } else if (averageGz < -20) {
    if (turnDirection != 2) {
      Serial.println("Turning right");
      turnDirection = 2;
    }
  } else {
    if (turnDirection != 420) {
      Serial.println("Stationary");
      turnDirection = 420;
    }
  }

  delay(100);
}
// Hier worden de waardes genormaliseerd met de map functie.
int16_t InertialSensor::normalizeValue(int16_t value, int16_t maxValue) {
  return map(value, -maxValue, maxValue, -1024, 1023);
}
// Hier wordt de laatste Z waarde van de Gyro terug gestuurd.
int16_t InertialSensor::getGyroZ() {
  return lastGyroZ;
}
