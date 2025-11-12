// level sensor (boolean state) firmware
#include "levelSensor.h"

void initLevelSensor() {
    pinMode(levelSens, INPUT_PULLUP);
}

bool isLiquidDetected() {
  /* since INPUT_PULLUP is used:
   LOW  = liquid detected 
   HIGH = no liquid */
  return digitalRead(LEVEL_SENSOR_PIN) == LOW;
}