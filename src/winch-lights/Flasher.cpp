#include "Flasher.h"

Flasher::Flasher(int pin, int maxOnTime) {
    _pin = pin;
    _maxOnTime = maxOnTime;
    _startTime = millis();
    Serial.println("Flasher created for pin " + String(_pin) + " max on time: " + String(_maxOnTime) + "ms" + " start time: " + String(_startTime));
}

void Flasher::flash(int resetAfterMillis) {
    int now = millis();
    int elapsed = now - _startTime;
    Serial.println("Flasher for pin: " + String(_pin) + " elapsed: " + String(elapsed) + "ms");
    if (elapsed > _maxOnTime) {
        digitalWrite(_pin, LOW);
    } else {
        Serial.println("Setting pin " + String(_pin) + " HIGH");
        digitalWrite(_pin, HIGH);
    }
    if (elapsed > resetAfterMillis) {
        _startTime = millis();
    }
}

void Flasher::stop() {
    digitalWrite(_pin, LOW);
    _startTime = millis();
}

String Flasher::toString() {
    return "pin: " + String(_pin) + " max on time: " + String(_maxOnTime) + "ms" + " start time: " + String(_startTime);
}