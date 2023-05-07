#include <Arduino.h>
#include <AUnit.h>
#include <IPAddress.h>
#include <AceCommon.h>
#include "./src/WinchLeds.h"

WinchLeds winchLeds;

void setup() {
#if !defined(EPOXY_DUINO)
    delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif

    SERIAL_PORT_MONITOR.begin(115200);
    while (!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro
    Serial.println("winchLeds: " + winchLeds.toString());
}

test(HandleAllOutCommandTurnsOnAllOutLed) {
        winchLeds.handleCommand(ALL_OUT);
        assertEqual(HIGH, digitalWriteValue(ALL_OUT_LED));
        assertEqual(HIGH, digitalWriteValue(BUZZER));
        assertEqual(LOW, digitalWriteValue(WINCH_STOP_LED));
}

test(HandleTakeUpSlackTurnsOnTakeUpSlackLed) {
        winchLeds.handleCommand(TAKE_UP_SLACK);
        assertEqual(HIGH, digitalWriteValue(TAKE_UP_SLACK_LED));
        assertEqual(HIGH, digitalWriteValue(BUZZER));
        assertEqual(LOW, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(LOW, digitalWriteValue(ALL_OUT_LED));
}

test(HandleStopCommandTurnsOnStopLed) {
        winchLeds.handleCommand(STOP);
        assertEqual(HIGH, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(HIGH, digitalWriteValue(BUZZER));
        assertEqual(LOW, digitalWriteValue(TAKE_UP_SLACK_LED));
        assertEqual(LOW, digitalWriteValue(ALL_OUT_LED));
}

test(HandleCancelStopCommandTurnsOffBuzzer){
    winchLeds.handleCommand(CANCEL_STOP);
        assertEqual(LOW, digitalWriteValue(BUZZER));
        assertEqual(LOW, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(LOW, digitalWriteValue(TAKE_UP_SLACK_LED));
        assertEqual(LOW, digitalWriteValue(ALL_OUT_LED));
}

test(HandleNoCommandTurnsOffAll) {
        winchLeds.handleCommand(NO_COMMAND);
        assertEqual(LOW, digitalWriteValue(BUZZER));
        assertEqual(LOW, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(LOW, digitalWriteValue(TAKE_UP_SLACK_LED));
        assertEqual(LOW, digitalWriteValue(ALL_OUT_LED));
}

void loop() {
    aunit::TestRunner::run();
}

