#include "Buttons.h"
#include "Commands.h"

Buttons::Buttons() {

}


void Buttons::setup() {
    pinMode(TAKE_UP_SLACK_BUTTON, INPUT_PULLUP);
    pinMode(ALL_OUT_BUTTON, INPUT_PULLUP);
    pinMode(STOP_BUTTON, INPUT_PULLUP);
}

String Buttons::checkButtonPress() {
    //Stop button always takes priority
    if (digitalRead(STOP_BUTTON) == LOW) {
        return STOP;
    } else if (digitalRead(ALL_OUT_BUTTON) == LOW) {
        return ALL_OUT;
    } else if (digitalRead(TAKE_UP_SLACK_BUTTON) == LOW) {
        return TAKE_UP_SLACK;
    }
    return NO_COMMAND;
}