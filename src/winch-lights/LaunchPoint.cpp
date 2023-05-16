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

void LaunchPointClass::loop() {
    ReceiveResult result = Comms.receiveMessage();
    if (result.exists()) {
        processReceivedResult(result);
    } else {
        checkForButtonPress();
    }
}

void LaunchPointClass::processReceivedResult(ReceiveResult result) {
    Serial.println("Received command: " + result._command + ", txId: " + result._txId);
    LaunchPointLeds.setStateReceiving(result._command);
    _latestReceiveResult = result;
}

void LaunchPointClass::checkForButtonPress() {
    String command = Buttons.checkButtonPress();
    if (command == NO_COMMAND) {
        LaunchPointLeds.checkBattery();
    } else {
        handleCommand(command);
    }

}

boolean LaunchPointClass::waitTimeHasElapsed() {
    return ((_latestReceiveResult._txId + 1) == _nextTxId) ||
           ((millis() - _lastSendTime) > _interval);
};

void LaunchPointClass::handleCommand(String command){
    if (waitTimeHasElapsed()) {
        LaunchPointLeds.setStateTransmitting(true);
        Serial.println("Command: " + command);
        int start = millis();
        Comms.sendMessage(command, _nextTxId++);
        Serial.println("Send time: " + String(millis() - start));
        _lastSendTime = millis();
        LaunchPointLeds.setStateTransmitting(false);
    }
}

LaunchPointClass LaunchPoint;