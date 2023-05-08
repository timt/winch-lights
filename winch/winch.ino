#include <winch-lights.h>

Comms comms("w", "l", "E");
WinchLeds winchLeds;
int interval = 100;
long lastSendTime = 0;

void setup() {
    Serial.begin(9600);
    comms.setup();
    winchLeds.setup();
}

void loop() {
    ReceiveResult result = comms.receiveMessage();
    if (result.exists()) {
        comms.sendMessage(result._command, result._txId);
        Serial.println("Received command: " + result._command + ", txId: " + result._txId);
        winchLeds.handleCommand(result._command);
    }
}