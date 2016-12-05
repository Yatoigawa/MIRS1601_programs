#include <USS.h>

USS uss[4] = { USS(7), USS(8), USS(9),USS(10) };

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	for (int i;i < sizeof(uss) / sizeof(uss[0]);i++) {
		Serial.print(uss[i].getCM());
	}
	Serial.println();
	delay(100);
}
