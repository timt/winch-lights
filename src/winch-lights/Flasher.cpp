#include "Flasher.h"

Flasher::Flasher(int pin, int maxOnTime) {
    _pin = pin;
    _maxOnTime = maxOnTime;
    _startTime = millis();
    Serial.println(
            "Flasher created for pin " + String(_pin) + " max on time: " + String(_maxOnTime) + "ms" + " start time: " +
            String(_startTime));
}

void Flasher::flash(int resetAfterMillis) {
    //TODO perhaps reverse this logic so check if need to reset the startTime before evaluation of elapsed time
    int elapsed = checkFlasher();
    Serial.println("Flasher for pin: " + String(_pin) + " elapsed: " + String(elapsed) + "ms");
    if (elapsed <= _maxOnTime && !_isOn) {
        Serial.println("Setting pin " + String(_pin) + " HIGH");
        _isOn = true;
        _startTime = millis();
        digitalWrite(_pin, HIGH);
    }
    if (elapsed > resetAfterMillis) {
        _startTime = millis();
    }
}

void Flasher::stop() {
    digitalWrite(_pin, LOW);
    _isOn = false;
    _startTime = millis();
}

String Flasher::toString() {
    return "pin: " + String(_pin) + " max on time: " + String(_maxOnTime) + "ms" + " start time: " + String(_startTime);
}

int Flasher::checkFlasher() {
    int now = millis();
    int elapsed = now - _startTime;
    if (elapsed > _maxOnTime && _isOn) {
        Serial.println("Setting pin " + String(_pin) + " LOW, elapsed: " + String(elapsed) + "ms");
        _isOn = false;
        digitalWrite(_pin, LOW);
    }
    return elapsed;
}