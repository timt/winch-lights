//
// Created by Tim Tennant on 24/04/2023.
//

#ifndef WINCH_LIGHTS_LEDLIGHTS_H
#define WINCH_LIGHTS_LEDLIGHTS_H

#include <Wire.h>
#include "Commands.h"
#include <axp20x.h>


//led pins
const int rxled = 13;
const int stopled = 2;
const int powerled = 14;

class LedLights {
public:
    LedLights(int interval);

    void setLedStateTransmitting();

    void setLedStateReceiving(String command);

    void checkBatteryAndReset();

    void setup();

private:
    int _interval;
    int _rxFlashStartTime;
    AXP20X_Class _axp;

    void rxFlash(int interval, int maxOnTime);
};


#endif //WINCH_LIGHTS_LEDLIGHTS_H
