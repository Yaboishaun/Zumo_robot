#include "Xbee.h"
#include <Zumo32U4.h>
#include <Zumo32U4Motors.h>
Zumo32U4Motors motoren;
#include <Vector.h>
#include "Motors.h"
#include "ProxySensor.h"
Motors mtr;
ProxySensor proximit;

//Vector<int> nummer;
// int nummer[12] = { 119, 87, 115, 83, 97, 65, 100, 68, 102, 101, 113, 105 };
// int characters[12] = { "w", "W", "s", "S", "a", "A", "d", "D", "f", "e", "q", "i" };
using namespace std;
// int w = 119;
// int HW = 87;
// int s = 115;
// int HS = 83;
// int a = 97;
// int HA = 65;
// int d = 100;
// int HD = 68;
// int f = 102;
// int e = 101;
// int q = 113;

Xbee::Xbee() {
}
Xbee::~Xbee() {
}
void Xbee::check() {
  activeerXbee = true;
}
//Hiermee wordt gekeken of er een nieuw commando binnenkomt vanuit de Xbee en wanneer dit zo is wordt deze informatie uitgelezen en in de variabele data gestored.
// String Xbee::leesWaarde() {
//   if (Serial1.available() > 0) {
//     d = Serial1.readString();
//     read = true;
//     Serial1.println(d);
//     return d;
//   }
//   //Hier moet straks code voor de toets om xbee te activeren.
// }

 void Xbee::converteer() {
  // if (read) {
  //   for (int i = 0; i < 12; ++i) {
  //     read = false;
  //     Serial1.println(data);
  //   }
  // }
  Serial1.setTimeout(1);
  if (Serial1.available() > 0) {
    d = Serial1.readString();
    read = true;
    Serial1.println(d);
  }
  // if (d == "C") {
  // return true;
  // } else {
  //   return false;
  }
  //}
  






  // Vector<char> toets {"w", "W", "s", "S", "a", "A", "d", "D", "f", "e", "q"};
  // Vector<int> nummer;// { 119, 87, 115, 83, 97, 65, 100, 68, 102, 101, 113 };

  // for (int i = 0; i < nummer.size(); ++i) {
  //   if (nummer[i] == data) {
  //     data = toets[i];
  //   }
  // }

  bool Xbee::uitvoer() {

String data = d;
  //Hierin wordt de variabele genaamd data uitgelezen als getal en wanneer dit overeenkomt met de juiste character wordt het bijbehorende commando uitgevoerd. dit wordt gestored in een variabele zodat dit kan worden opgevraagd.
  if (data == "A") {  //Dit is A, let erop dat dit een hoofdletter is en dat is het verschil tussen de band activeren met een snelheid van 150 of 400! de Zumo draait hier hard naar links!
    //motoren.setSpeeds(0, 400);
    // string g = "rechtdoor0;";
    mtr.HardLeft();
    return true;
    // infoMotorR = 400;
  }
  if (data == "a") {  //Dit is a, Dit is een kleine letter en wanneer je deze meegeeft zal de Zumo langzamer draaien. De Zumo draait hier naar links!
    //motoren.setSpeeds(0, 150);
    // infoMotorR = 150;
    mtr.Left();
    return true;
  }
  if (data == "w") {  //Dit is w, let op dit is een kleine letter en de Zumo zal hierdoor langzaam vooruit rijden.
    mtr.straight();
    return true;
    //Serial1.println("bereikt");
    // infoMotorL = 150;
    // infoMotorR = 150;

  }
  if (data == "d") {  //dit is d, hiermee draait de Zumo langzaam naar rechts.
    //motoren.setSpeeds(150, 0);
    // infoMotorL = 150;
    mtr.Right();
    return true;
  }
  if (data == "W") {
    //motoren.setSpeeds(400, 400);  //Dit is W, hiermee rijdt de Zumo hard naar voren!
    // infoMotorL = 400;
    // infoMotorR = 400;
    mtr.HardStraight();
    return true;
  }
  if (data == "D") {
    //motoren.setSpeeds(400, 0);  //Dit is D, hiermee draait de Zumo hard naar rechts!
    // infoMotorL = 400;
    mtr.HardRight();
    return true;
  }
  if (data == "s") {
    //motoren.setSpeeds(-150, -150);  // dit is s en hiermee rijdt de Zumo langzaam achteruit.
    // infoMotorL = -150;
    // infoMotorR = -150;
    mtr.Back();
    return true;
  }
  if (data == "S") {
    //motoren.setSpeeds(-400, -400);  //Dit is S en hiermee rijdt de Zumo snel achteruit!
    // infoMotorL = -400;
    // infoMotorR = -400;
    mtr.HardBack();
    return true;
  }
  if (data == "i") {  // Hiermee wordt de methode printInfo() aangeroepen om informatie op te vragen.
    printInfo();
    return true;
    //data = 0;
  }
  if (data == "f") {  // Wanneer de Zumo niks uitleest op de Zumo zal hij 0,0 meegeven aan de Zumo.
    mtr.stop();
    return true;
    // infoMotorL = 0;
    // infoMotorR = 0;
  }
   if (data == "q") {
     mtr.turnLeft();
     return true;
  //   //motoren.setSpeeds(-150, 150);
   }
   if (data == "e") {
     mtr.turnRight();
     return true;
  //   //motoren.setSpeeds(150, -150);
   }
   if (data == "K") {
    return false;
   }
   if (data == "Z") {
    pro = true;
    mtr.stop();
    checkProx();
   }
}
void Xbee::checkProx() {
  if (pro) {
    proximit.setup();
  }
  while (pro) {
    proximit.ZieObject();

    if (Serial1.read() == "P") {
      pro = false;
    }
  }
}


bool Xbee::xbtest() {
  Serial.println(d);
  if (d == "C") {
    mtr.stop();
    Serial.println(d);
    return true;
  } else {
    return false;
  }
}

int Xbee::printInfo() {
  //Hier moet sensor informatie worden geprint van de motoren en de IR sensoren.
  Serial1.println();
  Serial1.println("De huidige waarden zijn: " + info);
  // Serial.println("En de waarden van de motoren zijn: " + infoMotorL + " " + infoMotorR);
}