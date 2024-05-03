#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4OLED display;

// Line sensor en proximity sensor initialisatie
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;

// Array om de waarden van de lijnsensoren op te slaan
uint16_t lineSensorValues[5] = { 0, 0, 0, 0, 0 };

// Variabelen om de activering van de proximity sensors bij te houden
bool proxLeftActive;
bool proxFrontActive;
bool proxRightActive;

void setup()
{
  // Initialisatie van de lijn- en proximity sensors
  lineSensors.initThreeSensors();
  proxSensors.initThreeSensors();

  // Laad aangepaste karakters voor de OLED-display
  loadCustomCharacters();

  // Kalibreer de lijnsensoren
  calibrateLineSensors();
}

// Functie om de lijnsensoren te kalibreren
void calibrateLineSensors()
{
  // Activeer de gele LED en geef "Line cal" weer op de display
  ledYellow(1);
  display.clear();
  display.print(F("Line cal"));

  // Loop om de lijnsensoren te kalibreren
  for (uint16_t i = 0; i < 400; i++)
  {
    display.gotoXY(0, 1);
    display.print(i);
    lineSensors.calibrate();
  }

  // Schakel de gele LED uit en wis het display
  ledYellow(0);
  display.clear();
}

// Functie om aangepaste karakters te laden voor de display
void loadCustomCharacters()
{
  // Definieer de bitpatronen voor de aangepaste karakters
  static const char levels[] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63
  };
  
  // Laad elk aangepast karakter in de display
  display.loadCustomCharacter(levels + 0, 0);
  display.loadCustomCharacter(levels + 1, 1);
  display.loadCustomCharacter(levels + 2, 2);
  display.loadCustomCharacter(levels + 3, 3);
  display.loadCustomCharacter(levels + 4, 4);
  display.loadCustomCharacter(levels + 5, 5);
  display.loadCustomCharacter(levels + 6, 6);
}

// Functie om een balk weer te geven op basis van de hoogte
void printBar(uint8_t height)
{
  if (height > 8) { height = 8; }
  const char barChars[] = {' ', 0, 1, 2, 3, 4, 5, 6, (char)255};
  display.print(barChars[height]);
}

// Functie om de sensorwaarden weer te geven op de display
void printReadingsToDisplay()
{
  // Toon de proximiteitssensorwaarden op de eerste regel van de display
  display.gotoXY(0, 0);
  printBar(proxSensors.countsLeftWithLeftLeds());
  printBar(proxSensors.countsLeftWithRightLeds());
  display.print(' ');
  printBar(proxSensors.countsFrontWithLeftLeds());
  printBar(proxSensors.countsFrontWithRightLeds());
  display.print(' ');
  printBar(proxSensors.countsRightWithLeftLeds());
  printBar(proxSensors.countsRightWithRightLeds());

  // Toon de lijnsensorwaarden op de tweede regel van de display
  display.gotoXY(0, 1);
  for (uint8_t i = 0; i < 5; i++)
  {
    uint8_t barHeight = map(lineSensorValues[i], 0, 1000, 0, 8);
    printBar(barHeight);
  }

  // Toon de basiswaarden van de proximiteitssensoren op de tweede regel van de display
  display.gotoXY(5, 1);
  printBar(proxLeftActive);
  printBar(proxFrontActive);
  printBar(proxRightActive);
}

// Functie om de sensorwaarden naar de seriële monitor te sturen
void printReadingsToSerial()
{
  static char buffer[80];
  sprintf(buffer, "%d %d %d %d %d %d  %d %d %d  %4d %4d %4d %4d %4d\n",
    proxSensors.countsLeftWithLeftLeds(),
    proxSensors.countsLeftWithRightLeds(),
    proxSensors.countsFrontWithLeftLeds(),
    proxSensors.countsFrontWithRightLeds(),
    proxSensors.countsRightWithLeftLeds(),
    proxSensors.countsRightWithRightLeds(),
    proxLeftActive,
    proxFrontActive,
    proxRightActive,
    lineSensorValues[0],
    lineSensorValues[1],
    lineSensorValues[2],
    lineSensorValues[3],
    lineSensorValues[4]
  );
  Serial.print(buffer);
}

void loop()
{
  static uint16_t lastSampleTime = 0;

  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();

    // Lees de proximiteitssensoren
    proxSensors.read();

    // Lees de basiswaarden van de proximiteitssensoren
    proxLeftActive = proxSensors.readBasicLeft();
    proxFrontActive = proxSensors.readBasicFront();
    proxRightActive = proxSensors.readBasicRight();

    // Lees de gekalibreerde waarden van de lijnsensoren
    lineSensors.readCalibrated(lineSensorValues);

    // Toon de sensorwaarden op de display en in de seriële monitor
    printReadingsToDisplay();
    printReadingsToSerial();
  }
}
