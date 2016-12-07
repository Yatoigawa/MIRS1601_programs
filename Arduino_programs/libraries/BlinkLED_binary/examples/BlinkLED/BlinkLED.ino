#include <BlinkLED_binary.h>

int count = 0;
BlinkLED_binary TapeLED(11, 12, 13);

void setup() {}

void loop() {
	count++;
	TapeLED.BlinkLED(count,1000);
	count = count > 8 ? 0 : count;
}
