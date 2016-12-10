/*
メインプログラム
テストボードごとに書き換えるのは面倒なのでシリアル通信でテスト内容を変更する
*/
#include "PinAssignment.h"
#include <L298N_omuni\L298N_omuni.h>
#include <BlinkLED_binary\BlinkLED_binary.h>
#include <USS\USS.h>

//変数定義
//ピン名を配列に入れる(初期化関数で使うため)
//TODO:全てのピンを適切な配列に入れる(面倒)
//const int outputPins[] = { {} };
//const int inputPins[] = { {} };

L298N_omuni omuni = L298N_omuni(MTR_1ENA, MTR_N1, MTR_N2, MTR_S1, MTR_S2, MTR_1ENB,
								MTR_2ENA, MTR_E1, MTR_E2, MTR_W1, MTR_W2, MTR_2ENB);
USS ussArray[4] = { USS(USS_N),USS(USS_S),USS(USS_E),USS(USS_W) };
BlinkLED_binary tapeLED = BlinkLED_binary(TL_0, TL_1, TL_2);

bool checkTestFinished = true;
bool ledState = true;

//プロトタイプ宣言
void flashLED(int pin, int delayTime);

void setup() {
	pinMode(13, OUTPUT);
	//initPinAssiment(outputPins, OUTPUT);
	//initPinAssiment(inputPins, INPUT);
	Serial.begin(9600);
	menu();
}

void loop() {
	char command = Serial.read();

	selector(command);

	//動作確認用のLチカ
	flashLED(13, 100);
}

inline void flashLED(int pin, int delayTime) {
	byte s = ledState ? HIGH : LOW;
	digitalWrite(pin, s);
	ledState = !ledState;
	delay(delayTime);
}

