
#include <STemptureHumidity.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Message.h>
#include <SPI.h>


#define MIDDLE_LAYER_ADDRESS 101  
#define MY_ADDRESS 1  

//globals
//-------
RF24 radio(7, 8);

int soil_humidity_threshold_minimum = 40;
int soil_humidity_threshold_maximmum = 40;


const byte rxAddr[6] = "00002";             //worked addresses before
const byte wxAddr[6] = "00001";             //


void initConsole() {
      Serial.println("initConsole called");

  while (!Serial);
  Serial.begin(9600);
}

void initRadio() {
    Serial.println("initRadio called");
    radio.begin();
    radio.setRetries(15, 15);
    radio.openWritingPipe(MIDDLE_LAYER_ADDRESS);
    radio.openReadingPipe(1,MY_ADDRESS);
    radio.stopListening();
}

void setup() {
  Serial.println("setup called");
  initConsole();
  initRadio();
  
}
void sendMessage(Message message){
    Serial.println("sendMessage called");
    bool ok = false;
    int retry_times = 30;
    radio.stopListening();
    while(!ok && --retry_times){  //if message fails , retry 30 times
                 Serial.print("retry: ");  
                 Serial.println(retry_times  );  
         ok =  radio.write(&message, sizeof(message));
        if(ok){
           Serial.println("send seccess");      
        }
         else{
             Serial.println("send failed ");
         }
    }
    radio.startListening();
  }
  Message prepareMessage(Message message){
    message.source = 1;
    message.dest = 101;
    return message;
    }
bool receiveMessage(Message& message){
        Serial.println("receiveMessage called");

    if (radio.available()){
      radio.read(&message, sizeof(message));
      Serial.print("recived message:");
      Serial.println(message.data);
      return true;
    }
    else{
           Serial.println("nothing to read");
           return false;
      }
}


void loop()
{
    Serial.println("loop called");

  Sensor * th= new STemptureHumidity(2);              //create new temperature sensor instanse
    Serial.println("STemptureHumidity created");

//  Sensor * sh= new SSoilHumidity(4); 
 // sh->readSensorData();
  //check threshhold();  
  Message readSensor =  th->readSensorData();          //read sensor data
      Serial.println("after read created");
  Message messageToSend = prepareMessage(readSensor); //add sender id and receiver id to message
  sendMessage(messageToSend);                          //send message  
 
  Message messageToRead;
 if(receiveMessage(messageToRead)){                   //receive message
    Serial.print("main loop, i got: ");
    Serial.println(messageToRead.minimum_threshold);
    Serial.print("and: ");
    Serial.println(messageToRead.maximum_threshold);
 }


  delay(3000);
}
