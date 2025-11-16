// GENERAL CONFIG FILE 

#ifndef CONFIG_H
#define CONFIG_H

// pinout (0 is a placeholder until we wire)
const int turbidityOutSens = 0; 
const int turbidityInSens = 0;

const int startBtn = 0;
const int emergStopBtn = 0;

const int mixingMotorPin = 0;
const int pressMotorPin = 0;

const int horizSubPumpPin = 0;
const int cfPumpPin = 0;
const int perisDispensePumpPin = 0; // relay


#define TREATED_THRESHOLD 500 // can implement after testing

// timing constants
#define DISPENSE_DURATION_MS 5000
#define SLOW_MIXING_DURATION_MS 10000
#define FAST_MIXING_DURATION_MS 10000

#endif 

