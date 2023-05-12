#ifndef WINCH_LIGHTS_BUTTONS_H
#define WINCH_LIGHTS_BUTTONS_H

#include "Arduino.h"
#include "Commands.h"

static const int TAKE_UP_SLACK_BUTTON = 4;
static const int ALL_OUT_BUTTON = 15;
static const int STOP_BUTTON = 25;

class ButtonsClass {
private:
    bool isPressed(int button);

public:
    ButtonsClass();

    String checkButtonPress();

    void begin();
};

extern ButtonsClass Buttons;

#endif //WINCH_LIGHTS_BUTTONS_H
