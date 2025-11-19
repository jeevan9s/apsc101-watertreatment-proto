#ifndef CONTROL_H
#define CONTROL_H

#include "config.h"
#include "actuation.h"

extern bool systemRunning;
extern int lastStartReading;
extern int lastEmergReading;
extern long lastStartDebounce;
extern long lastEmergDebounce;

#define DEBOUNCE_DELAY 200


void initControls();
bool startPressed();
bool emergencyPressed();

String getSystemStatus(float turbidityOut);

bool systemRunningFlag();

enum systemPhase {
    PHASE_DEFAULT,
    PHASE_PRE_CF,
    PHASE_IDLE,
    PHASE_DISPENSING,
    PHASE_PRESSING,
    PHASE_MIXING_SLOW,
    PHASE_MIXING_FAST,
    PHASE_POST_PRESS,
    PHASE_TREATED,
    PHASE_EMERGENCY,
    DONE
};


systemPhase getCurrentPhase(float turbidityOut);
String phaseToString(systemPhase phase);


#endif