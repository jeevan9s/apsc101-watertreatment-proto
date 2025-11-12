#ifndef TURBIDITY_H
#define TURBIDITY_H

#include <Arduino.h>
#include "config.h"

void initTurbidity();
float readTurbidityVoltage(int turbiditySens);
float voltageToNTU(float v);

#endif