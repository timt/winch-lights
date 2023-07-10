#include "WinchLeds.h"
#include "Flasher.h"

WinchLedsClass::WinchLedsClass(): _allOutFlasher(ALL_OUT_LED, 500), _upSlackFlasher(TAKE_UP_SLACK_LED, 500),
                        _smallBuzzerFlasher(SMALL_BUZZER, 500) {

}

void WinchLedsClass::begin() {
    pinMode(ALL_OUT_LED, OUTPUT);
    pinMode(TAKE_UP_SLACK_LED, OUTPUT);
    pinMode(WINCH_STOP_LED, OUTPUT);
    pinMode(SMALL_BUZZER, OUTPUT);
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
    digitalWrite(SMALL_BUZZER, HIGH);
    delay(250);
    digitalWrite(SMALL_BUZZER, LOW);
}

void WinchLedsClass::handleCommand(String command) {
    if (command == ALL_OUT && !_isStopped) {
        _allOutFlasher.flash(750);
        _smallBuzzerFlasher.flash(750);
        _upSlackFlasher.stop();
        digitalWrite(WINCH_STOP_LED, LOW);
    } else if (command == TAKE_UP_SLACK && !_isStopped) {
        _upSlackFlasher.flash(1500);
        _smallBuzzerFlasher.flash(1500);
        _allOutFlasher.stop();
        digitalWrite(WINCH_STOP_LED, LOW);
    } else if (command == STOP) {
        _isStopped = true;
        digitalWrite(WINCH_STOP_LED, HIGH);
        _smallBuzzerFlasher.flash(500);
        _allOutFlasher.stop();
        _upSlackFlasher.stop();
    } else if (command == CANCEL_STOP){
        _isStopped = false;
        reset();
    } else if(!_isStopped){
        reset();
    }
}

String WinchLedsClass::toString() {
    return "_allOutFlasher: " + _allOutFlasher.toString() + "\n" +
           "_upSlackFlasher: " + _upSlackFlasher.toString() + "\n" +
           "_smallBuzzerFlasher: " + _smallBuzzerFlasher.toString() + "\n";
}

void WinchLedsClass::reset() {
    _allOutFlasher.stop();
    _upSlackFlasher.stop();
    _smallBuzzerFlasher.stop();
    digitalWrite(WINCH_STOP_LED, LOW);
    _isStopped = false;
}

void WinchLedsClass::checkAllLeds() {
    _allOutFlasher.checkFlasher();
    _upSlackFlasher.checkFlasher();
    _smallBuzzerFlasher.checkFlasher();
}

WinchLedsClass WinchLeds;