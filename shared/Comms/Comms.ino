#include <SPI.h>
#include <LoRa.h>


#define RADIO_CS_PIN 18
#define RADIO_DI0_PIN 26
#define RADIO_RST_PIN 23

class Comms(localAddress:byte ) {
  private:
    byte _localAddress;
    byte _destinationAddress;
    string _glidingClub;
    byte txCommand = 0;
    byte rxCommand = 0;
    byte txID = 0;
    long lastSendTime = 0;
    long lastRxTime = 0;
    int interval = 100;
    int count = 0;

  public:
    Comms(byte localAddress, byte destinationAddress, string glidingClub){
      _localAddress = localAddress;
      _destinationAddress = destinationAddress;
    }

    void setup() {
      LoRa.setPins(RADIO_CS_PIN, RADIO_RST_PIN, RADIO_DI0_PIN);      
    }

    void sendMessage(byte: command, byte: txId) {
      string message "gc$glidingClub$-Command[TakeUpSlack]-txId[1234]"
      bytes buffer = bytes[message.length];
      LoRa.beginPacket();
      LoRa.write(buffer, buffer.length);
      // LoRa.write(destinationAddress);
      // LoRa.write(localAddress);
      // LoRa.write(txCommand);
      // LoRa.write(txCommand);
      // LoRa.write(txCommand);
      // LoRa.write(txID);
      LoRa.endPacket();
    }


}