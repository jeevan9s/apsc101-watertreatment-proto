#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include "config.h"
#include "actuation/actuation.h"

bool systemRunning = false;
static int lastStartReading = HIGH;
static int lastEmergReading = HIGH;
static long lastStartDebounce = 0;
static long lastEmergDebounce = 0;

void initControls();
bool startPressed();
bool emergencyPressed();

String getSystemStatus();

enum systemPhase {
    PHASE_IDLE;
    PHASE_UNTREATED;
    PHASE_DISPENSING;
    PHASE_PRESSING;
    PHASE_MIXING_SLOW;
    PHASE_MIXING_FAST;
    PHASE_TREATED;
}

systemPhase getCurrentPhase(float turbidityOut);
String phaseToString(systemPhase phase);


#endif