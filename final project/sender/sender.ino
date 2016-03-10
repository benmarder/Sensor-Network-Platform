

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ArduinoJson.h>

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";
StaticJsonBuffer<200> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();

void setup()
{
    while (!Serial);
  Serial.begin(9600);
  radio.begin();
radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  
  radio.stopListening();
root["sensor"] = "gps";
root["time"] = 1351824120;

JsonArray& data = root.createNestedArray("data");
data.add(48.756080, 6);  // 6 is the number of decimals to print
data.add(2.302038, 6);   // if not specified, 2 digits are printed

 //This prints:
// {"sensor":"gps","time":1351824120,"data":[48.756080,2.302038]}
}

void loop()
{
  const int size=sizeof(unsigned char); 
  char text[255]={"123456789123456789123456789123456788912344567787777777777777777"};
 // root.printTo(text,sizeof(text));
  Serial.println(text);
  
  radio.write(&text, sizeof(text));
  

  delay(1000);
}
