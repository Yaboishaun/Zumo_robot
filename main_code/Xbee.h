#ifndef XBEE_H
#define XBEE_H

//#include <unistd.h>
#include <HardwareSerial.h>


using namespace std;

class Xbee {

public:
  Xbee();
  ~Xbee();
  int printInfo();
  void converteer();
  String leesWaarde();
  bool uitvoer();
  bool xbtest();
  bool activeerXbee;
  void check();
  bool pro;
  void checkProx();
private:
  String d;
  int info;
  int infoMotorL;
  int infoMotorR;
  bool read = true;
};

#endif // XBEE_H