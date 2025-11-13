#include "actuation.h"
#include "control.h"

AF_DCMotor motor1(MOTOR1_PORT);
AF_DCMotor motor2(MOTOR2_PORT);
AF_DCMotor perisPump(PERIS_PUMP_PORT);
AF_DCMotor horizSubPump(HORIZ_PUMP_PORT);

Servo alumServo;

bool perisPumpState = false;
bool horizSubPumpState = false;
bool servoDispensing = false;
bool motor1State = false;
bool motor2State = false;
bool systemRunning = false;

void initActuators()
{
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    perisPump.setSpeed(0);
    horizSubPump.setSpeed(0);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    perisPump.run(RELEASE);
    horizSubPump.run(RELEASE);
    alumServo.attach(SERVO_PIN);
    alumServo.write(SERVO_LOCK_ANGLE);
}

void perisPumpOn(int speed = PERIS_PUMP_PORT)
{
    perisPump.setSpeed(speed);
    perisPump.run(FORWARD);
    perisPumpState = true;
}

void perisPumpOff()
{
    perisPump.run(RELEASE);
    perisPumpState = false;
}

void horizSubPumpOn(int speed = HORIZ_PUMP_SPEED)
{
    horizSubPump.setSpeed(speed);
    horizSubPump.run(FORWARD);
    horizSubPumpState = true;
}

void horizSubPumpOff()
{
    horizSubPump.run(RELEASE);
    horizSubPumpState = false;
}

void motorRun(MotorType motor, int speed)
{
    switch (motor)
    {
    case MOTOR_1:
        motor1.setSpeed(speed);
        motor1.run(FORWARD);
        motor1State = true;
        break;
    case MOTOR_2:
        motor2.setSpeed(speed);
        motor2.run(FORWARD);
        motor2State = true;
        break;
    }
}

void motorStop(MotorType motor)
{
    switch (motor)
    {
    case MOTOR_1:
        motor1.run(RELEASE);
        motor1State = false;
        break;
    case MOTOR_2:
        motor2.run(RELEASE);
        motor2State = false;
        break;
    }
}

void servoDispense(int startAngle, int endAngle, unsigned long delayMs)
{
    for (int angle = startAngle; angle <= endAngle; angle++) {
        alumServo.write(angle);
        delay(delayMs);
    }
    servoDispensing = true;
}

void servoReset(int currAngle, unsigned long delayMs)
{startAngle
    for (int angle = currAngle; angle >= SERVO_LOCK_ANGLE; angle--) {
        alumServo.write(angle);
        delay(delayMs);
    }
    servoDispensing = false;
}

void emergencyShutdown()
{
    perisPumpOff();
    horizSubPumpOff();
    motorStop(MOTOR_1);
    motorStop(MOTOR_2);
    servoReset(SERVO_LOCK_ANGLE, 0);
}
