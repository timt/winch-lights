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

Comms::Comms(String localAddress, String destinationAddress, String glidingClub) {
    _localAddress = localAddress;
    _destinationAddress = destinationAddress;
    _glidingClub = glidingClub;
};

void Comms::setup() {
    LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DI0_PIN);
    if (!LoRa.begin(866E6)) {
        Serial.println("LoRa init failed. Check your connections.");
        while (true) {}
    }
    Serial.println("Comms setup complete. Local address: " + _localAddress + ", destination address: " + _destinationAddress +
                   ", gliding club: " + _glidingClub);
};

String Comms::payload(String command, int txId) {
    String message =
            String(txId) + MESSAGE_DELIMITER + _glidingClub + MESSAGE_DELIMITER + _localAddress + MESSAGE_DELIMITER +
            _destinationAddress + MESSAGE_DELIMITER + command;
    return message;
};

String *Comms::messageParts(String message) {
    int index = 0;
    String parts[5];
    while (message.indexOf(MESSAGE_DELIMITER) != -1) {
        parts[index] = message.substring(0, message.indexOf(MESSAGE_DELIMITER));
        message = message.substring(message.indexOf(MESSAGE_DELIMITER) + 1);
        index++;
    }
    parts[index] = message;
    return parts;
};

void Comms::sendMessage(String command, int txId) {
    String message = payload(command, txId);
    byte buffer[message.length()];
    message.getBytes(buffer, message.length());
    LoRa.beginPacket();
    LoRa.write(buffer, message.length());
    LoRa.endPacket();
};

ReceiveResult Comms::receiveMessage() {
    int packetSize = LoRa.parsePacket();
    if (packetSize == 0) return NO_RESULT;

    byte buffer[packetSize];

    for (int i = 0; i < packetSize; i++) {
        buffer[i] = LoRa.read();
    }

    String message = String((char *) buffer);
    Serial.println("Received message: " + message);
    byte rssi = LoRa.packetRssi();
    Serial.println("RSSI: " + String(rssi));

    String *parts = messageParts(message);
    String txId = parts[0];
    String glidingClub = parts[1];
    String sender = parts[2];
    String recipient = parts[3];
    String command = parts[4];

    if(glidingClub != _glidingClub) {
        Serial.println("Error: Gliding club ["+glidingClub +"] does not match local gliding club[" + _glidingClub +"]");
        return NO_RESULT;
    }
    if (recipient != _localAddress) {
        Serial.println("Error: Recipient address ["+recipient +"] does not match local address[" + _localAddress +"]");
        return NO_RESULT;
    }

    _lastRxTime = millis();

    return ReceiveResult(txId.toInt(), command);
}



