// control firmware (system states, status, emerg/start buttons with flags)

#include "control.h"

bool systemRunning = false;

static int lastStartReading = HIGH;
static int lastEmergReading = HIGH;
static long lastStartDebounce = 0;
static long lastEmergDebounce = 0;

void initControls() {
    pinMode(startBtn, INPUT_PULLUP);
    pinMode(emergStopBtn, INPUT_PULLUP);
    systemRunning = false;
}

bool debouncedPressed(int pin, int &lastReading, long &lastDebounce) {
    int reading = digitalRead(pin);
    bool pressed = false;
    if (reading != lastReading) lastDebounce = millis();
    if ((millis() - lastDebounce) > DEBOUNCE_DELAY) {
        if (reading == LOW && lastReading == HIGH) pressed = true;
    }
    lastReading = reading;
    return pressed;
}

bool startPressed() {
    return debouncedPressed(startBtn, lastStartReading, lastStartDebounce);
}

bool emergencyPressed() {
    return debouncedPressed(emergStopBtn, lastEmergReading, lastEmergDebounce);
}

bool systemRunningFlag() {
    if (emergencyPressed()) systemRunning = false;
    else if (startPressed() && !systemRunning) systemRunning = true;
    return systemRunning;
}

String getSystemStatus(float turbidityOut) {
    if (!systemRunning) return "offline";
    if (turbidityOut <= TREATED_THRESHOLD) return "treated";
    return "treating";
}

