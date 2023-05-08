#include <winch-lights.h>

int txId = 0;
int interval = 500;
long lastSendTime = millis();

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

void loop() {
    ReceiveResult result = comms.receiveMessage();
    if (result.exists()) {
        Serial.println("Received command: " + result._command + ", txId: " + result._txId);
        launchPointLeds.setStateReceiving(result._command);
    } else {
        String command = buttons.checkButtonPress();
        Serial.println("Command: " + command);
        if (((millis() - lastSendTime) > interval) && (command != NO_COMMAND)) {
            launchPointLeds.setStateTransmitting(true);
            int start = millis();
            comms.sendMessage(command, txId++);
            Serial.println("Send time: " + String(millis() - start));
            lastSendTime = millis();
            launchPointLeds.setStateTransmitting(false);
        }
         launchPointLeds.checkBatteryAndReset();
    }
}

