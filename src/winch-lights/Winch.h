//
// Created by Tim Tennant on 12/05/2023.
//

#ifndef WINCH_LIGHTS_WINCH_H
#define WINCH_LIGHTS_WINCH_H
#include <Arduino.h>
#include "WinchLeds.h"
#include "Comms.h"

class WinchClass {
private:
    String _clubTurnPoint;
public:
    WinchClass();

    void setClub(String turnPoint);

    void begin();

    void loop();
};

extern WinchClass Winch;

#endif //WINCH_LIGHTS_WINCH_H
