#include "LedLights.h"

LedLights::LedLights() {

}

void LedLights::setup() {
    pinMode(rxled, OUTPUT);
    pinMode(stopled, OUTPUT);
    pinMode(powerled, OUTPUT);
    Wire.begin(21, 22);
    if(axp.begin(Wire, AXP192_SLAVE_ADDRESS) == AXP_FAIL) {
        Serial.println(F("failed to initialize communication with AXP192"));
        while (true) {}
    }
    Serial.println("LedLights setup complete");
}

void LedLights::setLedStateTransmitting() {
//    digitalWrite(RED_LED, HIGH);
//    digitalWrite(GREEN_LED, LOW);
//    digitalWrite(BLUE_LED, LOW);
}

void LedLights::setLedStateReceiving(String command) {
//    if (command == ALL_OUT) {
//        digitalWrite(RED_LED, LOW);
//        digitalWrite(GREEN_LED, LOW);
//        digitalWrite(BLUE_LED, HIGH);
//    } else if (command == TAKE_UP_SLACK) {
//        digitalWrite(RED_LED, LOW);
//        digitalWrite(GREEN_LED, HIGH);
//        digitalWrite(BLUE_LED, LOW);
//    } else if (command == STOP) {
//        digitalWrite(RED_LED, HIGH);
//        digitalWrite(GREEN_LED, LOW);
//        digitalWrite(BLUE_LED, HIGH);
//    }
}