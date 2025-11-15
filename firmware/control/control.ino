// control firmware (system states, status, emerg/start buttons with flags)
#include "control.h"

bool systemRunning = false;
static int lastStartReading = HIGH;
static int lastEmergReading = HIGH;
static long lastStartDebounce = 0;
static long lastEmergDebounce = 0;

void initControls() {
    pinMode(startBtn, INPUT_PULLUP);
    pinMode(emergStopBtn, INPUT_PULLUP);
    systemRunning = false;
}

bool debouncedPressed(int pin, int &lastReading, long &lastDebounce) {
    int reading = digitalRead(pin);
    bool pressed = false;
    if (reading != lastReading) lastDebounce = millis();
    if ((millis() - lastDebounce) > DEBOUNCE_DELAY) {
        if (reading == LOW && lastReading == HIGH) pressed = true;
    }
    lastReading = reading;
    return pressed;
}

bool startPressed() {
    return debouncedPressed(startBtn, lastStartReading, lastStartDebounce);
}

bool emergencyPressed() {
    return debouncedPressed(emergStopBtn, lastEmergReading, lastEmergDebounce);
}

bool systemRunningFlag() {
    if (emergencyPressed()) systemRunning = false;
    else if (startPressed() && !systemRunning) systemRunning = true;
    return systemRunning;
}

String getSystemStatus(float turbidityOut) {
    if (!systemRunning) return "offline";
    if (turbidityOut <= TREATED_THRESHOLD) return "treated";
    return "treating";
}

systemPhase getCurrentPhase(float turbidityOut) {
    if (perisDispensePumpState) return PHASE_DISPENSING;
    if (fastMixingMotorState && !slowMixingMotorState) return PHASE_MIXING_FAST;
    if (slowMixingMotorState && !fastMixingMotorState) return PHASE_MIXING_SLOW;
    if (pressMotorState) return PHASE_PRESSING;
    if (getSystemStatus(turbidityOut) == "treated") return PHASE_TREATED;
    if (!systemRunning) return PHASE_IDLE;
    return PHASE_IDLE;
}

String phaseToString(systemPhase phase) {
    switch (phase) {
        case PHASE_IDLE:
                return "idle"; 
        case PHASE_DISPENSING:
                return "coagulant dispensing";
        case PHASE_MIXING_FAST:
                return "fast mixing";
        case PHASE_MIXING_SLOW:
                return "slow mixing";
        case PHASE_PRESSING:
                return "filter pressing";
        case PHASE_TREATED:
                return "treated";
        default:
            return "idle";
    }
}