#include "LaunchPointLeds.h"


LaunchPointLeds::LaunchPointLeds(int interval) {
    _interval = interval;
    _rxFlashStartTime = millis();
}

void LaunchPointLeds::setup() {
    pinMode(rxLed, OUTPUT);
    pinMode(stopLed, OUTPUT);
    pinMode(powerLed, OUTPUT);
    Wire.begin(21, 22);
    if (_axp.begin(Wire, AXP192_SLAVE_ADDRESS) == AXP_FAIL) {
        Serial.println(F("failed to initialize communication with AXP192"));
        while (true) {}
    }
    Serial.println("LED lights setup complete");
}

void LaunchPointLeds::setLedStateTransmitting() {
    digitalWrite(powerLed, HIGH);
}

void LaunchPointLeds::setLedStateReceiving(String command) {
    Serial.println("Setting LED state receiving for command: " + command);
    digitalWrite(powerLed, LOW);
    if (command == STOP) {
        digitalWrite(stopLed, HIGH);
        digitalWrite(rxLed, HIGH);
    } else if (command == CANCEL_STOP) {
        digitalWrite(rxLed, LOW);
    } else if (command == ALL_OUT) {
        rxFlash(1000, 500);
    } else if (command == TAKE_UP_SLACK) {
        rxFlash(2000, 500);
    }
}

void LaunchPointLeds::rxFlash(int interval, int maxOnTime) {
    int now = millis();
    int elapsed = now - _rxFlashStartTime;
    if (elapsed > maxOnTime) {
        digitalWrite(rxLed, LOW);
    } else {
        digitalWrite(rxLed, HIGH);
    }
    if (elapsed > interval) {
        _rxFlashStartTime = millis();
    }
}

void LaunchPointLeds::checkBatteryAndReset() {
    digitalWrite(stopLed, LOW);
    if (_axp.getBattVoltage() < 3400) {
        rxFlash(500, 100);
    } else {
        digitalWrite(rxLed, LOW);
    }
}