#include <Arduino.h>
#include "turbidity/turbidity.h"
#include "control/control.h"
#include "comm/comm.h"
#include "actuation/actuation.h"
#include "config.h"

// MAIN CONTROL LOOP!

enum Phase {IDLE, DISPENSE, FAST_MIX, SLOW_MIX, PRESSING, TREATED_WATER, DONE};
Phase phase = IDLE;
unsigned long phaseStart = 0;

void setup() {
    Serial.begin(BAUD_RATE);
    initControls();
    initTurbidity();
    initActuators();
    initCommunication();
    float initialTurbIn = voltageToNTU(readTurbidityVoltage(turbidityInSens));
    float initialTurbOut = voltageToNTU(readTurbidityVoltage(turbidityOutSens));
    sendStatus(initialTurbIn, initialTurbOut, "initialized", PHASE_IDLE, millis());
}

void loop() {
    unsigned long now = millis();

    if (!systemRunningFlag()) {
        emergencyShutdown();
        phase = IDLE;
        sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                   voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                   "emergency_stop",
                   PHASE_IDLE,
                   now);
        return;
    }

    switch (phase) {
        case IDLE:
            if (systemRunningFlag()) {
                phase = DISPENSE;
                phaseStart = now;
                runActuators(PUMP_PERIS);
                sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                           voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                           "dispensing",
                           PHASE_DISPENSE,
                           now);
            }
            break;

        case DISPENSE:
            if (now - phaseStart >= DISPENSE_DURATION_MS) {
                stopActuators(PUMP_PERIS);
                phase = FAST_MIX;
                phaseStart = now;
                runActuators(MOTOR_MIX_FAST);
                sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                           voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                           "fast_mixing",
                           PHASE_FAST_MIX,
                           now);
            }
            break;

        case FAST_MIX:
            if (now - phaseStart >= FAST_MIX_DURATION_MS) {
                stopActuators(MOTOR_MIX_FAST);
                phase = SLOW_MIX;
                phaseStart = now;
                runActuators(MOTOR_MIX_SLOW);
                sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                           voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                           "slow_mixing",
                           PHASE_SLOW_MIX,
                           now);
            }
            break;

        case SLOW_MIX:
            if (now - phaseStart >= SLOW_MIX_DURATION_MS) {
                stopActuators(MOTOR_MIX_SLOW);
                phase = PRESSING;
                phaseStart = now;
                runActuators(MOTOR_PRESS);
                sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                           voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                           "pressing",
                           PHASE_PRESSING,
                           now);
            }
            break;

        case PRESSING:
            if (now - phaseStart >= PRESS_DURATION_MS) {
                stopActuators(MOTOR_PRESS);
                phase = TREATED_WATER;
                runActuators(PUMP_HORIZ);
                sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                           voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                           "moving_to_clean_tank",
                           PHASE_TREATED_WATER,
                           now);
            }
            break;

        case TREATED_WATER:
            stopActuators(PUMP_HORIZ);
            phase = DONE;
            sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                       voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                       "done",
                       PHASE_DONE,
                       now);
            break;

        case DONE:
        default:
            break;
    }
}
