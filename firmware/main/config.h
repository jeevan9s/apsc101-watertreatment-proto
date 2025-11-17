// GENERAL CONFIG FILE 

#ifndef CONFIG_H
#define CONFIG_H

// pinout (0 is a placeholder until we wire)
const int turbidityOutSens = 47; 
const int turbidityInSens = 46;

const int startBtn = 53;
const int emergStopBtn = 52;

const int operatingLED = 51;
const int emergLED = 50;
const int treatedLED = 48;

const int mixingMotorPin = 1;
const int pressMotorPin = 2;

const int horizSubPumpPin = 3;
const int cfPumpPin = 4;
const int perisDispensePumpPin = 49; // relay


#define TREATED_THRESHOLD 500 // can implement after testing

// timing constants
#define DISPENSE_DURATION_MS 5000
#define PRESS_DURATION_MS 2000
#define SLOW_MIX_DURATION_MS 10000
#define FAST_MIX_DURATION_MS 10000

#endif 

