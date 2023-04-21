#include "Comms.h"
#include "Buttons.h"
#include "Commands.h"


Comms comms("launch-point", "winch", "ESGC");
Buttons buttons;


void setup() {
   // put your setup code here, to run once:
   Serial.begin(9600);
   comms.setup();
   buttons.setup();
   Serial.println();

   Serial.print("Roll number of the student is: " + NO_COMMAND);
}

void loop() {
    String command = buttons.checkButtonPress();
    //If button press, send message
    delay(100);
    //Check for response
    //Set LED state
}

