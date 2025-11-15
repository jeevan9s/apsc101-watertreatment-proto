#ifndef COMM_H
#define COMM_H

#include <Arduino.h>
#include "control/control.h"

#define BAUD_RATE 9600
#define MAX_PAYLOAD_LEN 256

#define PAYLOAD_FORMAT "{\"turbidity_in\":%.2f,\"turbidity_out\":%.2f,\"status\":\"%s\",\"phase\":\"%s\",\"ts\":%lu}"

void sendStatus(float turbidity_in, float turbidity_out, String status, systemPhase phase, unsigned long timestamp);


#endif 