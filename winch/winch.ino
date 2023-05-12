#include <winch-lights.h>

WinchLeds winchLeds;
int interval = 100;
long lastSendTime = 0;

//Consider having a winch library class with a setup and loop only include that here
void setup() {
    Serial.begin(9600);
    Comms.setIdentifiers("W", "L", "RIN");
    Comms.begin();
    winchLeds.setup();
}

void loop() {
    //Have winchLeds.handleCommand also handle the "NO_COMMAND" case so can get rid of the if here
    //Also consider returning just the command from comms.receiveMessage() rather than a struct
    ReceiveResult result = Comms.receiveMessage();
    if (result.exists()) {
        Comms.sendMessage(result._command, result._txId);
        Serial.println("Received command: " + result._command + ", txId: " + result._txId);
        winchLeds.handleCommand(result._command);
    } else {
        winchLeds.checkAllLeds();
    }
}