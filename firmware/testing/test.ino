/*
- main testing file 
- testing 4 node bridge:  static data, and live sensor data. 
*/

#include <Arduino.h>

#define sensorPin A0

unsigned long lastUpdate = 0;
const unsigned long INTERVAL = 1000;

int pumpState = 0; 

void setup() 
{
    Serial.begin(9600);
    pinMode(sensorPin, INPUT);
}

void loop() 
{
    unsigned long currentTime = millis();
    if (currentTime - lastUpdate >= INTERVAL) {
        sendStaticData();
        lastUpdate = currentTime;
    }
}

/* this and sendLiveData MUST be consistent w node handler payload regex/format */
void sendStaticData() 
{
    float in = 2.67;
    float out = 1.41;
    Serial.print("{\"turbidity\": {\"in\": ");
    Serial.print(in, 2);
    Serial.print(", \"out\": ");
    Serial.print(out, 2);
    Serial.print("}, \"system\": {\"status\": \"operating\", \"pump\": ");
    Serial.print(pumpState);
    Serial.println("}}");
}

float readSensor()
{
    // taken from provided hardware tests
    int sensorVal = analogRead(sensorPin);
    float voltage = sensorVal * (5.0 / 1024.0);
    return voltage;
}

float calculateTurbidty() 
{
    //TODO - calibr. curve speficic (check T1 excel sheets/report)
}

bool fetchPumpState() 
{
    //TODO - simple helper to check if pump is on/off -> should return pump name running and its status 
           // could use a pin -> pumpname dictionary
           // return boolean true or false (pumping, inactive)
}

// a "get system status" helper function could be useful

void sendLiveData() 
{
    float in = readSensor();
    float out = 0.20;
    Serial .print("{\"turbidity\": {\"in\": ");
    Serial.print(in, 2);
    Serial.print(", \"out\": ");
    Serial.print(out, 2);
    Serial.print("}, \"system\": {\"status\": \"operating\", \"pump\": ");
    Serial.print(pumpState);
    Serial.println("}}");
}
