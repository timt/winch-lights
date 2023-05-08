#include <winch-lights.h>

int txId = 0;
int interval = 500;
long lastSendTime = millis();
ReceiveResult latestReceiveResult = ReceiveResult(NO_TX_ID, NO_COMMAND);

Comms comms("l", "w", "E");
Buttons buttons;
LaunchPointLeds launchPointLeds;


void setup() {
    Serial.begin(9600);
    comms.setup();
    buttons.setup();
    launchPointLeds.setup();
    Serial.println();
    Serial.print("Launch point started.");
}

boolean waitTimeHasElapsed() {
    return ((latestReceiveResult._txId + 1) == txId) ||
           ((millis() - lastSendTime) > interval);
};

void loop() {
    ReceiveResult result = comms.receiveMessage();
    if (result.exists()) {
        Serial.println("Received command: " + result._command + ", txId: " + result._txId);
        launchPointLeds.setStateReceiving(result._command);
    } else {
        String command = buttons.checkButtonPress();
        if (command == NO_COMMAND) {
            launchPointLeds.checkBatteryAndReset();
        }
        if (waitTimeHasElapsed() && (command != NO_COMMAND)) {
            launchPointLeds.setStateTransmitting(true);
            Serial.println("Command: " + command);
            int start = millis();
            comms.sendMessage(command, txId++);
            Serial.println("Send time: " + String(millis() - start));
            lastSendTime = millis();
            launchPointLeds.setStateTransmitting(false);
        }
    }
}

