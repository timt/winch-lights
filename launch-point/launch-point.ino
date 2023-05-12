#include <winch-lights.h>

int txId = 0;
int interval = 500;
long lastSendTime = millis();
ReceiveResult latestReceiveResult = ReceiveResult(NO_TX_ID, NO_COMMAND);

//Consider having a launch-point library class with a setup and loop only include that here
void setup() {
    Serial.begin(9600);
    Comms.setIdentifiers("L", "W", "RIN");
    Comms.begin();
    Buttons.begin();
    LaunchPointLeds.begin();
    Serial.println();
    Serial.print("Launch point started.");
}

boolean waitTimeHasElapsed() {
    return ((latestReceiveResult._txId + 1) == txId) ||
           ((millis() - lastSendTime) > interval);
};

void loop() {
    //TODO simplify by breaking up into well named shorter methods
    ReceiveResult result = Comms.receiveMessage();
    if (result.exists()) {
        Serial.println("Received command: " + result._command + ", txId: " + result._txId);
        LaunchPointLeds.setStateReceiving(result._command);
    } else {
        String command = Buttons.checkButtonPress();
        if (command == NO_COMMAND) {
            LaunchPointLeds.checkBatteryAndReset();
        }
        if (waitTimeHasElapsed() && (command != NO_COMMAND)) {
            LaunchPointLeds.setStateTransmitting(true);
            Serial.println("Command: " + command);
            int start = millis();
            Comms.sendMessage(command, txId++);
            Serial.println("Send time: " + String(millis() - start));
            lastSendTime = millis();
            LaunchPointLeds.setStateTransmitting(false);
        }
    }
}

