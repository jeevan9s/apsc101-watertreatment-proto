#ifndef ACTUATION_H
#define ACTUATION_H

#include <Arduino.h>
#include "config.h"

extern bool perisPumpState;
extern bool horizSubPumpState;

#define 

void initActuators();

void perisPumpOn();
void horizSubPumpOff();
void pumpOff();

void motorRun(int speed);
void motorStop();

void emergencyShutdown();


#endif