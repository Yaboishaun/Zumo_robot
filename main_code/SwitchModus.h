#include "Xbee.h"


class SwitchModus {
  public:
  SwitchModus();
  ~SwitchModus();
  bool xbeeActive(bool);
  bool ProxyActive(bool);
  bool ZumoRace(bool);

  private:
  bool checkxb;
  bool proxy;
  bool BRace;
  bool test;
  bool activProxy;
  String bruin;
};