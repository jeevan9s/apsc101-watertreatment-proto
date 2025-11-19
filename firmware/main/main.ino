#include "turbiditySensor.h"
#include "control.h"
#include "comm.h"
#include "actuation.h"
#include "config.h"

#include "turbiditySensor.h"
#include "control.h"
#include "comm.h"
#include "actuation.h"
#include "config.h"

systemPhase phase = PHASE_DEFAULT;
unsigned long phaseStart = 0;

void setup() {
    initControls();
    initTurbidity();
    initActuators();
    initCommunication();
    initLEDS();

    phase = PHASE_DEFAULT;
    phaseStart = 0;

    float initialTurbIn = voltageToNTU(readTurbidityVoltage(turbidityInSens));
    float initialTurbOut = voltageToNTU(readTurbidityVoltage(turbidityOutSens));
    sendStatus(initialTurbIn, initialTurbOut, "offline", PHASE_DEFAULT, millis());
}

void loop() {
    unsigned long now = millis();

    static bool lastEmergencyState = false;
    bool emergencyState = emergencyPressed();

    if (emergencyState && !lastEmergencyState) {
        stopLED(treatingLED);
        stopLED(treatedLED);
        emergencyShutdown();
        phase = PHASE_EMERGENCY;

        sendStatus(
            voltageToNTU(readTurbidityVoltage(turbidityInSens)),
            voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
            "emergency",
            PHASE_EMERGENCY,
            now
        );

        lastEmergencyState = emergencyState;
    }

    lastEmergencyState = emergencyState;

    switch (phase) {

        case PHASE_EMERGENCY:
            blinkLED(emergLED);
            if (startPressed()) {
                stopLED(emergLED);
                phase = PHASE_DEFAULT;
                phaseStart = now;
            }
            break;

        case PHASE_DEFAULT:
            stopActuators(PUMP_PERIS);
            stopActuators(MOTOR_MIX_FAST);
            stopActuators(MOTOR_MIX_SLOW);
            stopActuators(MOTOR_PRESS);
            stopActuators(PUMP_HORIZ);
            stopActuators(PUMP_CF);

            stopLED(treatingLED);
            stopLED(treatedLED);
            stopLED(emergLED);

            if (startPressed()) {
                phase = PHASE_IDLE;
                phaseStart = now;
                blinkLED(treatingLED);
            }
            break;

        case PHASE_IDLE:
            stopLED(treatingLED);
            stopLED(treatedLED);

            phase = PHASE_PRE_CF;
            phaseStart = now;
            blinkLED(treatingLED);

            runActuators(PUMP_CF);

            sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                       voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                       "online",
                       PHASE_PRE_CF,
                       now);
            break;

        case PHASE_PRE_CF:
            runLED(treatingLED);

            if (now - phaseStart >= CF_PUMP_DURATION_MS) {
                stopActuators(PUMP_CF);
                phase = PHASE_DISPENSING;
                phaseStart = now;
                blinkLED(treatingLED);

                runActuators(PUMP_PERIS);

                sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                           voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                           "treating",
                           PHASE_DISPENSING,
                           now);
            }
            break;

        case PHASE_DISPENSING:
            runLED(treatingLED);

            if (now - phaseStart >= DISPENSE_DURATION_MS) {
                stopActuators(PUMP_PERIS);
                phase = PHASE_MIXING_SLOW;
                phaseStart = now;
                blinkLED(treatingLED);

                runActuators(MOTOR_MIX_SLOW);

                sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                           voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                           "treating",
                           PHASE_MIXING_SLOW,
                           now);
            }
            break;
        
        case PHASE_MIXING_SLOW:
            runLED(treatingLED);

            if (now - phaseStart >= SLOW_MIX_DURATION_MS) {
                stopActuators(MOTOR_MIX_SLOW);
                phase = PHASE_MIXING_FAST;
                phaseStart = now;
                blinkLED(treatingLED);

                runActuators(MOTOR_MIX_FAST);

                sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                           voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                           "treating",
                           PHASE_MIXING_FAST,
                           now);
            }
            break;

        case PHASE_MIXING_FAST:
            blinkLED(treatingLED);

            if (now - phaseStart >= FAST_MIX_DURATION_MS) {
                stopActuators(MOTOR_MIX_FAST);
                phase = PHASE_PRESSING;
                phaseStart = now;
                blinkLED(treatingLED);

                runActuators(MOTOR_PRESS);

                sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                           voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                           "treating",
                           PHASE_PRESSING,
                           now);
            }
            break;

        case PHASE_PRESSING:
            runLED(treatingLED);

            if (now - phaseStart >= PRESS_DURATION_MS) {
                stopActuators(MOTOR_PRESS);
                phase = PHASE_POST_PRESS;
                phaseStart = now;
                blinkLED(treatingLED);

                runActuators(PUMP_HORIZ);

                sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                           voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                           "treating",
                           PHASE_POST_PRESS,
                           now);
            }
            break;

        case PHASE_POST_PRESS:
            blinkLED(treatingLED);
            runLED(treatedLED);

            if (now - phaseStart >= HORIZ_PUMP_DURATION_MS) {
                stopActuators(PUMP_HORIZ);
                phase = PHASE_TREATED;
                phaseStart = now;
                blinkLED(treatingLED);

                sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                           voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                           "treated",
                           PHASE_TREATED,
                           now);
            }
            break;

        case PHASE_TREATED: {
            unsigned long elapsed = millis() - phaseStart;

            if (elapsed < 3 * 600) {
                if ((elapsed / 300) % 2 == 0) {
                    digitalWrite(treatedLED, HIGH);
                } else {
                    digitalWrite(treatedLED, LOW);
                }
            } else {
                digitalWrite(treatedLED, HIGH);
            }
            break;
        }

        default:
            break;
    }
}

// const int LED_ARRAY[] = {treatingLED, emergLED, treatedLED};
// void test_PUMP() {
//     for (int i = 0; i < 3; i++ ) {
//         runLED(LED_ARRAY[i]);
//         sendStatus(6, 7, "treating", PHASE_DISPENSING, millis());
//         delay(2000);
//         stopLED(LED_ARRAY[i]);
//     }
// }

// const ActuatorType PUMP_ARRAY[] = {PUMP_PERIS, PUMP_HORIZ, PUMP_CF};
// void test_PUMPS() {
//     for (int i = 0; i < 3; i++) {
//         runActuators(PUMP_ARRAY[i]);
//         sendStatus(6, 7, "treated", PHASE_MIXING_SLOW, millis());
//         delay(800);
//         stopActuators(PUMP_ARRAY[i]);
//     }
// }