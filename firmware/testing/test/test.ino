/*
- main testing file 
- testing 4 node bridge:  static data, and live sensor data. 
*/

#include <Arduino.h>

#define sensorPin A0

unsigned long lastUpdate = 0;
const unsigned long INTERVAL = 1000;

int pumpState = 1; 

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
    String systemStatus = getSystemStatus();
    
    Serial.print("{\"turbidity_in\": ");
    Serial.print(in, 2);
    Serial.print(", \"turbidity_out\": ");
    Serial.print(out, 2);
    Serial.print(", \"status\": \"");
    Serial.print(systemStatus);
    Serial.print("\", \"pump\": ");
    Serial.print(pumpState);
    Serial.println("}");
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

// replace with actual logic 
String getSystemStatus() 
{
    float turbidityIn = readSensor();
    int currentPumpState = pumpState;
    
    pumpState = currentPumpState;
    
    if (turbidityIn < 0.1) {
        return "offline";  
    }
    else if (turbidityIn > 5.0) {
        return "alert";    
    }
    else if (currentPumpState == 1) {
        return "treating"; 
    }
    else if (turbidityIn <= 2.0) {
        return "treated";   
    }
    else {
        return "monitoring"; 
    }
}

void sendLiveData() 
{
    float in = readSensor();
    float out = 0.20;
    String systemStatus = getSystemStatus();
    
    Serial.print("{\"turbidity_in\": ");
    Serial.print(in, 2);
    Serial.print(", \"turbidity_out\": ");
    Serial.print(out, 2);
    Serial.print(", \"status\": \"");
    Serial.print(systemStatus);
    Serial.print("\", \"pump\": ");
    Serial.print(pumpState);
    Serial.println("}");
}
