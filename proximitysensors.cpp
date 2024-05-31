#include "ProximitySensors.h"

void ProximitySensors::setup()
{
    proxSensors.initThreeSensors();
    loadCustomCharacters();
}

void ProximitySensors::loadCustomCharacters()
{
    static const char levels[] PROGMEM = {
        0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63
    };
    display.loadCustomCharacter(levels + 0, 0);
    display.loadCustomCharacter(levels + 1, 1);
    display.loadCustomCharacter(levels + 2, 2);
    display.loadCustomCharacter(levels + 3, 3);
    display.loadCustomCharacter(levels + 4, 4);
    display.loadCustomCharacter(levels + 5, 5);
    display.loadCustomCharacter(levels + 6, 6);
}

void ProximitySensors::printBar(uint8_t height)
{
    if (height > 8) { height = 8; }
    const char barChars[] = {' ', 0, 1, 2, 3, 4, 5, 6, (char)255};
    display.print(barChars[height]);
}

void ProximitySensors::printReadingsToDisplay()
{
    display.gotoXY(0, 0);
    printBar(proxSensors.countsLeftWithLeftLeds());
    printBar(proxSensors.countsLeftWithRightLeds());
    display.print(' ');
    printBar(proxSensors.countsFrontWithLeftLeds());
    printBar(proxSensors.countsFrontWithRightLeds());
    display.print(' ');
    printBar(proxSensors.countsRightWithLeftLeds());
    printBar(proxSensors.countsRightWithRightLeds());

    display.gotoXY(5, 1);
    printBar(proxLeftActive);
    printBar(proxFrontActive);
    printBar(proxRightActive);
}

void ProximitySensors::printReadingsToSerial()
{
    static char buffer[80];
    sprintf(buffer, "%d %d %d %d %d %d  %d %d %d\n",
        proxSensors.countsLeftWithLeftLeds(),
        proxSensors.countsLeftWithRightLeds(),
        proxSensors.countsFrontWithLeftLeds(),
        proxSensors.countsFrontWithRightLeds(),
        proxSensors.countsRightWithLeftLeds(),
        proxSensors.countsRightWithRightLeds(),
        proxLeftActive,
        proxFrontActive,
        proxRightActive
    );
    Serial.print(buffer);
}

void ProximitySensors::loop()
{
    static uint16_t lastSampleTime = 0;

    if ((uint16_t)(millis() - lastSampleTime) >= 100)
    {
        lastSampleTime = millis();

        proxSensors.read();
        proxLeftActive = proxSensors.readBasicLeft();
        proxFrontActive = proxSensors.readBasicFront();
        proxRightActive = proxSensors.readBasicRight();

        printReadingsToDisplay();
        printReadingsToSerial();
    }
}
