/*
メインプログラム
テストボードごとに書き換えるのは面倒なのでシリアル通信でテスト内容を変更する
*/
#include "PinAssignment.h"
#include <L298N_omuni.h>
#include <BlinkLED_binary.h>
#include <USS.h>
#include <Encoder.h>
#include <SD.h>
#include <SPI.h>
#include <Audio.h>
#include <string>

//変数定義
//ピン名を配列に入れる(初期化関数で使うため)
//TODO:全てのピンを適切な配列に入れる(面倒)
//const int outputPins[] = { {} };
//const int inputPins[] = { {} };

L298N_omuni omuni = L298N_omuni(MTR_1ENA, MTR_N1, MTR_N2, MTR_S1, MTR_S2, MTR_1ENB,
								MTR_2ENA, MTR_E1, MTR_E2, MTR_W1, MTR_W2, MTR_2ENB);
Encoder encoder_array[4] = { Encoder(ENC_N1, ENC_N2),Encoder(ENC_S1, ENC_S2), Encoder(ENC_E1,ENC_E2), Encoder(ENC_W1,ENC_W2) };
BlinkLED_binary tapeLED = BlinkLED_binary(TL_0, TL_1, TL_2);
USS ussArray[4] = { USS(USS_N),USS(USS_S),USS(USS_E),USS(USS_W) };

bool ledState = true;

//プロトタイプ宣言
void flashLED(int pin, int delayTime);

void setup() {
	pinMode(13, OUTPUT);
	//initPinAssiment(outputPins, OUTPUT);
	//initPinAssiment(inputPins, INPUT);

	Serial.begin(9600);

	//SDカード初期化
	Serial.print(F("Initializing SD card..."));
	String m = SD.begin(4) ? "done." : "failed!\n********************\nDO NOT RUN THE [WMV Player]\n********************";
	Serial.println(m);

	menu();
}

void loop() {
	char command = Serial.read();

	selector(command);

	//動作確認用のLチカ
	flashLED(13, 100);
}

void menu() {
	Serial.println(F("Module Circuit Test Program"));
	Serial.println(F("COMMANDS:"));
	Serial.println(F("[m] Motor"));
	Serial.println(F("[e] Encoder"));
	Serial.println(F("[w] WMV Player"));
	Serial.println(F("[t] Tape LED"));
	Serial.println(F("[i] Infrared sensor"));
	Serial.println(F("[u] Ultrasonic sensor"));
	Serial.flush();
}

inline void flashLED(int pin, int delayTime) {
	byte s = ledState ? HIGH : LOW;
	digitalWrite(pin, s);
	ledState = !ledState;
	delay(delayTime);
}