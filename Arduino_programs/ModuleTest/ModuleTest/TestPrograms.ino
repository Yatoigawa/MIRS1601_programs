/*
各種テストプログラムがあるファイル

***テストプログラムの実装方法***
TestPrograms.inoに各テストプログラムのクラスがあります。
各クラスにprocessメソッドがあるので、中に処理内容を実装してください。
必要に応じてフィールドやメソッドを追加しても構いませんが、誤動作を防ぐためにも全てprivateで宣言してください。
*/
#include "Arduino.h"
#include "PinAssignment.h"
#include <L298N.h>

/*
各クラスの実装
TODO:クラスの実装
*/

class AbstructProgram
{
public:
	char keyCommand = NULL;

	//処理メソッド
	void Processor()
	{
		//共通部分であるwhile、menu()を記述
		Serial.print(F("Test : "));
		Serial.println(command, HEX);
		Serial.println(F("COMMANDS:"));
		Serial.println(F("[e] Finish test"));
		testMenu();
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
				process();
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
		Serial.println(F("[f] forward"));
		Serial.println(F("[b] backward"));
		Serial.println(F("[r] turn right"));
		Serial.println(F("[l] turn left"));
		Serial.println(F("[s] full stop"));
		Serial.println(F("[+] speed up"));
		Serial.println(F("[-] speed down"));
	}
	void process()
	{
		switch (keyCommand)
		{
		case 'f':
			Serial.println(F("forward"));
			driver1.forward(speed,timeDelay);
			break;
		case 'b':
			Serial.println(F("backward"));
			driver1.backward(speed,timeDelay);
			break;
		case 'r':
			Serial.println(F("turn right"));
			driver1.turn_right(speed, timeDelay);
			break;
		case 'l':
			Serial.println(F("turn left"));
			driver1.turn_left(speed, timeDelay);
			break;
		case 's':
			Serial.println(F("full stop"));
			driver1.full_stop(timeDelay);
			break;
		case '+':
			speed += 10;
			Serial.print(F("speed up: "));
			Serial.println(speed);
			break;
		case '-':
			speed -= 10;
			Serial.print(F("speed down: "));
			Serial.println(speed);
			break;
		default:
			flashLED(13, 100);
			break;
		}
	}
};

class Uss : public AbstructProgram
{
public:
	Uss() {};
	~Uss() {};

private:
	long duration;
	long cm[4];
	int ussPins[4] = { USS_N, USS_E, USS_S, USS_W };

	void testMenu() {}
	void process()
	{
		// PING)))による距離計測ルーチン
		for (int i = 0; i < sizeof(ussPins) / sizeof(ussPins[0]); ++i)
		{
			pinMode(ussPins[i], OUTPUT);
			digitalWrite(ussPins[i], LOW);
			delayMicroseconds(2);
			digitalWrite(ussPins[i], HIGH);
			delayMicroseconds(5);
			digitalWrite(ussPins[i], LOW);

			pinMode(ussPins[i], INPUT);
			duration = pulseIn(ussPins[i], HIGH);
			cm[i] = microsecondsToCentimeters(duration);
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
	inline long microsecondsToCentimeters(long microseconds) {
		//return microseconds / 29 / 2
		return microseconds * 0.03448275862069 * 0.5;
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
	int tlPins[3] = { TL_0,TL_1,TL_2 };

	void testMenu() {}
	void process()
	{
		count++;
		ledFlashBinary();
		flashLED(13, 1000);
		count = count >= 8 ? 0 : count;
	}
	inline void ledFlashBinary()
	{
		int i, j;
		byte state;
		for (i = 0, j = 1; i < sizeof(tlPins) / sizeof(tlPins[0]); i++, j = j * 2)
		{
			//この()は重要。ないと挙動がおかしくなる。
			state = (count & j) > 0 ? HIGH : LOW;
			digitalWrite(tlPins[i], state);
		}
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
