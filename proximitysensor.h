#ifndef PROXIMITYSENSORS_H
#define PROXIMITYSENSORS_H

#include <Wire.h>
#include <Zumo32U4.h>

class ProximitySensors
{
public:
    void setup();
    void loadCustomCharacters();
    void printBar(uint8_t height);
    void printReadingsToDisplay();
    void printReadingsToSerial();
    void loop();

private:
    Zumo32U4OLED display;
    Zumo32U4ProximitySensors proxSensors;

    bool proxLeftActive;
    bool proxFrontActive;
    bool proxRightActive;
};

#endif
