#include "Buttons.h"

Buttons::Buttons() {

};


void Buttons::setup() {
    pinMode(TAKE_UP_SLACK_BUTTON, INPUT_PULLUP);
    pinMode(ALL_OUT_BUTTON, INPUT_PULLUP);
    pinMode(STOP_BUTTON, INPUT_PULLUP);
    Serial.println("Buttons setup complete");
};

String Buttons::checkButtonPress() {
    //Stop button always takes priority
    if (isPressed(STOP_BUTTON)) {
        return STOP;
    } else if(isPressed(ALL_OUT_BUTTON) && isPressed(TAKE_UP_SLACK_BUTTON)){
        return CANCEL_STOP;
    } else if (isPressed(ALL_OUT_BUTTON)) {
        return ALL_OUT;
    } else if (isPressed(TAKE_UP_SLACK_BUTTON)) {
        return TAKE_UP_SLACK;
    }
    return NO_COMMAND;
};

bool Buttons::isPressed(int button) {
    return digitalRead(button) == LOW;
};