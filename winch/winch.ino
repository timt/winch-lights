#include <winch-lights.h>
#include "WinchLeds.h"

Comms comms("winch", "launch-point", "ESGC");
WinchLeds winchLeds;
int interval = 100;

void setup() {
    Serial.begin(9600);
    comms.setup();
    winchLeds.setup();
}

void loop() {
    ReceiveResult result = comms.receiveMessage();
    if (result.exists()) {
        Serial.println("Received command: " + result._command + ", txId: " + result._txId);
        winchLeds.handleCommand(result._command);
    }
    delay(interval);
}