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

test(SetStateTransmittingTurnsOnPowerLed) {
        launchPointLeds.setStateTransmitting();
        assertEqual(HIGH, digitalWriteValue(POWER_LED));
}

test(OnStopCommandSetStateReceivingTurnsOnStopAndRXLeds) {
        launchPointLeds.setStateReceiving(STOP);
        assertEqual(HIGH, digitalWriteValue(STOP_LED));
        assertEqual(HIGH, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(POWER_LED));
}

test(OnCancelStopCommandSetStateReceivingTurnsOnRXLed) {
        launchPointLeds.setStateReceiving(CANCEL_STOP);
        assertEqual(LOW, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(POWER_LED));
        assertEqual(LOW, digitalWriteValue(STOP_LED));
}

test(OnAllOutCommandSetStateReceivingTurnsRXLed) {
        launchPointLeds.setStateReceiving(ALL_OUT);
        assertEqual(HIGH, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(POWER_LED));
        assertEqual(LOW, digitalWriteValue(STOP_LED));
}

test(OnTakeUpSlackCommandSetStateReceivingTurnsOnRXLed) {
        launchPointLeds.setStateReceiving(TAKE_UP_SLACK);
        assertEqual(HIGH, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(POWER_LED));
        assertEqual(LOW, digitalWriteValue(STOP_LED));
}

test(OnNoCommandSetStateReceivingTurnsOffAllLed) {
        launchPointLeds.setStateReceiving(NO_COMMAND);
        assertEqual(LOW, digitalWriteValue(RX_LED));
        assertEqual(LOW, digitalWriteValue(POWER_LED));
        assertEqual(LOW, digitalWriteValue(STOP_LED));
}

void loop() {
    aunit::TestRunner::run();
}

