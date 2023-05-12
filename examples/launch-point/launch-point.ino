#
#include <winch-lights.h>

void setup() {
    Serial.begin(9600);
    Serial.println("Starting launch-point test");
    LaunchPoint.setClub("RIN");
    LaunchPoint.begin();
    Serial.print("Launch point started.");
}

void loop() {
    LaunchPoint.loop();
}

