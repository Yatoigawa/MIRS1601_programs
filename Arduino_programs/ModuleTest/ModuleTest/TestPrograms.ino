/*
各種テストプログラムがあるファイル
*/
#include "Arduino.h"
#include "PinAssignment.h"

/*
各クラスの実装
TODO:クラスの実装
*/

class Program
{
public:
	//処理メソッド
	void Processor()
	{
		//共通部分であるwhile、menu()、commandを記述
		while (true)
		{
			readSerialEnd();
			if (isEnd)
			{
				goto END;
			}
			else {
				//process()は純粋仮想関数で、このクラスには実装されていない
				process();
			}
		}
	END:
		isEnd = false;
		menu();
	}
	void readSerialEnd()
	{
		if (Serial.read() == 'e') {
			isEnd = true;
		}
	}

protected:
	//この関数をオーバーライドすることで、子クラス(各テストプログラム)によって処理を変えられる
	virtual void process() = 0;

private:
	bool isEnd = false;
};

class Motor : public Program
{
public:
	Motor() {};
	void process()
	{

	}
};

class Uss : public Program
{
public:
	Uss() {};
	void process()
	{

	}
};

class Ir : public Program
{
public:
	Ir() {};
	void process()
	{

	}
};

class Tape : public Program
{
public:
	int counter;

	Tape() {};
	void process()
	{

	}
};

class Encoder : public Program
{
public:
	Encoder() {};
	void process()
	{

	}
};

class Mp3 : public Program
{
public:
	Mp3() {};
	void process()
	{

	}
};

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
