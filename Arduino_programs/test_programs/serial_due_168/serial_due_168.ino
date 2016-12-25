#include <Scheduler.h>

const int BAUDRATE = 115200;
uint8_t serial_data = 0x00;

void setup() {
	Serial.begin(BAUDRATE);
	Serial2.begin(BAUDRATE);

	// バッファクリア
	while(Serial.available() > 0){
		Serial.read();
	}
	while(Serial2.available() > 0){
		Serial2.read();
	}
	Scheduler.startLoop( serial_task );
}


void loop(){
	if(serial_data > 0){
		Serial.println(serial_data, HEX);
	}
	delay(500);
}

void serial_task(){
	if(Serial2.available() > 0){
		serial_data = Serial2.read();
	}
	yield();
}

