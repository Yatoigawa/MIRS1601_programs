/*
メインプログラム
テストボードごとに書き換えるのは面倒なのでシリアル通信でテスト内容を変更する
*/
#include "PinAssignment.h"
#include <L298N.h>

//変数定義
//ピン名を配列に入れる(初期化関数で使うため)
//TODO:全てのピンを適切な配列に入れる(面倒)
const int outputPins[3] = { TL_0, TL_1, TL_2 };
const int inputPins[1] = { 12 };
L298N driver1(MTR_1ENA, P_N1, P_N2, P_S1, P_S2, MTR_1ENB);
L298N driver2(MTR_2ENA, P_E1, P_E2, P_W1, P_W2, MTR_2ENB);
char command = NULL;
bool checkTestFinished = true;
bool ledState = true;

//プロトタイプ宣言
void flashLED(int pin, int delayTime);

void setup() {
	pinMode(13, OUTPUT);
	initPinAssiment(outputPins, OUTPUT);
	initPinAssiment(inputPins, INPUT);
	Serial.begin(9600);
	menu();
}

void loop() {
	command = Serial.read();

	selector();

	//動作確認用のLチカ
	flashLED(13, 100);
}

inline void flashLED(int pin, int delayTime) {
	byte s = ledState ? HIGH : LOW;
	digitalWrite(pin, s);
	ledState = !ledState;
	delay(delayTime);
}

