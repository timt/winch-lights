#include <Arduino.h>
#include <AUnit.h>
#include <IPAddress.h>
#include <AceCommon.h>
#include "./src/WinchLeds.h"

void setup() {
#if !defined(EPOXY_DUINO)
    delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif

    SERIAL_PORT_MONITOR.begin(115200);
    while (!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro
    Serial.println("winchLeds: " + WinchLeds.toString());
}

void beforeEach() {
    WinchLeds.reset();
}

test(HandleAllOutCommandTurnsOnAllOutLed) {
        beforeEach();
        WinchLeds.handleCommand(ALL_OUT);
        assertEqual(HIGH, digitalWriteValue(ALL_OUT_LED));
        assertEqual(HIGH, digitalWriteValue(SMALL_BUZZER));
        assertEqual(LOW, digitalWriteValue(WINCH_STOP_LED));
}

test(HandleTakeUpSlackTurnsOnTakeUpSlackLed) {
        beforeEach();
        WinchLeds.handleCommand(TAKE_UP_SLACK);
        assertEqual(HIGH, digitalWriteValue(TAKE_UP_SLACK_LED));
        assertEqual(HIGH, digitalWriteValue(SMALL_BUZZER));
        assertEqual(LOW, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(LOW, digitalWriteValue(ALL_OUT_LED));
}

test(HandleStopCommandTurnsOnStopLed) {
        beforeEach();
        WinchLeds.handleCommand(STOP);
        assertEqual(HIGH, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(HIGH, digitalWriteValue(SMALL_BUZZER));
        assertEqual(LOW, digitalWriteValue(TAKE_UP_SLACK_LED));
        assertEqual(LOW, digitalWriteValue(ALL_OUT_LED));
}

test(HandleCancelStopCommandTurnsOffSMALL_BUZZER){
        beforeEach();
        WinchLeds.handleCommand(CANCEL_STOP);
        assertEqual(LOW, digitalWriteValue(SMALL_BUZZER));
        assertEqual(LOW, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(LOW, digitalWriteValue(TAKE_UP_SLACK_LED));
        assertEqual(LOW, digitalWriteValue(ALL_OUT_LED));
}

test(HandleNoCommandTurnsOffAll) {
        beforeEach();
        WinchLeds.handleCommand(NO_COMMAND);
        assertEqual(LOW, digitalWriteValue(SMALL_BUZZER));
        assertEqual(LOW, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(LOW, digitalWriteValue(TAKE_UP_SLACK_LED));
        assertEqual(LOW, digitalWriteValue(ALL_OUT_LED));
}

test(WhenInStopModeHandleCancelStopCommandTurnsOffSmallBuzzerAndStopLight) {
        beforeEach();
        WinchLeds.handleCommand(STOP);
        assertEqual(HIGH, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(HIGH, digitalWriteValue(SMALL_BUZZER));
        WinchLeds.handleCommand(CANCEL_STOP);
        assertEqual(LOW, digitalWriteValue(SMALL_BUZZER));
        assertEqual(LOW, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(LOW, digitalWriteValue(TAKE_UP_SLACK_LED));
        assertEqual(LOW, digitalWriteValue(ALL_OUT_LED));
}

test(WhenInStopModeHandleAllOutCommandLeavesStopBuzzerAndLightOn) {
        beforeEach();
        WinchLeds.handleCommand(STOP);
        assertEqual(HIGH, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(HIGH, digitalWriteValue(SMALL_BUZZER));
        WinchLeds.handleCommand(ALL_OUT);
        assertEqual(HIGH, digitalWriteValue(SMALL_BUZZER));
        assertEqual(HIGH, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(LOW, digitalWriteValue(TAKE_UP_SLACK_LED));
        assertEqual(LOW, digitalWriteValue(ALL_OUT_LED));
}

test(WhenInStopModeHandleTakeUpSlackCommandLeavesStopBuzzerAndLightOn) {
        beforeEach();
        WinchLeds.handleCommand(STOP);
        assertEqual(HIGH, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(HIGH, digitalWriteValue(SMALL_BUZZER));
        WinchLeds.handleCommand(TAKE_UP_SLACK);
        assertEqual(HIGH, digitalWriteValue(SMALL_BUZZER));
        assertEqual(HIGH, digitalWriteValue(WINCH_STOP_LED));
        assertEqual(LOW, digitalWriteValue(TAKE_UP_SLACK_LED));
        assertEqual(LOW, digitalWriteValue(ALL_OUT_LED));
}

void loop() {
    aunit::TestRunner::run();
}

