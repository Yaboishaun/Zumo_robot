#include <Zumo32U4.h>
#include <Zumo32U4Buttons.h>
#include <Wire.h>
Zumo32U4Motors motoren;
using namespace std;
void setup() {
Serial1.begin(9600);
Xbee xbee;
}

void loop() {
  xbee.leesWaarde();
  xbee.converteer();
/* Ik probeer deze "main" zo klein mogelijk te houden */

}
