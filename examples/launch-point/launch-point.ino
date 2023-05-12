#
#include <winch-lights.h>

const String CLUB_TURN_POINT = "RIN";

void setup() {
    Serial.begin(9600);
    LaunchPoint.setClub(CLUB_TURN_POINT);
    LaunchPoint.begin();
}

void loop() {
    LaunchPoint.loop();
}

