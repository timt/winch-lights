#include "Comms.h"
#include "Buttons.h"
#include "Commands.h"


Comms comms("launch-point", "winch", "ESGC");
Buttons buttons;
int txId = 0;


void setup() {
   Serial.begin(9600);
   comms.setup();
   buttons.setup();

   Serial.println();
   Serial.print("Launch point started. Local address");
}

void loop() {
    String command = buttons.checkButtonPress();
    if (command != NO_COMMAND) {
        comms.sendMessage(command, txId++);
    }
    delay(100);
    ReceiveResult result = comms.receiveMessage();
    if(result._txId != NO_TX_ID) {
        Serial.println("Received command: " + result._command + ", txId: " + result._txId);
        //Set LED state
    }
}

