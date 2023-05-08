#include "LaunchPointLeds.h"


LaunchPointLeds::LaunchPointLeds() : _rxFlasher(RX_LED, 500) {

}

void LaunchPointLeds::setup() {
    pinMode(RX_LED, OUTPUT);
    pinMode(STOP_LED, OUTPUT);
    pinMode(TX_LED, OUTPUT);
#if !defined(EPOXY_DUINO)
    Wire.begin(21, 22);
#endif
    if (_axp.begin(Wire, AXP192_SLAVE_ADDRESS) == AXP_FAIL) {
        Serial.println(F("failed to initialize communication with AXP192"));
        while (true) {}
    }
    Serial.println("LED lights setup complete");
}

void LaunchPointLeds::setStateTransmitting(boolean isTransmitting) {
    if (isTransmitting) {
        digitalWrite(TX_LED, HIGH);
    } else {
        digitalWrite(TX_LED, LOW);
    }
}

void LaunchPointLeds::setStateReceiving(String command) {
    Serial.println("Setting LED state receiving for command: " + command);
    digitalWrite(TX_LED, LOW);
    if (command == STOP) {
        _isStopped = true;
        digitalWrite(STOP_LED, HIGH);
        digitalWrite(RX_LED, HIGH);
    } else if (command == CANCEL_STOP) {
        _isStopped = false;
        digitalWrite(RX_LED, LOW);
        digitalWrite(STOP_LED, LOW);
    } else if (command == ALL_OUT && !_isStopped) {
        rxFlash(1000);
    } else if (command == TAKE_UP_SLACK && !_isStopped) {
        rxFlash(2000);
    } else if(!_isStopped){
        reset();
    } else {
        digitalWrite(RX_LED, LOW);
        digitalWrite(TX_LED, LOW);
    }
}
//void flash(int pin, int &startTime, int maxOnTime, int resetPeriod);

void LaunchPointLeds::rxFlash(int interval) {
    digitalWrite(STOP_LED, LOW);
    _rxFlasher.flash(interval);
}

void LaunchPointLeds::checkBatteryAndReset() {
//    Serial.println("Battery voltage: " + String(_axp.getBattVoltage()));
    if (_axp.getBattVoltage() < 3400) {
        rxFlash(500);
    } else {
        digitalWrite(RX_LED, LOW);
    }
}

void LaunchPointLeds::reset() {
    digitalWrite(STOP_LED, LOW);
    digitalWrite(TX_LED, LOW);
    _rxFlasher.stop();
    _isStopped = false;
}