//
// Created by Tim Tennant on 12/05/2023.
//

#include "Winch.h"

WinchClass::WinchClass() {
}

void WinchClass::setClub(String turnPoint) {
    _clubTurnPoint = turnPoint;
}

void WinchClass::begin() {
    Serial.println("Starting winch");
    Comms.setIdentifiers("W", "L", _clubTurnPoint);
    Comms.begin();
    WinchLeds.begin();
    Serial.println("Winch started.");
}

void WinchClass::loop() {
    ReceiveResult result = Comms.receiveMessage();
    if (result.exists()) {
        Comms.sendMessage(result._command, result._txId);
        Serial.println("Received command: " + result._command + ", txId: " + result._txId);
        WinchLeds.handleCommand(result._command);
    } else {
        WinchLeds.checkAllLeds();
    }
}

WinchClass Winch;