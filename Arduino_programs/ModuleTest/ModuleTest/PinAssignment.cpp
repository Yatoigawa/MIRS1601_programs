/*
ピンの初期化をするファイル
*/
#include "PinAssignment.h"
#include "Arduino.h"

//変数定義
//ピン名を配列に入れる(初期化関数で使うため)
//TODO:全てのピンを適切な配列に入れる(面倒)
const int outputPins[5] = { 8, 9 ,TL_0, TL_1, TL_2};
const int inputPins[1] = { 2 };

//初期化関数定義
void initPinAssiment(const int Pins[], byte io) {
	for (int i = 0; i < sizeof(Pins) / sizeof(Pins[0]); i++)
	{
		pinMode(Pins[i], io);
	}
}