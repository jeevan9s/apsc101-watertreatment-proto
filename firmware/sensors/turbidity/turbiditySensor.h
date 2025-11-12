#ifndef TURBIDITY_H
#define TURBIDITY_H

#include <Arduino.h>
#include "config.h"


float readTurbidityVoltage(int turbiditySens);
float voltageToNTU(float voltage);
void initTurbidity();

#endif