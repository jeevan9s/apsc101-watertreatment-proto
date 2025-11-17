#include "turbiditySensor.h"
#include "control.h"
#include "comm.h"
#include "actuation.h"
#include "config.h"

systemPhase phase = PHASE_IDLE;
unsigned long phaseStart = 0;

void setup() {
    Serial.begin(BAUD_RATE);

    initControls();
    initTurbidity();
    initActuators();
    initCommunication();
    initLEDS();

    float initialTurbIn = voltageToNTU(readTurbidityVoltage(turbidityInSens));
    float initialTurbOut = voltageToNTU(readTurbidityVoltage(turbidityOutSens));
    sendStatus(initialTurbIn, initialTurbOut, "initialized", PHASE_IDLE, millis());
}

void loop() {
    // unsigned long now = millis();

    // if (!systemRunningFlag()) {
    //     emergencyShutdown();
        
    //     phase = PHASE_IDLE;

    //     sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
    //                voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
    //                "emergency stop",
    //                PHASE_IDLE,
    //                now);
    //     return;
    // }

    // switch (phase) {

    //     case PHASE_IDLE:
    //         if (systemRunningFlag()) {
    //             runLED(treatingLED);
    //             phase = PHASE_DISPENSING;
    //             phaseStart = now;
    //             runActuators(PUMP_PERIS);

    //             sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
    //                        voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
    //                        "coagulant dispensing",
    //                        PHASE_DISPENSING,
    //                        now);
    //         }
    //         break;

    //     case PHASE_DISPENSING:
    //         if (now - phaseStart >= DISPENSE_DURATION_MS) {
    //             runLED(treatingLED);
    //             stopActuators(PUMP_PERIS);
    //             phase = PHASE_MIXING_FAST;
    //             phaseStart = now;
    //             runActuators(MOTOR_MIX_FAST);

    //             sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
    //                        voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
    //                        "fast mixing",
    //                        PHASE_MIXING_FAST,
    //                        now);
    //         }
    //         break;

    //     case PHASE_MIXING_FAST:
    //         if (now - phaseStart >= FAST_MIX_DURATION_MS) {
    //             runLED(treatingLED);
    //             stopActuators(MOTOR_MIX_FAST);
    //             phase = PHASE_MIXING_SLOW;
    //             phaseStart = now;
    //             runActuators(MOTOR_MIX_SLOW);

    //             sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
    //                        voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
    //                        "slow mixing",
    //                        PHASE_MIXING_SLOW,
    //                        now);
    //         }
    //         break;

    //     case PHASE_MIXING_SLOW:
    //         if (now - phaseStart >= SLOW_MIX_DURATION_MS) {
    //             runLED(treatingLED);
    //             stopActuators(MOTOR_MIX_SLOW);
    //             phase = PHASE_PRESSING;
    //             phaseStart = now;
    //             runActuators(MOTOR_PRESS);

    //             sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
    //                        voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
    //                        "filter pressing",
    //                        PHASE_PRESSING,
    //                        now);
    //         }
    //         break;

    //     case PHASE_PRESSING:
    //         if (now - phaseStart >= PRESS_DURATION_MS) {
    //             runLED(treatingLED);
    //             stopActuators(MOTOR_PRESS);
    //             phase = PHASE_TREATED;
    //             runActuators(PUMP_HORIZ);

    //             sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
    //                        voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
    //                        "treated",
    //                        PHASE_TREATED,
    //                        now);
    //         }
    //         break;

    //     case PHASE_TREATED:
    //         runLED(treatedLED);
    //         stopActuators(PUMP_HORIZ);
    //         phase = DONE;

    //         sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
    //                    voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
    //                    "treated",
    //                    DONE,
    //                    now);
    //         break;

    //     case DONE:
    //     default:
    //         break;
    // }

    sendStatus(voltageToNTU(readTurbidityVoltage(turbidityInSens)),
                       voltageToNTU(readTurbidityVoltage(turbidityOutSens)),
                       "treated",
                       PHASE_TREATED,
                       millis());
}

const int LED_ARRAY[] = {operatingLED, emergLED, treatedLED};
void test_PUMP() {
    for (int i = 0; i < 3; i++ ) {
        runLED(LED_ARRAY[i]);
        sendStatus(6, 7, "treating", PHASE_DISPENSING, millis());
        delay(2000);
        stopLED(LED_ARRAY[i]);
    }
}

const ActuatorType PUMP_ARRAY[] = {PUMP_PERIS, PUMP_HORIZ, PUMP_CF};
void test_PUMPS() {
    for (int i = 0; i < 3; i++) {
        runActuators(PUMP_ARRAY[i]);
        sendStatus(6, 7, "treated", PHASE_MIXING_SLOW, millis());
        delay(800);
        stopActuators(PUMP_ARRAY[i]);
    }
}


 
