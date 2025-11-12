#include "comm.h"

char payloadBuffer[MAX_PAYLOAD_LEN];

void sendStatus(float turbidity_in, float turbidity_out, String status, unsigned long timestamp) {
    snprintf(
        payloadBuffer,
        MAX_PAYLOAD_LEN,
        PAYLOAD_FORMAT,
        turbidity_in,
        turbidity_out,
        status.c_str(),
        timestamp
    );
    Serial.println(payloadBuffer);
}

void initCommunication() {
    Serial.begin(BAUD_RATE);
}
