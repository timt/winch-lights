#include <Arduino.h>
#include <AUnit.h>
#include <IPAddress.h>
#include <AceCommon.h>
#include "./src/Flasher.h"

void setup() {
#if !defined(EPOXY_DUINO)
    delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif

    SERIAL_PORT_MONITOR.begin(115200);
    while (!SERIAL_PORT_MONITOR); // needed for Leonardo/Micro
}

//test(HandleAllOutCommandTurnsOnAllOutLed) {
//        winchLeds.handleCommand(ALL_OUT);
//        assertEqual(HIGH, digitalWriteValue(ALL_OUT_LED));
//        assertEqual(HIGH, digitalWriteValue(BUZZER));
//        assertEqual(LOW, digitalWriteValue(WINCH_STOP_LED));
//}

test(FlasherTurnsOffAfterMaxOnTimeExceeded) {
    const int ledPin = 13;
    const int maxOnTime = 250;
    const int resetAfter = 1000;
    Flasher flasher(ledPin, maxOnTime);

    assertEqual(LOW, digitalWriteValue(ledPin));

    flasher.flash(resetAfter);
    assertEqual(HIGH, digitalWriteValue(ledPin));

    delay(240);
    flasher.flash(resetAfter);
    assertEqual(HIGH, digitalWriteValue(ledPin));

    delay(10);
    flasher.flash(resetAfter);
    assertEqual(LOW, digitalWriteValue(ledPin));
}

test(FlasherCanBeTurnedOnAgainOnceResetAfterExceeded) {
        const int ledPin = 14;
        const int maxOnTime = 50;

        Flasher flasher(ledPin, maxOnTime);

        flasher.flash(100);
        assertEqual(HIGH, digitalWriteValue(ledPin));

        delay(100);
        flasher.flash(100);
        assertEqual(LOW, digitalWriteValue(ledPin));

        flasher.flash(100);
        assertEqual(HIGH, digitalWriteValue(ledPin));
}


void loop() {
    aunit::TestRunner::run();
}

