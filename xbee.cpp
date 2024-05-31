#include "xbee.h"
#include <unistd.h>
#include <iostream>


Xbee::Xbee() {
}
~Xbee::Xbee() {
}
// Hiermee wordt gekeken of er een nieuw commando binnenkomt vanuit de Xbee en wanneer dit zo is wordt deze informatie uitgelezen en in de variabele data gestored.
void Xbee::leesWaarde() {
     if (Serial1.available() > 0) {
    data = Serial1.read();
}
}

void Xbee::converteer() {
    //Hierin wordt de variabele genaamd data uitgelezen als getal en wanneer dit overeenkomt met de juiste character wordt het bijbehorende commando uitgevoerd. dit wordt gestored in een variabele zodat dit kan worden opgevraagd.
     if (data == 65) { //Dit is A, let erop dat dit een hoofdletter is en dat is het verschil tussen de band activeren met een snelheid van 150 of 400! de Zumo draait hier hard naar links!
      motoren.setRightSpeed(400);
      infoMotorR = 400;
    }
    if (data == 97) { //Dit is a, Dit is een kleine letter en wanneer je deze meegeeft zal de Zumo langzamer draaien. De Zumo draait hier naar links!
      motoren.setRightSpeed(150);
      infoMotorR = 150;
    } if (data == 119) { //Dit is w, let op dit is een kleine letter en de Zumo zal hierdoor langzaam vooruit rijden.
      motoren.setSpeeds(150, 150);
      infoMotorL = 150;
      infoMotorR = 150;
    } if (data == 100) {//dit is d, hiermee draait de Zumo langzaam naar rechts.
      motoren.setLeftSpeed(150);
      infoMotorL = 150;
    } if (data == 87) {
      motoren.setSpeeds(400, 400); //Dit is W, hiermee rijdt de Zumo hard naar voren!
      infoMotorL = 400;
      infoMotorR = 400;
    } if (data == 68) {
      motoren.setLeftSpeed(400); //Dit is D, hiermee draait de Zumo hard naar rechts!
      infoMotorL = 400;
    } if (data == 115) {
      motoren.setSpeeds(-150, -150);// dit is s en hiermee rijdt de Zumo langzaam achteruit.
      infoMotorL = -150;
      infoMotorR = -150;
    } if (data == 83) {
      motoren.setSpeeds(-400, -400);//Dit is S en hiermee rijdt de Zumo snel achteruit!
      infoMotorL = -400;
      infoMotorR = -400;
    } if (data == 23) {// Hiermee wordt de methode printInfo() aangeroepen om informatie op te vragen.
      printinfo();
    }
     else {// Wanneer de Zumo niks uitleest op de Zumo zal hij 0,0 meegeven aan de Zumo.
      motoren.setSpeeds(0, 0);
      infoMotorL = 0;
      infoMotorR = 0;
    }

}
void Xbee::printinfo() {
    //Hier moet sensor informatie worden geprint van de motoren en de IR sensoren.
    cout<<"De huidige waarden zijn: "<<info<<endl; /* Ik wil een vector maken van info waarin de sensor waarden worden geprint.*/
    cout<<"De huidige snelheid van de Zumo is:"<<infoMotorL<<" "<<infoMotorR<<endl;
}
