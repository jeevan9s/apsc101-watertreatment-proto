#include "comm.h"
#include "control.h"

char payloadBuffer[MAX_PAYLOAD_LEN];

void initCommunication() {
    Serial.begin(BAUD_RATE);
}

void sendStatus(float turbidity_in, float turbidity_out, String status, systemPhase phase, unsigned long timestamp) {
    String phaseStr = phaseToString(phase);

    snprintf(
        payloadBuffer,
        MAX_PAYLOAD_LEN,
        PAYLOAD_FORMAT,
        turbidity_in,
        turbidity_out,
        status.c_str(),
        phaseStr.c_str(),
        timestamp
    );

    Serial.println(payloadBuffer);
}
