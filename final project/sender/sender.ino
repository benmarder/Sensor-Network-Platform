

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ArduinoJson.h>

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";

void setup()
{
    while (!Serial);
    Serial.begin(9600);
    radio.begin();
    radio.setRetries(15, 15);
    radio.openWritingPipe(rxAddr);
  
    radio.stopListening();



}

void loop()
{
  
  char text[256]={"im the first"};
  Serial.println(text);
  radio.write(&text, sizeof(text));
  

  delay(1000);
}
