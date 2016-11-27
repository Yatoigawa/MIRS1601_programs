/*
ピンの初期化をするファイル
*/
#include "Arduino.h"
#include "PinAssignment.h"

//初期化関数定義
void initPinAssiment(const int Pins[], byte io) {
	for (int i = 0; i < sizeof(Pins) / sizeof(Pins[0]); i++)
	{
		pinMode(Pins[i], io);
	}
}