// #include "Xbee.h"
// #include "Motors.h"
// #include "ChooseCase.h"
// #include "ProxySensor.h"

// ChooseCase::ChooseCase(Xbee*& xbee)
//   : xbee(xbee), XbeeActief(0) {
// }
// ChooseCase::~ChooseCase() {
// }
// bool ChooseCase::CheckModus() {
//   if (xbee->leesWaarde() == "C") {
//     XbeeActief = true;
//     xbee->ActiveerXbee = true;
//   }
// }
// void ChooseCase::BepaalModus(bool status) {
//   XbeeActief = status;
// }
// bool ChooseCase::ModusActief() {
//   return XbeeActief;
// }
