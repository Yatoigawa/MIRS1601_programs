/*
各種テストプログラムがあるファイル

***テストプログラムの実装方法***
TestPrograms.inoに各テストプログラムのクラスがあります。
各クラスにprocessメソッドがあるので、中に処理内容を実装してください。
必要に応じてフィールドやメソッドを追加しても構いませんが、誤動作を防ぐためにも全てprivateで宣言してください。
*/
#include "Arduino.h"
#include "PinAssignment.h"

/*
各クラスの実装
TODO:クラスの実装
*/

class AbstructProgram
{
public:
	char keyCommand = NULL;

	//処理メソッド
	void Processor(char command)
	{
		//共通部分であるwhile、menu()を記述
		Serial.print(F("Test : "));
		Serial.println(command, HEX);
		Serial.println(F("COMMANDS:"));
		Serial.println(F("[e] Finish test"));
		this->testMenu();
		Serial.println(F("Please press any key to start"));
		while (Serial.available() == 0) {}
		Serial.flush();
		while (true)
		{
			keyCommand = Serial.read();
			if (keyCommand == 'e')
			{
				break;
			}
			else {
				//process()は純粋仮想関数で、このクラスには実装されていない
				this->process();
			}
			keyCommand = NULL;
		}
		menu();
	}

protected:
	//この関数をオーバーライドすることで、子クラス(各テストプログラム)によって処理を変えられる
	virtual void testMenu() = 0;
	virtual inline void process() = 0;
};

class Motor : public AbstructProgram
{
public:
	Motor() {};
	~Motor() {};

private:
	int timeDelay = 500;
	int speed = 150;

	void testMenu()
	{
		Serial.println(F("[8] forward"));
		Serial.println(F("[2] backward"));
		Serial.println(F("[6] right"));
		Serial.println(F("[4] left"));
		Serial.println(F("[9] rightForward"));
		Serial.println(F("[3] rightBackward"));
		Serial.println(F("[7] leftForward"));
		Serial.println(F("[1] leftBackward"));
		Serial.println(F("[*] turnRight"));
		Serial.println(F("[/] turnLeft"));
		Serial.println(F("[5] full stop"));
		Serial.println(F("[+] speed up"));
		Serial.println(F("[-] speed down"));
		Serial.println(F("Caution : Please use the numeric keypad"));
	}
	void process()
	{
		switch (keyCommand)
		{
			//テンキーでほとんどを操作
		case '8':
			Serial.println(F("forward"));
			omuni.forward(this->speed, timeDelay);
			break;
		case '2':
			Serial.println(F("backward"));
			omuni.backward(this->speed, timeDelay);
			break;
		case '6':
			Serial.println(F("right"));
			omuni.right(this->speed, timeDelay);
			break;
		case '4':
			Serial.println(F("left"));
			omuni.left(this->speed, timeDelay);
			break;
		case '9':
			Serial.println(F("rightForward"));
			omuni.rightForward(speed, timeDelay);
			break;
		case '3':
			Serial.println(F("rightBackward"));
			omuni.rightBackward(speed, timeDelay);
			break;
		case '7':
			Serial.println(F("leftForward"));
			omuni.leftForward(speed, timeDelay);
			break;
		case '1':
			Serial.println(F("leftBackward"));
			omuni.leftBackward(speed, timeDelay);
			break;
		case '*':
			Serial.println(F("turnRight"));
			omuni.turnRight(speed, timeDelay);
			break;
		case '/':
			Serial.println(F("turnLeft"));
			omuni.turnLeft(speed, timeDelay);
			break;
		case '5':
			Serial.println(F("full stop"));
			omuni.fullStop(timeDelay);
			break;
		case '+':
			this->speed += 10;
			this->isSafeSpeed();
			Serial.print(F("speed up: "));
			Serial.println(this->speed);
			break;
		case '-':
			this->speed -= 10;
			this->isSafeSpeed();
			Serial.print(F("speed down: "));
			Serial.println(this->speed);
			break;
		default:
			flashLED(13, 100);
			break;
		}
	}

	void isSafeSpeed() {
		if (this->speed > 225)
		{
			this->speed = 225;
		}
		if (this->speed < 0)
		{
			this->speed = 0;
		}
	}
};

class Uss : public AbstructProgram
{
public:
	Uss() {};
	~Uss() {};

private:
	long cm[4];

	void testMenu() {}
	void process()
	{
		for (int i = 0; i < sizeof(ussArray) / sizeof(ussArray[0]); i++)
		{
			this->cm[i] = ussArray[i].getCM();
		}
		Serial.print("N: ");
		Serial.print(cm[0]);
		Serial.print("cm E: ");
		Serial.print(cm[1]);
		Serial.print("cm S: ");
		Serial.print(cm[2]);
		Serial.print("cm W: ");
		Serial.print(cm[3]);
		Serial.println("cm");
		flashLED(13, 100);
	}
};

class Ir : public AbstructProgram
{
public:
	Ir() {};
	~Ir() {};

private:
	void testMenu()
	{

	}
	void process()
	{

	}
};

class Tape : public AbstructProgram
{
public:
	Tape() {};
	~Tape() {};

private:
	int count;

	void testMenu() {}
	void process()
	{
		this->count++;
		tapeLED.BlinkLED(this->count, 1000);
		flashLED(13, 1000);
		this->count = this->count >= 8 ? 0 : this->count;
	}
};

class Encoder : public AbstructProgram
{
public:
	Encoder() {};
	~Encoder() {};

private:
	void testMenu()
	{

	}
	void process()
	{

	}
};

class Mp3 : public AbstructProgram
{
public:
	Mp3() {};
	~Mp3() {};

private:
	void testMenu()
	{

	}
	void process()
	{

	}
};

//子クラスをインスタンス化
//これで新しいクラスができても変更が楽
AbstructProgram *pTests[6] = { new Motor, new Uss, new Ir,new Tape, new Encoder, new Mp3 };

void selector(char command) {
	//コマンドの文字によって子クラスのポインタを親クラスへ代入
	switch (command)
	{
	case 'm':
		pTests[0]->Processor(command);
		break;

	case 'u':
		pTests[1]->Processor(command);
		break;

	case 'i':
		pTests[2]->Processor(command);
		break;

	case 't':
		pTests[3]->Processor(command);
		break;

	case 'e':
		pTests[4]->Processor(command);
		break;

	case 'M':
		pTests[5]->Processor(command);
		break;

	default:
		//なにも処理しない
		break;
	}
}
