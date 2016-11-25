/*
各種テストプログラムがあるファイル
*/
#include "Arduino.h"
#include "TestPrograms.h"
#include "PinAssignment.h"
#include "SerialFunction.h"

char command = NULL;
bool checkTestFinished = true;

//子クラスをインスタンス化
Program *motor = new Motor;
Program *uss = new Uss;
Program *ir = new Ir;
Program *tape = new Tape;
Program *encoder = new Encoder;
Program *mp3 = new Mp3;

void selector() {
	//コマンドの文字によって子クラスのポインタを親クラスへ代入
	switch (command)
	{
	case 'm':
		motor->Processor();
		break;

	case 'u':
		uss->Processor();
		break;

	case 'i':
		ir->Processor();
		break;

	case 't':
		tape->Processor();
		break;

	case 'e':
		encoder->Processor();
		break;

	case 'M':
		mp3->Processor();
		break;

	default:
		//なにも処理しない
		break;
	}
	command = NULL;
}

/*
以下クラスの実装
*/

void Program::Processor() {
	//共通部分であるwhile、menu()、commandを記述
	while (true)
	{
		readSerialEnd();
		if (true)
		{
			goto END;
		}
		else {
			//process()は純粋仮想関数で、このクラスには実装されていない
			process();
		}
	}
	END:
	menu();
}

void Program::readSerialEnd() {
	if (Serial.read() == 'e') {
		isEnd = false;
	}
}

/*
各テストプログラムの実装
TODO:クラスの実装
*/

void Motor::process() {
	//ここに実装内容を書く
}

void Uss::process() {
	//ここに実装内容を書く
}

void Ir::process() {
	//ここに実装内容を書く
}

//TapeLEDは3bitの信号をデコードする
void Tape::process() {
	for (counter = 8; counter < 0; counter++)
	{
		byte b = (byte)counter % 2;
		digitalWrite(TL_0,b);
		counter = counter;
	}
}

void Encoder::process() {
	//ここに実装内容を書く
}

void Mp3::process() {
	//ここに実装内容を書く
}