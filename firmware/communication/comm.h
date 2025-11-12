#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>

#define BAUD_RATE 9600
#define MAX_PAYLOAD_LEN 128
extern char payloadBuffer[MAX_PAYLOAD_LEN];

#define PAYLOAD_FORMAT "{\"turbidity_in\":%.2f,\"turbidity_out\":%.2f,\"level\":%s,\"status\":\"%s\",\"ts\":%lu}"

void sendStatus(float turbidity_in, float turbidity_out, boolean level, String status, unsigned long timestamp);



#endif 