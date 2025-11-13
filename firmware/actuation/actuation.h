#ifndef ACTUATION_H
#define ACTUATION_H

#include <Arduino.h>
#include <AFMotor.h>
#include <Servo.h>
#include "config.h"

extern bool perisPumpState;
extern bool horizSubPumpState;
extern bool servoDispensing;
extern bool motor1State;
extern bool motor2State;
extern bool systemRunning;

#define HORIZ_PUMP_SPEED;
#define PERIS_PUMP_SPEED;

#define SERVO_LOCK_ANGLE 0;

enum MotorType {
    MOTOR_1,
    MOTOR_2
};

void initActuators();

void perisPumpOn(int speed);
void perisPumpOff();

void horizSubPumpOn(int speed);
void horizSubPumpOff();

void servoDispense(int angle, unsigned long delayMs);
void servoReset(int angle, unsigned long delayMs);

void motorRun(MotorType motor, int speed);
void motorStop(MotorType motor);

void emergencyShutdown();

#endif
