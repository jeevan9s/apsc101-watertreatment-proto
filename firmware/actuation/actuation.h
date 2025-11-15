#ifndef ACTUATION_H
#define ACTUATION_H

#include <Arduino.h>
#include <AFMotor.h>
#include "config.h"
#include "control/control.h"

extern bool horizSubPumpState;
extern bool perisDispensePumpState;
extern bool slowMixingMotorState;
extern bool fastMixingMotorState;
extern bool pressMotorState;
extern bool cfPumpState;

#define HORIZ_PUMP_SPEED 100 // change after testing
#define PERIS_DISPENSE_PUMP_SPEED 100 // change after testing (applies 2 all speed constants)
#define CF_PUMP_SPEED 100

#define SLOW_MIX_MOTOR_SPEED 50
#define FAST_MIX_MOTOR_SPEED 150

#define PRESS_MOTOR_SPEED 100

typedef enum {
    MOTOR_PRESS,
    MOTOR_MIX_SLOW,
    MOTOR_MIX_FAST,
    PUMP_PERIS,
    PUMP_HORIZ,
    PUMP_CF
} ActuatorType;


void initActuators();

void runActuators(ActuatorType actuator);
void stopActuators(ActuatorType actuator);

void emergencyShutdown();

#endif
