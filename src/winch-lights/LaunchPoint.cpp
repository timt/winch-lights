#include "LaunchPoint.h"

LaunchPointClass::LaunchPointClass() {
}

void LaunchPointClass::setClub(String turnPoint) {
    _clubTurnPoint = turnPoint;
}

void LaunchPointClass::begin() {
    Serial.println("Starting launch-point test");
    Comms.setIdentifiers("L", "W", _clubTurnPoint);
    Comms.begin();
    Buttons.begin();
    LaunchPointLeds.begin();
    Serial.println("Launch point started.");
}


boolean LaunchPointClass::waitTimeHasElapsed() {
    return ((_latestReceiveResult._txId + 1) == _nextTxId) ||
           ((millis() - _lastSendTime) > _interval);
};

void LaunchPointClass::loop() {
    //TODO simplify by breaking up into well named shorter methods
    ReceiveResult result = Comms.receiveMessage();
    if (result.exists()) {
        Serial.println("Received command: " + result._command + ", txId: " + result._txId);
        LaunchPointLeds.setStateReceiving(result._command);
        _latestReceiveResult = result;
    } else {
        String command = Buttons.checkButtonPress();
        if (command == NO_COMMAND) {
            LaunchPointLeds.checkBatteryAndReset();
        }
        if (waitTimeHasElapsed() && (command != NO_COMMAND)) {
            LaunchPointLeds.setStateTransmitting(true);
            Serial.println("Command: " + command);
            int start = millis();
            Comms.sendMessage(command, _nextTxId++);
            Serial.println("Send time: " + String(millis() - start));
            _lastSendTime = millis();
            LaunchPointLeds.setStateTransmitting(false);
        }
    }
}

LaunchPointClass LaunchPoint;