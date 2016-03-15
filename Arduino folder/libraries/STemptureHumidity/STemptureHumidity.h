#ifndef S_TEMPERTURE_HUMIDITY_H
#define S_TEMPERTURE_HUMIDITY_H
#include <Arduino.h>
#include <Sensor.h>
#include <RF24.h>

class STemptureHumidity : public Sensor {
public:
	STemptureHumidity(int,  RF24 &);
	int readSensorData();
	const Message prepareMessage();
	byte read_data();//aux func
private:
	int pin;
	byte dat[4];
	RF24 radio;
};


#endif