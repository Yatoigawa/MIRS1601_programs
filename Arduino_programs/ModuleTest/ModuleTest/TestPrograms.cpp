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
//これで新しいクラスができても変更が楽
Program *pTests[5] = { new Motor, new Uss, new Ir, new Encoder, new Mp3 };

void selector() {
	//コマンドの文字によって子クラスのポインタを親クラスへ代入
	switch (command)
	{
	case 'm':
		pTests[0]->Processor();
		break;

	case 'u':
		pTests[1]->Processor();
		break;

	case 'i':
		pTests[2]->Processor();
		break;

	case 't':
		pTests[3]->Processor();
		break;

	case 'e':
		pTests[4]->Processor();
		break;

	case 'M':
		pTests[5]->Processor();
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