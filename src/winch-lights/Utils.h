#ifndef WINCH_LIGHTS_UTILS_H
#define WINCH_LIGHTS_UTILS_H
#include "Arduino.h"

void flash(int pin, int &startTime, int maxOnTime, int resetPeriod);

#endif //WINCH_LIGHTS_UTILS_H
