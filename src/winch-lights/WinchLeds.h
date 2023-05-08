#ifndef WINCH_LEDS_WINCHLIGHTS_H
#define WINCH_LEDS_WINCHLIGHTS_H
#include <Arduino.h>
#include "Commands.h"
#include "Flasher.h"

static const int ALL_OUT_LED = 25;
static const int TAKE_UP_SLACK_LED = 14;
static const int WINCH_STOP_LED = 13;
static const int SMALL_BUZZER = 2;

class WinchLeds {
    public:
    WinchLeds();

    void setup();

    void handleCommand(String command);

    String toString();

    void reset();

    void checkAllLeds();

private:
    Flasher _allOutFlasher;
    Flasher _upSlackFlasher;
    Flasher _smallBuzzerFlasher;
    boolean _isStopped=false;
};


#endif //WINCH_LEDS_WINCHLIGHTS_H
