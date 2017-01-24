/*
file   : BlinkLED_binary.h
Create : 2016/12/02
Author : R. Hirayama
Board  : Arduino Due

feture :
0~8の数字を3bitの2進数にエンコードした後、各桁に対応するLEDを光らせます。
*/

#ifndef _TAPELED_h
#define _TAPELED_h

#include "Arduino.h"

class BlinkLED_binary {
public:
	BlinkLED_binary(int LED1, int LED2, int LED3);

	void BlinkLED(int dec, int delayTime) {
		int i;
		int j;
		byte state;
		for (i = 0, j = 1; i < sizeof(this->_LED) / sizeof(this->_LED[0]); i++, j = j << 1) {
			state = (dec & j) > 0 ? HIGH : LOW;
			digitalWrite(this->_LED[i], state);
		}
		delay(delayTime);
		for (i = 0; i < sizeof(this->_LED) / sizeof(this->_LED[0]); i++) {
			digitalWrite(this->_LED[i], LOW);
		}
	}

private:
	int _LED[3];
};

#endif

