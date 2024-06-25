// #include "LineSensors.h"
// #include "Motors.h"
// #include "inertial_sensor.h"
// #include <Zumo32U4.h>
// #include <Wire.h>

// // Hier worden de objecten gemaakt die aangeroepen worden.
// Zumo32U4ButtonC buttonC;
// Zumo32U4ButtonB buttonB;
// Zumo32U4IMU imu;
// LineSensors myLineSensors;
// InertialSensor inertialSensor1;
// Motors myMotors;
// int MaxSpeed; // Globaal variabel voor maximale snelheid. 

// // Dit is de standaard setup functie, deze wordt 1x uitgevoerd. Hier worden alle snelheden op 0 gezet van de motoren
// // en alle sensoren/serial monitoren gestart.
// void setup() {

//   pinMode(LED_BUILTIN, OUTPUT);
//   myMotors.stop();
//   Serial.begin(9600);
//   delay(3000);
//   Serial.println("Setup is gestart!");
//   Wire.begin();
//   imu.enableDefault();
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
//     myLineSensors.checkWaardesLS();  // Roep de loop methode van het object aan

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
// // Hieronder staat de implementatie voor andere kleuren, maar hier hadden wij helaas geen tijd meer voor.
// // De logica is er wel maar het is nog niet goed genoeg afgesteld en geimplementeerd om het perfect werkend te krijgen.

//     // if (kleur == "Groen") {
//     //   Serial.print("Groen is aan. \n ");
//     //   MaxSpeed = myMotors.speedGreen();
//     //   myMotors.lineFollow(MaxSpeed, LineWaardes, allWhite);
//     // }
//     // else if (kleur == "GrijsLR"){
//     //   Serial.print("GrijsLR is aan ");
//     //   myMotors.stop();
//     //   delay(5000);
//     //   myMotors.speedBlack();
//     //   kleur = " ";
//     // }
//     // else if (kleur == "GrijsL") {
//     //   Serial.print("GrijsL is aan ");
//     //      while (LineWaardes != 0);{
//     //       myMotors.lineFollow(MaxSpeed, LineWaardes, allWhite );
//     //      }
//     //     myMotors.turnLeft();
//     //     kleur = " ";
//     //  }
//     // else if (kleur == "GrijsR") {
//     //   Serial.print("GrijsR is aan ");
//     //     while (LineWaardes != 4000);{
//     //       myMotors.lineFollow(MaxSpeed, LineWaardes, allWhite );
//     //      }

//     //     myMotors.turnRight();
//     //     kleur = " ";
//      }
//         // else if (kleur == "Bruin Links") {
//         //     myMotors.speedBruinL();  // Veronderstel dat deze functie bestaat
//         //    kleur = " ";
//         // } else if (kleur == "Bruin Rechts") {
//         //     myMotors.speedBruinR();  // Veronderstel dat deze functie bestaat
//         //    kleur = " ";
//         // }
//         else if (kleur == "Zwart") {
//           int MaxSpeed = myMotors.speedBlack();
//           myMotors.lineFollow(MaxSpeed, LineWaardes, allWhite);
//           kleur = " ";
//         }
//   }
// }