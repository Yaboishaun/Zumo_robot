#include "LineSensors.h"
#include "Motors.h"
#include "inertial_sensor.h"
#include <Zumo32U4.h>
#include <Wire.h>

Zumo32U4IMU imu;
LineSensors lineSensor1;
Motors motors1;
InertialSensor inertialSensor1;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  delay(3000);
  Serial.println("Setup is gestart!");
  Wire.begin();
  imu.enableDefault();

}
void loop (){

  lineSensor1.startup();
  lineSensor1.checkWaardesLS();

}