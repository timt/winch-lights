//
// Created by Tim Tennant on 24/04/2023.
//

#ifndef WINCH_LIGHTS_LAUNCH_POINT_LEDS_H
#define WINCH_LIGHTS_LAUNCH_POINT_LEDS_H

#include <Arduino.h>
#include <Wire.h>
#include "Commands.h"
#include <axp20x.h>
#include "Flasher.h"

//led pins
static const int RX_LED = 13;
static const int STOP_LED = 2;
static const int TX_LED = 14;

class LaunchPointLeds {
public:
    LaunchPointLeds();

    void setStateTransmitting(boolean isTransmitting);

    void setStateReceiving(String command);

    void checkBatteryAndReset();

    void setup();

private:
    Flasher _rxFlasher;
    AXP20X_Class _axp;

    void rxFlash(int interval);
};


#endif //WINCH_LIGHTS_LAUNCH_POINT_LEDS_H
