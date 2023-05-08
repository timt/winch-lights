#include <winch-lights.h>

Comms comms("winch", "launch-point", "ESGC");
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
    Serial.println("Command: " + result._command);
    if (result.exists()) {
        Serial.println("Received command: " + result._command + ", txId: " + result._txId);
        winchLeds.handleCommand(result._command);
        comms.sendMessage(result._command, result._txId);
    }
}