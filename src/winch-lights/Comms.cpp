#include "Comms.h"
#include "Commands.h"

const ReceiveResult NO_RESULT = ReceiveResult(NO_TX_ID, NO_COMMAND);

ReceiveResult::ReceiveResult(int txId, String command) {
    _txId = txId;
    _command = command;
}

bool ReceiveResult::exists() {
    return _txId != NO_TX_ID;
}

CommsClass::CommsClass() {
    //Do nothing here
}

void CommsClass::setIdentifiers(String localAddress, String destinationAddress, String turnPoint) {
    _localAddress = localAddress;
    _destinationAddress = destinationAddress;
    _turnPoint = turnPoint.substring(0, 3);
}

void CommsClass::begin() {
    LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DI0_PIN);
    if (!LoRa.begin(866E6)) {
        Serial.println("LoRa init failed. Check your connections.");
        while (true) {}
    }
    Serial.println(
            "Comms setup complete. Local address: " + _localAddress + ", destination address: " + _destinationAddress +
            ", gliding club: " + _turnPoint);
}

String CommsClass::payload(String command, int txId) {
    String message =
            String(txId) + MESSAGE_DELIMITER + _turnPoint + MESSAGE_DELIMITER + _localAddress + MESSAGE_DELIMITER +
            _destinationAddress + MESSAGE_DELIMITER + command;
    return message;
}

String* CommsClass::messageParts(String message) {
    int index = 0;
    String* parts = new String[5];
    while (message.indexOf(MESSAGE_DELIMITER) != -1) {
        parts[index] = message.substring(0, message.indexOf(MESSAGE_DELIMITER));
        message = message.substring(message.indexOf(MESSAGE_DELIMITER) + MESSAGE_DELIMITER.length());
        index++;
    }
    parts[index] = message;
    return parts;
}

void CommsClass::sendMessage(String command, int txId) {
    String message = payload(command, txId);
    Serial.println("Sending message: " + message);
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
}

ReceiveResult CommsClass::receiveMessage() {
    int packetSize = LoRa.parsePacket();
    if (packetSize == 0) return NO_RESULT;
    String message = "";
    while (LoRa.available()) {
        message += (char) LoRa.read();
    }
    Serial.println("Received message: " + message);
    byte rssi = LoRa.packetRssi();
    Serial.println("RSSI: " + String(rssi));

    String *parts = messageParts(message);
    String txId = parts[0];
    String turnPoint = parts[1];
    String sender = parts[2];
    String recipient = parts[3];
    String command = parts[4];

    if (turnPoint != _turnPoint) {
        Serial.println(
                "Error: Gliding club [" + turnPoint + "] does not match local gliding club[" + _turnPoint + "]");
        return NO_RESULT;
    }
    if (recipient != _localAddress) {
        Serial.println(
                "Error: Recipient address [" + recipient + "] does not match local address[" + _localAddress + "]");
        return NO_RESULT;
    }

    _lastRxTime = millis();

    return ReceiveResult(txId.toInt(), command);
}

CommsClass Comms;
