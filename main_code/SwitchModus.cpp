#include "SwitchModus.h"
#include "ProxySensor.h"
#include "Xbee.h"
#include "LineSensors.h"
Xbee xbee;
ProxySensor proximity;
LineSensors ls;
SwitchModus::SwitchModus() : checkxb(false), proxy(false), BRace(false) {
}
SwitchModus::~SwitchModus() {
}

bool SwitchModus::xbeeActive(bool xb) {
  checkxb = xb;
  if (checkxb) {
    xbee.converteer();
    test = xbee.xbtest();
    if (test) {
      BRace = false;
      proxy = false;
    }
    while (test) {
    xbee.converteer();
    xbee.uitvoer();
    test = xbee.uitvoer();
  }
  return test;
}
}
bool SwitchModus::ProxyActive(bool prox) {
  proxy = prox;
  if (proxy) {
  
      activProxy = true;
      while (activProxy) {
      activProxy = xbeeActive(true);
      if (BRace) {
        proximity.setup();
      }
      BRace = false;
    proximity.ZieObject();
    
  }
}

}
bool SwitchModus::ZumoRace(bool Race) {
  BRace = Race;
  return BRace;
}
