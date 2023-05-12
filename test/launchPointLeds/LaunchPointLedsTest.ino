#include <Arduino.h>
#include <AUnit.h>
#include <IPAddress.h>
#include <AceCommon.h>
#include "./src/LaunchPointLeds.h"

void setup() {
#if !defined(EPOXY_DUINO)
    delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif
    LaunchPointLeds.begin();
    SERIAL_PORT_MONITOR.begin(115200);
    while (!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro
}

void resetLeds() {
    LaunchPointLeds.reset();
}

test(SetStateTransmittingTurnsOnPowerLed) {
        resetLeds();
        LaunchPointLeds.setStateTransmitting(true);
        assertEqual(HIGH, digitalWriteValue(TX_LED));
        LaunchPointLeds.setStateTransmitting(false);
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

test(OnStopCommandSetStateReceivingTurnsOnStopAndRXLeds) {
        resetLeds();
        LaunchPointLeds.setStateReceiving(STOP);
        assertEqual(HIGH, digitalWriteValue(STOP_LED));
        assertEqual(HIGH, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

test(OnCancelStopCommandSetStateReceivingTurnsOnRXLed) {
        resetLeds();
        LaunchPointLeds.setStateReceiving(CANCEL_STOP);
        assertEqual(LOW, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
        assertEqual(LOW, digitalWriteValue(STOP_LED));
}

test(OnAllOutCommandSetStateReceivingTurnsRXLed) {
        resetLeds();
        LaunchPointLeds.setStateReceiving(ALL_OUT);
        assertEqual(HIGH, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

test(OnTakeUpSlackCommandSetStateReceivingTurnsOnRXLed) {
        resetLeds();
        LaunchPointLeds.setStateReceiving(TAKE_UP_SLACK);
        assertEqual(HIGH, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

test(OnNoCommandSetStateReceivingTurnsOffAllLed) {
        resetLeds();
        LaunchPointLeds.setStateReceiving(NO_COMMAND);
        assertEqual(LOW, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

test(WhenStopLightIsOnCancelStopTurnsStopLedAndBuzzerOff) {
        resetLeds();
        LaunchPointLeds.setStateReceiving(STOP);
        assertEqual(HIGH, digitalWriteValue(STOP_LED));
        LaunchPointLeds.setStateReceiving(CANCEL_STOP);
        assertEqual(LOW, digitalWriteValue(STOP_LED));
        assertEqual(LOW, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

test(WhenStopLightIsOnAllOutDoesNotCancelStopLedAndBuzzer) {
        resetLeds();
        LaunchPointLeds.setStateReceiving(STOP);
        assertEqual(HIGH, digitalWriteValue(STOP_LED));
        LaunchPointLeds.setStateReceiving(ALL_OUT);
        assertEqual(HIGH, digitalWriteValue(STOP_LED));
        assertEqual(LOW, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

void loop() {
    aunit::TestRunner::run();
}

