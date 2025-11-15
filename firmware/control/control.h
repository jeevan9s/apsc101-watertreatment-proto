#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include "config.h"
#include "actuation/actuation.h"

extern bool systemRunning;
extern int lastStartReading;
extern int lastEmergReading;
extern long lastStartDebounce;
extern long lastEmergDebounce;


void initControls();
bool startPressed();
bool emergencyPressed();

String getSystemStatus(float turbidityOut);

enum systemPhase {
    PHASE_IDLE,
    PHASE_DISPENSING,
    PHASE_PRESSING,
    PHASE_MIXING_SLOW,
    PHASE_MIXING_FAST,
    PHASE_TREATED,
};

systemPhase getCurrentPhase(float turbidityOut);
String phaseToString(systemPhase phase);


#endif