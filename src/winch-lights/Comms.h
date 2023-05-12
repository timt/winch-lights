#ifndef WINCH_LIGHTS_COMMS_H
#define WINCH_LIGHTS_COMMS_H

#include "Arduino.h"
#include <SPI.h>
#include <LoRa.h>

static const int NO_TX_ID = -1;

class ReceiveResult {
public:
    int _txId;
    String _command;

    ReceiveResult(int txId, String command);

    bool exists();

};

class Comms {
private:
    String _localAddress;
    String _destinationAddress;
    String _turnPoint;
    long _lastSendTime = 0;
    long _lastRxTime = 0;
    int _interval = 100;
    int _count = 0;
    static const int RADIO_CS_PIN = 18;
    static const int RADIO_DI0_PIN = 26;
    static const int RADIO_RST_PIN = 23;
    const String MESSAGE_DELIMITER = "#";


    String payload(String command, int txId);

    String *messageParts(String message);


public:
    Comms(String localAddress, String destinationAddress, String turnPoint);

    Comms();

    void setup();

    void sendMessage(String command, int txId);

    ReceiveResult receiveMessage();
};

extern Comms CMS;
#endif