#include "WinchLeds.h"
#include "Flasher.h"

WinchLeds::WinchLeds(): _allOutFlasher(ALL_OUT_LED, 500), _upSlackFlasher(TAKE_UP_SLACK_LED, 500),
                        _buzzerFlasher(BUZZER, 500) {

}

void WinchLeds::setup() {
    pinMode(ALL_OUT_LED, OUTPUT);
    pinMode(TAKE_UP_SLACK_LED, OUTPUT);
    pinMode(WINCH_STOP_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    digitalWrite(ALL_OUT_LED, HIGH);
    digitalWrite(TAKE_UP_SLACK_LED, HIGH);
    digitalWrite(WINCH_STOP_LED, HIGH);
    delay(500);
    digitalWrite(ALL_OUT_LED, LOW);
    delay(250);
    digitalWrite(TAKE_UP_SLACK_LED, LOW);
    delay(250);
    digitalWrite(WINCH_STOP_LED, LOW);
    delay(250);
    digitalWrite(BUZZER, HIGH);
    delay(250);
    digitalWrite(BUZZER, LOW);
}

void WinchLeds::handleCommand(String command) {
    if (command == ALL_OUT) {
        _allOutFlasher.flash(1000);
        _buzzerFlasher.flash(1000);
        _upSlackFlasher.stop();
        digitalWrite(WINCH_STOP_LED, LOW);
    } else if (command == TAKE_UP_SLACK) {
        _upSlackFlasher.flash(2000);
        _buzzerFlasher.flash(2000);
        _allOutFlasher.stop();
        digitalWrite(WINCH_STOP_LED, LOW);
    } else if (command == STOP) {
        digitalWrite(WINCH_STOP_LED, HIGH);
        _buzzerFlasher.flash(500);
        _allOutFlasher.stop();
        _upSlackFlasher.stop();
    } else {
        digitalWrite(WINCH_STOP_LED, LOW);
        _allOutFlasher.stop();
        _upSlackFlasher.stop();
        _buzzerFlasher.stop();
    }
}

String WinchLeds::toString() {
    return "_allOutFlasher: " + _allOutFlasher.toString() + "\n" +
           "_upSlackFlasher: " + _upSlackFlasher.toString() + "\n" +
           "_buzzerFlasher: " + _buzzerFlasher.toString() + "\n";
}

