#include <STemptureHumidity.h>


byte STemptureHumidity::read_data () {
  byte data;
  for (int i = 0; i < 8; i ++) {
    if (digitalRead (pin) == LOW) {
      while (digitalRead (pin) == LOW); // wait for 50us
      delayMicroseconds (30); // determine the duration of the high level to determine the data is '0 'or '1'
      if (digitalRead (pin) == HIGH)
        data |= (1 << (7-i)); // high front and low in the post
      while (digitalRead (pin) == HIGH); // data '1 ', wait for the next one receiver
     }
  }
return data;
}

STemptureHumidity::STemptureHumidity(int pin, RF24 & radio){
	this->pin = pin;
	this->radio = radio;
}


int STemptureHumidity::readSensorData(){
  digitalWrite (pin, LOW);      // bus down, send start signal
  delay (30);                     // delay greater than 18ms, so DHT11 start signal can be detected
  digitalWrite (pin, HIGH);
  delayMicroseconds (40); // Wait for DHT11 response
  pinMode (pin, INPUT);   
  while (digitalRead (pin) == HIGH);
  delayMicroseconds (80); // DHT11 response, pulled the bus 80us
  if (digitalRead (pin) == LOW);
  delayMicroseconds (80); // DHT11 80us after the bus pulled to start sending data
  for (int i = 0; i < 4; i ++) // receive temperature and humidity data, the parity bit is not considered
    dat[i] = read_data ();
  pinMode (pin, OUTPUT);
  digitalWrite (pin, HIGH); // send data once after releasing the bus, wait for the host to open the next Start signal
	 
  Serial.print ("Current humdity = ");
  Serial.print (dat [0], DEC);                    // display the humidity-bit integer;
  //if(dat[0]>30) 
  //  digitalWrite(LEDin, HIGH);
//  else 
  //  digitalWrite(LEDin, LOW);
  Serial.print ('.');
  Serial.print (dat [1], DEC);                    // display the humidity decimal places;
  Serial.print ("% ");
  Serial.print ("              Temperature = ");
  Serial.print (dat [2], DEC);                    // display the temperature of integer bits;
  Serial.print ('.');
  Serial.print (dat [3], DEC);                    // display the temperature of decimal places;
  Serial.println ('C');
  delay (500);
}


const Message STemptureHumidity :: prepareMessage(){
	
	
  char text[32]="";
  itoa(dat[0],text,10);
  Serial.print("itoa check :");
  Serial.println(text);
    
    Serial.println("here1");
   radio.stopListening();
  char text2[32]="hi";
bool ok =  radio.write(&text, sizeof(text));
  if(ok){
    Serial.println("send seccess");
         
  }
else{
      Serial.println("send failed");

  }
   radio.startListening();

  if (radio.available())
  {
      radio.read(&text, sizeof(text));
      Serial.print("recived message:");
      Serial.println(text);

      limit = atoi(text);
  }
}





