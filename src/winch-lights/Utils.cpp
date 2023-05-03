#include "Utils.h"

void flash(int pin, int &startTime, int maxOnTime, int resetPeriod) {
    int now = millis();
    int elapsed = now - startTime;
    if (elapsed > maxOnTime) {
        digitalWrite(pin, LOW);
    } else {
        digitalWrite(pin, HIGH);
    }
    if (elapsed > resetPeriod) {
        startTime = millis();
    }
}