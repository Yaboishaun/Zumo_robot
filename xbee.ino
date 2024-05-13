#include <Zumo32U4.h>
#include <Wire.h>
Zumo32U4Motors motoren;


//initialiseer de te gebruiken variabelen voor deze code
int speed = 0;
byte data;

void setup() {
  Serial1.begin(9600);
  

}

void loop() {
  //checkt of er een serieel beriicht binnen komt vanuit de Xbee, zo ja dan wordt dit opgeslagen in de variabele genaamd data
if (Serial1.available() > 0) {
  data = Serial1.read();

  //Wanneer de data die binnenkomt via de Xbee overeen komt met links, rechts of voorwaarts reageren de motoren hierop door in beweging te komen en reset elke keer weer de motoren zodat de Zumo niet door blijft rijden.
  if (data == 'rechts') {
      for (speed; speed <= 400; speed++) {
    motoren.setLeftSpeed(speed);
      }
  }
  if (data == 'links') {
      for (speed; speed <= 400; speed++) {
    motoren.setRight(speed);
  }
  if (data == 'voorwaarts') {
      for (speed; speed <= 400; speed++) {
    motoren.setSpeeds(speed, speed);
  }
  else {
    for (speed; speed <= 400; speed--) {
    motoren.setSpeeds(speed, speed);
    }
  }


}

}
}

}
