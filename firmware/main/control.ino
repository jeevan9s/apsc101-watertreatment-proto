#include "control.h"

bool systemRunning = true;
static bool lastStartState = false;

void initControls() {
    pinMode(startBtn, INPUT_PULLUP);
    pinMode(emergStopBtn, INPUT_PULLUP);
}

bool startPressed() {
    return digitalRead(startBtn) == LOW;
}

bool emergencyPressed() {
    return digitalRead(emergStopBtn) == LOW;
}

bool systemRunningFlag() {
    bool startState = startPressed();

    if (emergencyPressed()) {
        systemRunning = false;
    } else if (startState && !lastStartState) {
        systemRunning = true;
    }

    lastStartState = startState;
    return systemRunning;
}

String getSystemStatus(float turbidityOut) {
    if (!systemRunning) return "offline";
    if (turbidityOut <= TREATED_THRESHOLD) return "treated";
    return "treating";
}

systemPhase getCurrentPhase(float turbidityOut) {
    if (!systemRunning) return PHASE_IDLE;
    if (perisDispensePumpState) return PHASE_DISPENSING;
    if (fastMixingMotorState && !slowMixingMotorState) return PHASE_MIXING_FAST;
    if (slowMixingMotorState && !fastMixingMotorState) return PHASE_MIXING_SLOW;
    if (pressMotorState) return PHASE_PRESSING;
    if (getSystemStatus(turbidityOut) == "treated") return PHASE_TREATED;
    return PHASE_IDLE;
}

String phaseToString(systemPhase phase) {
    switch (phase) {
        case PHASE_DEFAULT: return "default";
        case PHASE_IDLE: return "idle"; 
        case PHASE_PRE_CF: return "contaminated water dispensing";
        case PHASE_DISPENSING: return "coagulant dispensing";
        case PHASE_MIXING_FAST: return "fast mixing";
        case PHASE_MIXING_SLOW: return "slow mixing";
        case PHASE_PRESSING: return "filter pressing";
        case PHASE_TREATED: return "treated";
        case PHASE_POST_PRESS: return "transporting treated water";
        case PHASE_EMERGENCY: return "emergency";
        default: return "idle";
    }
}
