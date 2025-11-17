#include "actuation.h"
#include "control.h"

AF_DCMotor pressMotor(pressMotorPin);
AF_DCMotor mixingMotor(mixingMotorPin);
AF_DCMotor horizSubPump(horizSubPumpPin);
AF_DCMotor cfPump(cfPumpPin);

bool perisDispensePumpState = false;
bool horizSubPumpState = false;
bool cfPumpState = false;
bool pressMotorState = false;
bool slowMixingMotorState = false;
bool fastMixingMotorState = false;

void initActuators()
{
    pressMotor.setSpeed(0);
    mixingMotor.setSpeed(0);
    horizSubPump.setSpeed(0);
    cfPump.setSpeed(0);

    pressMotor.run(RELEASE);
    mixingMotor.run(RELEASE);
    horizSubPump.run(RELEASE);
    cfPump.run(RELEASE);
    pinMode(perisDispensePumpPin, OUTPUT);
}

void runActuators(ActuatorType actuator)
{
    switch (actuator)
    {
        case MOTOR_PRESS:
            pressMotor.setSpeed(PRESS_MOTOR_SPEED);
            pressMotor.run(FORWARD);
            pressMotorState = true;
            break;

        case MOTOR_MIX_SLOW:
            mixingMotor.setSpeed(SLOW_MIX_MOTOR_SPEED);
            mixingMotor.run(FORWARD);
            slowMixingMotorState = true;
            fastMixingMotorState = false;
            break;

        case MOTOR_MIX_FAST:
            mixingMotor.setSpeed(FAST_MIX_MOTOR_SPEED);
            mixingMotor.run(FORWARD);
            fastMixingMotorState = true;
            slowMixingMotorState = false;
            break;

        case PUMP_PERIS:
            digitalWrite(perisDispensePumpPin, HIGH);
            delay(1000);
            perisDispensePumpState = true;
            break;

        case PUMP_HORIZ:
            horizSubPump.setSpeed(HORIZ_PUMP_SPEED);
            horizSubPump.run(FORWARD);
            horizSubPumpState = true;
            break;

        case PUMP_CF:
            cfPump.setSpeed(CF_PUMP_SPEED);
            cfPump.run(FORWARD);
            cfPumpState = true;
            break;
    }
}

void stopActuators(ActuatorType actuator)
{
    switch (actuator)
    {
        case MOTOR_PRESS:
            pressMotor.run(RELEASE);
            pressMotorState = false;
            break;

        case MOTOR_MIX_SLOW:
        case MOTOR_MIX_FAST:
            mixingMotor.run(RELEASE);
            slowMixingMotorState = false;
            fastMixingMotorState = false;
            break;

        case PUMP_PERIS:
            digitalWrite(perisDispensePumpPin, LOW);
            perisDispensePumpState = false;
            break;

        case PUMP_HORIZ:
            horizSubPump.run(RELEASE);
            horizSubPumpState = false;
            break;

        case PUMP_CF:
            cfPump.run(RELEASE);
            cfPumpState = false;
            break;
    }
}

void emergencyShutdown()
{
    runLED(emergLED);
    stopActuators(PUMP_CF);
    stopActuators(PUMP_HORIZ);
    stopActuators(MOTOR_MIX_FAST);
    stopActuators(MOTOR_MIX_SLOW);
    stopActuators(MOTOR_PRESS);
    stopActuators(PUMP_PERIS);
    systemRunning = false;
}
