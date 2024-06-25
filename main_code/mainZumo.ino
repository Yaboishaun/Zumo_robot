#include "LineSensors.h"
#include "Motors.h"
#include "inertial_sensor.h"
#include <Zumo32U4.h>
#include <Wire.h>
//Xbee hieronder:
#include "Xbee.h"
#include <Zumo32U4Buttons.h>
#include "SwitchModus.h"
SwitchModus sm;
//ChooseCase hieronder:


// Hier worden de objecten gemaakt die aangeroepen worden.
Zumo32U4ButtonC buttonC;
Zumo32U4ButtonB buttonB;
Zumo32U4IMU imu;
LineSensors myLineSensors;
InertialSensor inertialSensor1;
Motors myMotorss;

//Xbee:
Zumo32U4ButtonA TestButtonA;
int maxSpeed;                 // Globaal variabel voor maximale snelheid.
bool xbeeAansturing = false;  // Globale variabel voor het activeren van de Xbee.
bool test;
bool racen;
bool xb;
bool activeerProxy;
Xbee xbe;

// Dit is de standaard setup functie, deze wordt 1x uitgevoerd. Hier worden alle snelheden op 0 gezet van de motoren
// en alle sensoren/serial monitoren gestart.
void setup() {
  // Dit zijn de LineSensors en Motors
  pinMode(LED_BUILTIN, OUTPUT);
  racen = true;
  myMotorss.stop();
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(3000);
  Wire.begin();
  imu.enableDefault();
  maxSpeed = myMotorss.speedBlack();  // De default snelheid is de snelheid van de zwarte lijn, omdat deze het meest voorkomt.
}
// Dit is de loop functie, hier gebeurt alle logica.
void loop() {
  xb = sm.xbeeActive(true);
  if (xb) {
  racen = sm.ZumoRace(true);
  }
  if (racen) {
  int start = myLineSensors.startup();  // Dit zorgt ervoor dat deze functie niet nog een keer volledig wordt uitgevoerd.

  if (start == 1) {
    myLineSensors.checkWaardesLS();  // Roep de loop methode van het object aan

    // Dit is een stukje logica die het kalibratie proces nog een keer doorloopt zodra buttonB wordt ingedrukt.
    if (buttonB.getSingleDebouncedPress()) {
      myMotorss.stop();
      delay(2000);
      myLineSensors.calibrateLineSensor();
      maxSpeed = myMotorss.speedBlack();
    }
  
    bool allWhite = false;
    int LineWaardes = myLineSensors.checkLijnen(allWhite);
    myLineSensors.KleurCheck();
    String kleur = myLineSensors.LSrouteVersturen();  // Bewaar het resultaat van KleurCheck
    activeerProxy = myLineSensors.detectBrown();

    if (activeerProxy) {
     sm.ProxyActive(true);
    
    } else {
    myMotorss.lineFollow(maxSpeed, LineWaardes, allWhite, kleur);
    


  }

    //Hieronder begint de Xbee code.
    // xbee->converteer();
   // if (chooseCase->isModusActief()) {
      // xbee->uitvoer();
 //   }
  }
  //sm.ProxyActive(true);

  
 sm.xbeeActive(true); 
} }