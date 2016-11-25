/*
	メインプログラム
	テストボードごとに書き換えるのは面倒なのでシリアル通信でテスト内容を変更する
	文字化けするのでTeraTermでの通信を推奨
	This program was written by Visual Studio 2015
*/
#include "TestPrograms.h"
#include "PinAssignment.h"
#include "SerialFunction.h"
#include <string>

bool ledState = true;

//プロトタイプ宣言
void flashLED(int pin, int delayTime);

//これで新しいクラスができても変更が楽
//Program *pTests[5] = { new Motor, new Uss, new Ir, new Encoder, new Mp3 };

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

void flashLED(int pin, int delayTime) {
	byte s = ledState ? HIGH : LOW;
	digitalWrite(pin, s);
	ledState = !ledState;
	delay(delayTime);
}

