#include "ZumoMotoren.h"

ZumoMotoren zumo;

void setup()
{
    zumo.init();
}

void loop()
{
    zumo.handleSerialInput();
}

