#include <Zumo32U4.h>
#include <Zumo32U4Buttons.h>
#include <Wire.h>
#include "xbee.h"
Xbee xbee;
Zumo32U4ButtonA ButtonA;
using namespace std;
void setup() {
Serial1.begin(9600);
Serial.begin(9600);
}

void loop() {
  xbee.leesWaarde();
  xbee.converteer();
  if (ButtonA.getSingleDebouncedPress()) {
    Serial1.println("testln");
  }
/* Ik probeer deze "main" zo klein mogelijk te houden */

}