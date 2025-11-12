#ifndef LEVEL_SENSOR_H
#define LEVEL_SENSOR_H

#include <Arduino.h>
#include "config.h"

void initLevelSensor();
bool isLiquidDetected();

#ifndef