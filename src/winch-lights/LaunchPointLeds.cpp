#include "LaunchPointLeds.h"


LaunchPointLedsClass::LaunchPointLedsClass() : _rxFlasher(RX_LED, 500) {

}

void LaunchPointLedsClass::begin() {
    pinMode(RX_LED, OUTPUT);
    pinMode(STOP_LED, OUTPUT);
    pinMode(TX_LED, OUTPUT);
#if !defined(EPOXY_DUINO)
    Wire.begin(21, 22);
    if (_axp.begin(Wire, AXP192_SLAVE_ADDRESS) == AXP_FAIL) {
        Serial.println(F("failed to initialize communication with AXP192"));
        while (true) {}
    }
#endif
    Serial.println("LED lights setup complete");
}

void LaunchPointLedsClass::setStateTransmitting(boolean isTransmitting) {
    if (isTransmitting) {
        digitalWrite(TX_LED, HIGH);
    } else {
        digitalWrite(TX_LED, LOW);
    }
}

void LaunchPointLedsClass::setStateReceiving(String command) {
    Serial.println("Setting LED state receiving for command: " + command);
    if (command == STOP) {
        _isStopped = true;
        digitalWrite(STOP_LED, HIGH);
        digitalWrite(RX_LED, HIGH);
    } else if (command == CANCEL_STOP) {
        _isStopped = false;
        digitalWrite(RX_LED, LOW);
        digitalWrite(STOP_LED, LOW);
    } else if (command == ALL_OUT && !_isStopped) {
        rxFlash(750);
    } else if (command == TAKE_UP_SLACK && !_isStopped) {
        rxFlash(1500);
    } else if(!_isStopped){
        reset();
    } else {
//        digitalWrite(TX_LED, LOW);
    }
}

void LaunchPointLedsClass::rxFlash(int interval) {
    digitalWrite(STOP_LED, LOW);
    _rxFlasher.flash(interval);
}

void LaunchPointLedsClass::checkBattery() {
//    Serial.println("Battery voltage: " + String(_axp.getBattVoltage()));
    if (_axp.getBattVoltage() < 3400) {
        rxFlash(500);
    } else if (!_isStopped) {
        digitalWrite(RX_LED, LOW);
    }
}

void LaunchPointLedsClass::reset() {
    digitalWrite(STOP_LED, LOW);
    digitalWrite(TX_LED, LOW);
    _rxFlasher.stop();
    _isStopped = false;
}

void LaunchPointLedsClass::checkAllLeds(String command) {
    setStateReceiving(command);
}

LaunchPointLedsClass LaunchPointLeds;
