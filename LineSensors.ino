#include "LineSensors.h"

// Maak een LineSensors object aan
LineSensors myLineSensors;

void setup() {
    myLineSensors.startup(); // Roep de setup methode van het object aan
    
}

void loop() {
    myLineSensors.checkWaardesLS(); // Roep de loop methode van het object aan
    myLineSensors.startup();
}
