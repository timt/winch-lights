#include "WinchLeds.h"

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

//TODO This is same as for LaunchPointLeds::rxFlash so move to common file/class that can be used in both places
void WinchLeds::flash(int pin, int &startTime, int maxOnTime, int resetPeriod) {
    int now = millis();
    int elapsed = now - startTime;
    if (elapsed > maxOnTime) {
        digitalWrite(pin, LOW);
    } else {
        digitalWrite(pin, HIGH);
    }
    if (elapsed > resetPeriod) {
        startTime = millis();
    }
}