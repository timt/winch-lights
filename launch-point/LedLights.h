//
// Created by Tim Tennant on 24/04/2023.
//

#ifndef WINCH_LIGHTS_LEDLIGHTS_H
#define WINCH_LIGHTS_LEDLIGHTS_H

#include <Chrono.h>
#include <Wire.h>
#include <axp20x.h>
// https://github.com/lewisxhe/AXP202X_Library

Chrono rxchrono;

AXP20X_Class axp;

//led pins
const int rxled = 13;
const int stopled = 2;
const int powerled = 14;

class LedLights {
private:
public:
    LedLights();

    void setLedStateTransmitting();
    void setLedStateReceiving(String command);

    void setup();
};

};


#endif //WINCH_LIGHTS_LEDLIGHTS_H
