#include <Arduino.h>
#include "turbidity/turbidity.h"
#include "control/control.h"
#include "comm/comm.h"
#include "actuation/actuation.h"
#include "config.h"

PHASE_IDLE, PHASE_DISPENSING, PHASE_MIXING_FAST, PHASE_MIXING_SLOW, PHASE_PRESSING, PHASE_TREATED;

PHASE_IDLE phase = PHASE_IDLE;
unsigned long phaseStart = 0;

void setup() {
    initControls();
    initTurbidity();
    initActuators();
    initCommunication();

    float turbIn = voltageToNTU(readTurbidityVoltage(turbidityInSens));
    float turbOut = voltageToNTU(readTurbidityVoltage(turbidityOutSens));

    sendStatus(turbIn, turbOut, "offline", phaseToString(PHASE_IDLE), millis());
}

void loop() {
    unsigned long now = millis();

    float turbIn = voltageToNTU(readTurbidityVoltage(turbidityInSens));
    float turbOut = voltageToNTU(readTurbidityVoltage(turbidityOutSens));

    if (!systemRunningFlag()) {
        emergencyShutdown();
        phase = PHASE_IDLE;
        sendStatus(turbIn, turbOut, "offline", phaseToString(PHASE_IDLE), now);
        return;
    }

    switch (phase) {
        case PHASE_IDLE:
            if (systemRunningFlag()) {
                phase = PHASE_DISPENSING;
                phaseStart = now;
                runActuators(PUMP_PERIS);
                sendStatus(turbIn, turbOut, "treating", phaseToString(phase), now);
            }
            break;

        case PHASE_DISPENSING:
            if (now - phaseStart >= DISPENSE_DURATION_MS) {
                stopActuators(PUMP_PERIS);
                phase = PHASE_MIXING_FAST;
                phaseStart = now;
                runActuators(MOTOR_MIX_FAST);
                sendStatus(turbIn, turbOut, "treating", phaseToString(phase), now);
            }
            break;

        case PHASE_MIXING_FAST:
            if (now - phaseStart >= FAST_MIX_DURATION_MS) {
                stopActuators(MOTOR_MIX_FAST);
                phase = PHASE_MIXING_SLOW;
                phaseStart = now;
                runActuators(MOTOR_MIX_SLOW);
                sendStatus(turbIn, turbOut, "treating", phaseToString(phase), now);
            }
            break;

        case PHASE_MIXING_SLOW:
            if (now - phaseStart >= SLOW_MIX_DURATION_MS) {
                stopActuators(MOTOR_MIX_SLOW);
                phase = PHASE_PRESSING;
                phaseStart = now;
                runActuators(MOTOR_PRESS);
                sendStatus(turbIn, turbOut, "treating", phaseToString(phase), now);
            }
            break;

        case PHASE_PRESSING:
            if (now - phaseStart >= PRESS_DURATION_MS) {
                stopActuators(MOTOR_PRESS);
                phase = PHASE_TREATED;
                runActuators(PUMP_HORIZ);
                sendStatus(turbIn, turbOut, "treating", phaseToString(phase), now);
            }
            break;

        case PHASE_TREATED:
            stopActuators(PUMP_HORIZ);
            phase = PHASE_IDLE;
            sendStatus(turbIn, turbOut, "treated", phaseToString(PHASE_TREATED), now);
            break;

        default:
            break;
    }
}
