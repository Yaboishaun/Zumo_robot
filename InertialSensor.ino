#include "calibrateNoComments.h"
#include <Zumo32U4.h>

// sensor 1 is an object of class InertialSensor
InertialSensor sensor1;

// setup runs the Setup function once for sensor1
void setup(){
  sensor1.Setup();
}

// prints "Calibrating!" to the serial monitor whilst the Setup is running.
void loop(){
  while(sensor1.Setup()){
    Serial.println("Calibrating!")
  }
}
