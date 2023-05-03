#include "WinchLeds.h"
#include "Utils.h"

WinchLeds::WinchLeds() {

}

void WinchLeds::setup() {
    pinMode(allOutLed, OUTPUT);
    pinMode(upSlackLed, OUTPUT);
    pinMode(stopLed, OUTPUT);
    pinMode(buzzer, OUTPUT);
    digitalWrite(allOutLed, HIGH);
    digitalWrite(upSlackLed, HIGH);
    digitalWrite(stopLed, HIGH);
    delay(500);
    digitalWrite(allOutLed, LOW);
    delay(250);
    digitalWrite(upSlackLed, LOW);
    delay(250);
    digitalWrite(stopLed, LOW);
    delay(250);
    digitalWrite(buzzer, HIGH);
    delay(250);
    digitalWrite(buzzer, LOW);
}

void WinchLeds::handleCommand(String command) {
    if (command == ALL_OUT) {
        flash(allOutLed, _allOutFlashStartTime, 500, 1000);
        flash(buzzer, _buzzerStartTime, 500, 1000);
    } else if (command == TAKE_UP_SLACK) {
        flash(upSlackLed, _upSlackFlashStartTime, 500, 2000);
        flash(buzzer, _buzzerStartTime, 500, 2000);
    } else if (command == STOP) {
        digitalWrite(stopLed, HIGH);
        flash(buzzer, _buzzerStartTime, 500, 500);
    } else {
        digitalWrite(allOutLed, LOW);
        _allOutFlashStartTime = millis();
        digitalWrite(upSlackLed, LOW);
        _upSlackFlashStartTime = millis();
        digitalWrite(stopLed, LOW);
        _stopFlashStartTime = millis();
        digitalWrite(buzzer, LOW);
        _buzzerStartTime = millis();
    }
}

