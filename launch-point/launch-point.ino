#include <winch-lights.h>

int txId = 0;
int interval = 100;
Comms comms("launch-point", "winch", "ESGC");
Buttons buttons;
LedLights ledLights(interval);


void setup() {
    Serial.begin(9600);
    comms.setup();
    buttons.setup();
    ledLights.setup();
    Serial.println();
    Serial.print("Launch point started.");
}

void loop() {
    String command = buttons.checkButtonPress();
    if (command != NO_COMMAND) {
        comms.sendMessage(command, txId++);
        ledLights.setLedStateTransmitting();
    }
    delay(interval);
    ReceiveResult result = comms.receiveMessage();
    if (result.exists()) {
        Serial.println("Received command: " + result._command + ", txId: " + result._txId);
        ledLights.setLedStateReceiving(result._command);
    } else {
        ledLights.checkBatteryAndReset();
    }
}

