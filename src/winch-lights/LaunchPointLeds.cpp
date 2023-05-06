#include "LaunchPointLeds.h"


LaunchPointLeds::LaunchPointLeds(int interval) {
    _interval = interval;
    _rxFlashStartTime = millis();
}

void LaunchPointLeds::setup() {
    pinMode(RX_LED, OUTPUT);
    pinMode(STOP_LED, OUTPUT);
    pinMode(POWER_LED, OUTPUT);
#if !defined(EPOXY_DUINO)
    Wire.begin(21, 22);
#endif
    if (_axp.begin(Wire, AXP192_SLAVE_ADDRESS) == AXP_FAIL) {
        Serial.println(F("failed to initialize communication with AXP192"));
        while (true) {}
    }
    Serial.println("LED lights setup complete");
}

void LaunchPointLeds::setStateTransmitting() {
    digitalWrite(POWER_LED, HIGH);
}

void LaunchPointLeds::setStateReceiving(String command) {
    Serial.println("Setting LED state receiving for command: " + command);
    digitalWrite(POWER_LED, LOW);
    if (command == STOP) {
        digitalWrite(STOP_LED, HIGH);
        digitalWrite(RX_LED, HIGH);
    } else if (command == CANCEL_STOP) {
        digitalWrite(RX_LED, LOW);
        digitalWrite(STOP_LED, LOW);
    } else if (command == ALL_OUT) {
        rxFlash(1000, 500);
    } else if (command == TAKE_UP_SLACK) {
        rxFlash(2000, 500);
    }
}
//void flash(int pin, int &startTime, int maxOnTime, int resetPeriod);

void LaunchPointLeds::rxFlash(int interval, int maxOnTime) {
    digitalWrite(STOP_LED, LOW);
    flash(RX_LED, _rxFlashStartTime, maxOnTime, interval);
}

void LaunchPointLeds::checkBatteryAndReset() {
    digitalWrite(STOP_LED, LOW);
    Serial.println("Battery voltage: " + String(_axp.getBattVoltage()));
    if (_axp.getBattVoltage() < 3400) {
        rxFlash(500, 100);
    } else {
        digitalWrite(RX_LED, LOW);
    }
}