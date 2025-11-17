#ifndef TURBIDITYSENSOR_H
#define TURBIDITYSENSOR_H
#include "config.h"

void initTurbidity();
float readTurbidityVoltage(int turbiditySens);
float voltageToNTU(float v);

#endif