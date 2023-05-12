#include <Arduino.h>
#include <AUnit.h>
#include <IPAddress.h>
#include <AceCommon.h>
#include "./src/Buttons.h"

void resetButtons() {
    Buttons.begin();
    //make sure all the buttons are in not pressed state (epoxy_duino does not seem to honour the pinMode([button], INPUT_PULLUP))
    digitalReadValue(TAKE_UP_SLACK_BUTTON, HIGH);
    digitalReadValue(ALL_OUT_BUTTON, HIGH);
    digitalReadValue(STOP_BUTTON, HIGH);
}

void setup() {
#if !defined(EPOXY_DUINO)
    delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif

    SERIAL_PORT_MONITOR.begin(115200);
    while (!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro
}

test(NoButtonPressReturnsNoCommand) {
        resetButtons();
        assertEqual(NO_COMMAND, Buttons.checkButtonPress());
}

test(PressingStopButtonReturnsStopCommand) {
        resetButtons();
        digitalReadValue(STOP_BUTTON, LOW);
        assertEqual(STOP, Buttons.checkButtonPress());
}

test(PressingAllOutButtonReturnsAllOutCommand) {
        resetButtons();
        digitalReadValue(ALL_OUT_BUTTON, LOW);
        assertEqual(ALL_OUT, Buttons.checkButtonPress());
}

test(PressingTakeUpSlackButtonReturnsTakeUpSlackCommand) {
        resetButtons();
        digitalReadValue(TAKE_UP_SLACK_BUTTON, LOW);
        assertEqual(TAKE_UP_SLACK, Buttons.checkButtonPress());
}

test(PressingAllOutAndTakeUpSlackButtonReturnsCancelStopCommand) {
        resetButtons();
        digitalReadValue(ALL_OUT_BUTTON, LOW);
        digitalReadValue(TAKE_UP_SLACK_BUTTON, LOW);
        assertEqual(CANCEL_STOP, Buttons.checkButtonPress());
}


void loop() {
    aunit::TestRunner::run();
}

