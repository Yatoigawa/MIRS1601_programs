#include <Scheduler.h>

typedef union {
	uint16_t val;
	struct {
		uint8_t lsb;
		uint8_t msb;
	};
} infrared_data_t;

const int BAUDRATE = 115200;

infrared_data_t data;
int i = 0;

void setup() {
	Serial.begin(BAUDRATE);
	Serial2.begin(BAUDRATE);
	Scheduler.startLoop( serial_task );
}

void loop(){
	Serial2.write(i + 0x80);
	if(data.val > 0){
		Serial.print("count: ");
		Serial.print(i);
		Serial.print(" data: ");
		Serial.println(data.val, HEX);
	}
	i++;
	delay(500);
}

void serial_task(){
	if(Serial2.available() > 2){
		if(Serial2.read() == 0xA4){
			data.msb = (Serial2.read() /* & 0x0F */);
			data.lsb =  Serial2.read();
		}
	}
	delay(100);
	yield();
}

