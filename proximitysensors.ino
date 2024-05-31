#include "ProximitySensors.h"

ProximitySensors sensors;

void setup()
{
    sensors.setup();
}

void loop()
{
    sensors.loop();
}
