#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include "Config.h"

void initControls();
bool startPressed();
bool emergencyPressed();

String getSystemState();
String getSystemStatus();

#endif