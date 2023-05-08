#include <Arduino.h>
#include <AUnit.h>
#include <IPAddress.h>
#include <AceCommon.h>
#include "./src/LaunchPointLeds.h"

LaunchPointLeds launchPointLeds;

void setup() {
#if !defined(EPOXY_DUINO)
    delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif

    SERIAL_PORT_MONITOR.begin(115200);
    while (!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro
}

void resetLeds() {
    launchPointLeds.reset();
}

test(SetStateTransmittingTurnsOnPowerLed) {
        resetLeds();
        launchPointLeds.setStateTransmitting(true);
        assertEqual(HIGH, digitalWriteValue(TX_LED));
        launchPointLeds.setStateTransmitting(false);
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

test(OnStopCommandSetStateReceivingTurnsOnStopAndRXLeds) {
        resetLeds();
        launchPointLeds.setStateReceiving(STOP);
        assertEqual(HIGH, digitalWriteValue(STOP_LED));
        assertEqual(HIGH, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

test(OnCancelStopCommandSetStateReceivingTurnsOnRXLed) {
        resetLeds();
        launchPointLeds.setStateReceiving(CANCEL_STOP);
        assertEqual(LOW, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
        assertEqual(LOW, digitalWriteValue(STOP_LED));
}

test(OnAllOutCommandSetStateReceivingTurnsRXLed) {
        resetLeds();
        launchPointLeds.setStateReceiving(ALL_OUT);
        assertEqual(HIGH, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

test(OnTakeUpSlackCommandSetStateReceivingTurnsOnRXLed) {
        resetLeds();
        launchPointLeds.setStateReceiving(TAKE_UP_SLACK);
        assertEqual(HIGH, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

test(OnNoCommandSetStateReceivingTurnsOffAllLed) {
        resetLeds();
        launchPointLeds.setStateReceiving(NO_COMMAND);
        assertEqual(LOW, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

test(WhenStopLightIsOnCancelStopTurnsStopLedAndBuzzerOff) {
        resetLeds();
        launchPointLeds.setStateReceiving(STOP);
        assertEqual(HIGH, digitalWriteValue(STOP_LED));
        launchPointLeds.setStateReceiving(CANCEL_STOP);
        assertEqual(LOW, digitalWriteValue(STOP_LED));
        assertEqual(LOW, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

test(WhenStopLightIsOnAllOutDoesNotCancelStopLedAndBuzzer) {
        resetLeds();
        launchPointLeds.setStateReceiving(STOP);
        assertEqual(HIGH, digitalWriteValue(STOP_LED));
        launchPointLeds.setStateReceiving(ALL_OUT);
        assertEqual(HIGH, digitalWriteValue(STOP_LED));
        assertEqual(LOW, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(TX_LED));
}

void loop() {
    aunit::TestRunner::run();
}

