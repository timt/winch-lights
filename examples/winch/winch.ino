#include <Arduino.h>
#include <winch-lights.h>

const String CLUB_TURN_POINT = "RIN";

void setup() {
    Serial.begin(9600);
    Winch.setClub(CLUB_TURN_POINT);
    Winch.begin();
}

void loop() {
    Winch.loop();
}
