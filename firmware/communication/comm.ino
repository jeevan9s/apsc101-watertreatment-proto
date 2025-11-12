#include "comm.h"

char payloadBuffer[MAX_PAYLOAD_LEN];

void sendStatus(float turbidity_in, float turbidity_out, boolean level, String status, unsigned long timestamp) {
    snprintf(
        payloadBuffer,
        MAX_PAYLOAD_LEN,
        PAYLOAD_FORMAT,
        turbidity_in,
        turbidity_out,
        level ? "true" : "false",
        status.c_str(),
        timestamp
    );
    Serial.println(payloadBuffer);
}

void initCommunication() {
    Serial.begin(BAUD_RATE);
}
