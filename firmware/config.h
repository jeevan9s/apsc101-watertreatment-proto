// GENERAL CONFIG FILE 

#ifndef CONFIG_H
#define CONFIG_H

// pinout (0 is a placeholder until we wire)
const int turbidityOutSens = 0; 
const int turbidityInSens = 0;
const int levelSens = 0;

const int startBtn = 0;
const int emergStopBtn = 0;

const int motor1 = 0;
const int motor2 = 0;
const int servoMotor = 0;

const int horizSubPump = 0;
const int perisPump = 0;

extern bool systemRunning;

#define TREATED_THRESHOLD // can implement after testing

#endif 

