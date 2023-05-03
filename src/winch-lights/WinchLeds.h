#ifndef WINCH_LEDS_WINCHLIGHTS_H
#define WINCH_LEDS_WINCHLIGHTS_H
#include "winch-lights.h"

class WinchLeds {
    public:
    WinchLeds();

    void setup();

    void handleCommand(String command);

private:
    const int allOutLed = 25;
    const int upSlackLed = 14;
    const int stopLed = 13; //13
    const int buzzer = 2; //2
    int _allOutFlashStartTime = millis();
    int _upSlackFlashStartTime = millis();
    int _stopFlashStartTime = millis();
    int _buzzerStartTime = millis();

    void flash(int pin, int& startTime, int maxOnTime, int resetPeriod);

};


#endif //WINCH_LEDS_WINCHLIGHTS_H
