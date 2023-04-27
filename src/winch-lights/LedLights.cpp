#include "LedLights.h"


LedLights::LedLights(int interval) {
    _interval = interval;
    _rxFlashStartTime = millis();
}

void LedLights::setup() {
    pinMode(rxled, OUTPUT);
    pinMode(stopled, OUTPUT);
    pinMode(powerled, OUTPUT);
    Wire.begin(21, 22);
    if (_axp.begin(Wire, AXP192_SLAVE_ADDRESS) == AXP_FAIL) {
        Serial.println(F("failed to initialize communication with AXP192"));
        while (true) {}
    }
    Serial.println("LedLights setup complete");
}

void LedLights::setLedStateTransmitting() {
    digitalWrite(powerled, HIGH);
}

void LedLights::setLedStateReceiving(String command) {
    digitalWrite(powerled, LOW);
    if (command == STOP) {
        digitalWrite(stopled, HIGH);
        digitalWrite(rxled, HIGH);
    } else if (command == CANCEL_STOP) {
        digitalWrite(rxled, LOW);
    } else if (command == ALL_OUT) {
        rxFlash(1000, 500);
    } else if (command == TAKE_UP_SLACK) {
        rxFlash(2000, 500);
    }
}

void LedLights::rxFlash(int interval, int maxOnTime) {
    int now = millis();
    int elapsed = now - _rxFlashStartTime;
    if (elapsed > maxOnTime) {
        digitalWrite(rxled, LOW);
    } else {
        digitalWrite(rxled, HIGH);
    }
    if (elapsed > interval) {
        _rxFlashStartTime = millis();
    }
}

void LedLights::checkBatteryAndReset() {
    digitalWrite(stopled, LOW);
    if (_axp.getBattVoltage() < 3400) {
        rxFlash(500, 100);
    } else {
        digitalWrite(rxled, LOW);
    }
}