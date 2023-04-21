#include "Comms.h"
#include "Commands.h"


Comms comms("launch-point", "winch", "ESGC");

void setup() {
   // put your setup code here, to run once:
   Serial.begin(9600);
   Serial.println();

   Serial.print("Roll number of the student is: " + NO_COMMAND);
}

void loop() {
   // put your main code here, to run repeatedly:
}

