// turbidititty firmware
#include "turbiditySensor.h"

void initTurbidity() {
    pinMode(turbidityInSens, INPUT);
    pinMode(turbidityOutSens, INPUT);
}

float readTurbidityVoltage(int turbidityPin) {
  int raw = analogRead(turbidityPin);
  float voltage = raw * (5.0f / 1023.0f);
  return voltage;
}

// source: 2T equation from excel/putty data
float voltageToNTU(float v){
    return -1120.4f * v * v - 5742.3f * v - 4352.9f;
}