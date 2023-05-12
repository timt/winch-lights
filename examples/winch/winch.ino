#include <Arduino.h>
#include <winch-lights.h>

void setup() {
    Serial.begin(9600);
    Serial.println("Starting winch-lights test");
    Winch.setClub("RIN");
    Winch.begin();
    Serial.print("Winch-lights started.");
}

void loop() {
    Winch.loop();
}
