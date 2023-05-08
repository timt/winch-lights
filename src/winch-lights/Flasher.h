#ifndef WINCH_LIGHTS_FLASHER_H
#define WINCH_LIGHTS_FLASHER_H

#include "Arduino.h"


class Flasher {
private:
    int _pin;
    int _maxOnTime;
    int _startTime;
    boolean _isOn = false;

public:
    Flasher(int pin, int maxOnTime);

    void flash(int resetAfterMillis);

    void stop();

    String toString();

    int checkFlasher();
};

#endif //WINCH_LIGHTS_FLASHER_H
