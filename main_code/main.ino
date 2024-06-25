// #include "LineSensors.h"
// #include "Motors.h"
// #include "inertial_sensor.h"
// #include <Zumo32U4.h>
// #include <Wire.h>
// #include "ProxySensor.h"
// #include "Xbee.h"

// // Hier worden de objecten gemaakt die aangeroepen worden.
// Zumo32U4ButtonC buttonC;
// Zumo32U4ButtonB buttonB;
// Zumo32U4IMU imu;
// LineSensors myLineSensors;
// InertialSensor inertialSensor1;
// Motors myMotors;
// ProxySensor proxy;
// Xbee xbee;
// Zumo32U4ButtonA ButtonA;
// int MaxSpeed; // Globaal variabel voor maximale snelheid. 

// // Dit is de standaard setup functie, deze wordt 1x uitgevoerd. Hier worden alle snelheden op 0 gezet van de motoren
// // en alle sensoren/serial monitoren gestart.
// void setup() {

//   pinMode(LED_BUILTIN, OUTPUT);
//   myMotors.stop();
//   Serial1.begin(9600);
//   Serial.begin(9600);
//   delay(3000);
//   Serial.println("Setup is gestart!");
//   Wire.begin();
//   imu.enableDefault();
//     proxy.setup();

//   MaxSpeed = myMotors.speedBlack(); // De default snelheid is de snelheid van de zwarte lijn, omdat deze het meest voorkomt.
// }
// // Dit is de loop functie, hier gebeurt alle logica.
// void loop() {
//   int start = myLineSensors.startup(); // Dit zorgt ervoor dat deze functie niet nog een keer volledig wordt uitgevoerd.
//   // if (buttonC.getSingleDebouncedPress()){
//   //   myMotors.stop();
//   //   start = 0;
//   // }
//   if (start == 1) {
//     // int  MaxSpeed = myMotors.speedBlack();
//     // Serial.print("Dit is MaxSpeed");
//     // Serial.print(MaxSpeed);
//     // Serial.print(".\n");
//     myLineSensors.checkWaardesLS(); 
//     } // Roep de loop methode van het object aan

// // Dit is een stukje logica die het kalibratie proces nog een keer doorloopt zodra buttonB wordt ingedrukt.
//     if (buttonB.getSingleDebouncedPress()) {
//       myMotors.stop();
//       delay(2000);
//       myLineSensors.calibrateLineSensor();
//       MaxSpeed = myMotors.speedBlack();
//     }
//     bool allWhite = false;
//     int LineWaardes = myLineSensors.checkLijnen(allWhite);
//     // if (LineWaardes = -1){
//     // myMotors.straight();
//     // }
//     myLineSensors.KleurCheck();
//     String kleur = myLineSensors.LSrouteVersturen();  // Bewaar het resultaat van KleurCheck
//     myMotors.lineFollow(MaxSpeed, LineWaardes, allWhite, kleur);
//       proxy.ZieObject();
//   proxy.printReadingsToSerial();
//     xbee.leesWaarde();
//   xbee.converteer();
//   if (ButtonA.getSingleDebouncedPress()) {
//     Serial1.println("testln");
//   }
// }
  
  