// control firmware (system states, status, emerg/start buttons with flags)
#include "control.h"

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
    if (turbidity)
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
                return "Idle"; 
        case PHASE_DISPENSING:
                return "Coagulant Dispensing";
        case PHASE_MIXING_FAST:
                return "Fast Mixing";
        case PHASE_MIXING_SLOW:
                return "Slow Mixing";
        case PHASE_PRESSING:
                return "Filter Pressing";
        case PHASE_TREATED:
                return "Treated";
        default:
            return "Idle";
    }
}