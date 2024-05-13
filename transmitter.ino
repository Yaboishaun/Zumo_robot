#include <Zumo32U4.h>
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32u4ButtonC buttonC;


void setup() {
Serial1.begin(9600);

}

void loop() {

  //Print de string "rechts" op de seriele monitor, Serial1 zorgt ervoor dat dit over de xbee gaat. de leds zijn bedoeld voor bevestiging dat een knop is geactiveert. rood betekent rechts, geel betekent links, en groen betekent voorwaarts bewegen
  while (buttonA.getSingleDebouncedPress()) {
    Serial1.println("rechts");
    ledRed(1);

  }
    //print de string "links" zodat de Zumo naar links draait
  while (buttonB.getSingleDebouncedPress()) {
    Serial1.println("links");
    ledYellow(1);
  }
  //print de string "rechts" zodat de Zumo naar rechts draait.
  while (buttonC.getSingleDebouncedPress()) {
    Serial1.println("voorwaarts");
    ledGreen(1);
  }
  //Wanneer de knop wordt losgelaten worden de leds gereset.
  else {
    ledRed(0);
    ledYellow(0);
    ledGreen(0);

    //Print een witregel, zodat de zumo niet blijft reageren op een knop die al is losgelaten
    Serial1.println(" ");
  }
}
