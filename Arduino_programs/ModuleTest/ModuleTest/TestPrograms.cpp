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
Program *motor = new Motor();
Program *uss = new Uss();
Program *ir = new Ir();
Program *encoder = new Encoder();
Program *mp3 = new Mp3();

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
		ir->Processor();
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
}

/*
以下クラスの実装
*/

void Program::Processor() {
	//共通部分であるwhile、menu()、commandを記述
	while (true)
	{
		//process()は純粋仮想関数で、このクラスには実装されていない
		process();
		break;
	}
	menu();
	command = NULL;
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

void Tape::process() {
	//ここに実装内容を書く
}

void Encoder::process() {
	//ここに実装内容を書く
}

void Mp3::process() {
	//ここに実装内容を書く
}