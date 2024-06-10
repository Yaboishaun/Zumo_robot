#include "xbee.h"
#include <Zumo32U4.h>
#include <Zumo32U4Motors.h>
#include <Vector.h>
Zumo32U4Motors motoren;
//Vector<int> nummer;
int nummer[12] = { 119, 87, 115, 83, 97, 65, 100, 68, 102, 101, 113, 105 };
int characters[12] = {"w", "W", "s", "S", "a", "A", "d", "D", "f", "e", "q", "i"};
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
// Hiermee wordt gekeken of er een nieuw commando binnenkomt vanuit de Xbee en wanneer dit zo is wordt deze informatie uitgelezen en in de variabele data gestored.
void Xbee::leesWaarde() {
  if (Serial1.available() > 0) {
    data = Serial1.read();
    read = true;

  }
}

void Xbee::converteer() {
  if (read) {
for (int i = 0; i < 12; ++i) {
  if (nummer[i] == data) {
    data = characters[i];
    read = false;
  }
}
  }








  // Vector<char> toets {"w", "W", "s", "S", "a", "A", "d", "D", "f", "e", "q"};
 // Vector<int> nummer;// { 119, 87, 115, 83, 97, 65, 100, 68, 102, 101, 113 };

  // for (int i = 0; i < nummer.size(); ++i) {
  //   if (nummer[i] == data) {
  //     data = toets[i];
  //   }
  // }
  //Hierin wordt de variabele genaamd data uitgelezen als getal en wanneer dit overeenkomt met de juiste character wordt het bijbehorende commando uitgevoerd. dit wordt gestored in een variabele zodat dit kan worden opgevraagd.
  if (data == "A") {  //Dit is A, let erop dat dit een hoofdletter is en dat is het verschil tussen de band activeren met een snelheid van 150 of 400! de Zumo draait hier hard naar links!
    motoren.setSpeeds(0, 400);
    // infoMotorR = 400;
  }
  if (data == "a") {  //Dit is a, Dit is een kleine letter en wanneer je deze meegeeft zal de Zumo langzamer draaien. De Zumo draait hier naar links!
    motoren.setSpeeds(0, 150);
    // infoMotorR = 150;
  }
  if (data == "w") {  //Dit is w, let op dit is een kleine letter en de Zumo zal hierdoor langzaam vooruit rijden.
    motoren.setSpeeds(150, 150);
    // infoMotorL = 150;
    // infoMotorR = 150;
  }
  if (data == "d") {  //dit is d, hiermee draait de Zumo langzaam naar rechts.
    motoren.setSpeeds(150, 0);
    // infoMotorL = 150;
  }
  if (data == "W") {
    motoren.setSpeeds(400, 400);  //Dit is W, hiermee rijdt de Zumo hard naar voren!
    // infoMotorL = 400;
    // infoMotorR = 400;
  }
  if (data == "D") {
    motoren.setSpeeds(400, 0);  //Dit is D, hiermee draait de Zumo hard naar rechts!
    // infoMotorL = 400;
  }
  if (data == "s") {
    motoren.setSpeeds(-150, -150);  // dit is s en hiermee rijdt de Zumo langzaam achteruit.
    // infoMotorL = -150;
    // infoMotorR = -150;
  }
  if (data == "S") {
    motoren.setSpeeds(-400, -400);  //Dit is S en hiermee rijdt de Zumo snel achteruit!
    // infoMotorL = -400;
    // infoMotorR = -400;
  }
  if (data == "i") {  // Hiermee wordt de methode printInfo() aangeroepen om informatie op te vragen.
    printInfo();
    data = 0;
  }
  if (data == "f") {  // Wanneer de Zumo niks uitleest op de Zumo zal hij 0,0 meegeven aan de Zumo.
    motoren.setSpeeds(0, 0);
    // infoMotorL = 0;
    // infoMotorR = 0;
  }
  if (data == "q") {
    motoren.setSpeeds(-150, 150);
  }
  if (data == "e") {
    motoren.setSpeeds(150, -150);
  }
}




int Xbee::printInfo() {
  //Hier moet sensor informatie worden geprint van de motoren en de IR sensoren.
  Serial1.println();
  Serial1.println("De huidige waarden zijn: " + info);
  // Serial.println("En de waarden van de motoren zijn: " + infoMotorL + " " + infoMotorR);
}