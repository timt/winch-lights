#ifndef WINCH_LIGHTS_FLASHER_H
#define WINCH_LIGHTS_FLASHER_H
#include "Arduino.h"


class Flasher {
private:
    int _pin;
    int _maxOnTime;
    int _startTime;
public:
    Flasher(int pin, int maxOnTime);

    void flash(int resetPeriod);

    void stop();

    String toString();
};

#endif //WINCH_LIGHTS_FLASHER_H
