#ifndef WINCH_LIGHTS_LAUNCHPOINTCLASS_H
#define WINCH_LIGHTS_LAUNCHPOINTCLASS_H

#include <Arduino.h>
#include "Comms.h"
#include "LaunchPointLeds.h"
#include "Buttons.h"

class LaunchPointClass {
private:
    int _nextTxId = 0;
    int _interval = 500;
    long _lastSendTime = millis();
    String _clubTurnPoint;
    ReceiveResult _latestReceiveResult = ReceiveResult(NO_TX_ID, NO_COMMAND);
    boolean waitTimeHasElapsed();

public:
    LaunchPointClass();

    void setClub(String turnPoint);

    void begin();

    void loop();

};

extern LaunchPointClass LaunchPoint;

#endif //WINCH_LIGHTS_LAUNCHPOINTCLASS_H
