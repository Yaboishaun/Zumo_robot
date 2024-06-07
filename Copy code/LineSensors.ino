#include "LineSensors.h"
#include "Motors.h"
#include "inertial_sensor.h"
#include <Zumo32U4.h>
#include <Wire.h>

Zumo32U4ButtonC buttonC;
Zumo32U4ButtonB buttonB;
Zumo32U4IMU imu;
LineSensors myLineSensors;
InertialSensor inertialSensor1;
Motors myMotors;

void setup(){

  pinMode(LED_BUILTIN, OUTPUT);
  myMotors.stop();
  Serial.begin(9600);
  delay(3000);
  Serial.println("Setup is gestart!");
  Wire.begin();
  imu.enableDefault();
  // myMotors.speedBlack();

}
void loop() {
    int start= myLineSensors.startup();
    // if (buttonC.getSingleDebouncedPress()){
    //   myMotors.stop();
    //   start = 0;
    // }
    if (start == 1){
      //int  MaxSpeed = myMotors.speedBlack();
      myLineSensors.checkWaardesLS(); // Roep de loop methode van het object aan
      int Serror = myLineSensors.SensorenE();  
      if (buttonB.getSingleDebouncedPress()){
        myMotors.stop();
        delay(2000);
        myLineSensors.calibrateLineSensor();
        int MaxSpeed = myMotors.speedBlack();
      }
      int LineWaardes = myLineSensors.checkLijnen();
      myLineSensors.KleurCheck();
      String kleur = myLineSensors.LSrouteVersturen(); // Bewaar het resultaat van KleurCheck

    if (kleur == "Groen") {
      int MaxSpeed = myMotors.speedGreen();
      myMotors.lineFollow(MaxSpeed, LineWaardes, Serror );
    } 
    // else if (kleur == "GrijsL") {
    //      myMotors.speedGrijsL();  
    //  } 
    // else if (kleur == "GrijsR") {
    //     myMotors.speedGrijsR();  // Veronderstel dat deze functie bestaat
    // } 
    // else if (kleur == "Bruin Links") {
    //     myMotors.speedBruinL();  // Veronderstel dat deze functie bestaat
    // } else if (kleur == "Bruin Rechts") {
    //     myMotors.speedBruinR();  // Veronderstel dat deze functie bestaat
    // }
    else{
      int MaxSpeed = myMotors.speedBlack();   
      myMotors.lineFollow(MaxSpeed, LineWaardes, Serror);
    }
}
}