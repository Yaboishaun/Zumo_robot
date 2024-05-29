#include "calibrateNoComments.h"
#include <Zumo32U4.h>

class InertialSensor{
  public:
    InertialSensor(){}
    turnSensorReset();
    turnSensorUpdate();
    turnSensorSetup();
    calibrateGyro();
  private:
    const uint turnAngle45;
    const uint turnAngle90;
    const uint turnAngle1;
    uint turnAngle;
    int16_t turnRate;
    int16_t gyroOffset;
    uint16_t gyroLastUpdate;
    uint16_t microSeconds;
    uint16_t deltaTime;
    uint16_t deltaAngle
    int total;
}
