#include "comm.h"
#include "control.h"

char payloadBuffer[MAX_PAYLOAD_LEN];

void initCommunication() {
    Serial.begin(BAUD_RATE);
}

void sendStatus(float turbidity_in, float turbidity_out, String status, systemPhase phase, unsigned long timestamp) 
{
    String phaseStr = phaseToString(phase);

    Serial.print("{\"turbidity_in\": ");
    Serial.print(turbidity_in, 2);
    Serial.print(", \"turbidity_out\": ");
    Serial.print(turbidity_out, 2);
    Serial.print(", \"status\": \"");
    Serial.print(status);
    Serial.print("\", \"phase\": \"");
    Serial.print(phaseStr);
    Serial.print("\", \"ts\": ");
    Serial.print(timestamp);
    Serial.println("}");
}


void initLEDS() {
    pinMode(operatingLED, OUTPUT);
    pinMode(emergLED, OUTPUT);
    pinMode(treatedLED, OUTPUT);
}

void runLED (int led) {
    digitalWrite(led, HIGH);
}

void stopLED(int led) {
    digitalWrite(led, LOW);
} 
