//
// Created by Tim Tennant on 24/04/2023.
//

#ifndef WINCH_LIGHTS_LAUNCH_POINT_LEDS_H
#define WINCH_LIGHTS_LAUNCH_POINT_LEDS_H

#include <Arduino.h>
#include <Wire.h>
#include "Commands.h"
#include <axp20x.h>
#include "Utils.h"

//led pins
const int RX_LED = 13;
const int STOP_LED = 2;
const int POWER_LED = 14;

class LaunchPointLeds {
public:
    LaunchPointLeds(int interval);

    void setStateTransmitting();

    void setStateReceiving(String command);

    void checkBatteryAndReset();

    void setup();

private:
    int _interval;
    int _rxFlashStartTime;
    AXP20X_Class _axp;

    void rxFlash(int interval, int maxOnTime);
};


#endif //WINCH_LIGHTS_LAUNCH_POINT_LEDS_H
