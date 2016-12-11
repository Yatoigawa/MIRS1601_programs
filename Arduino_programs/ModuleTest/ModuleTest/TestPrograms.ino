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
			//process()は純粋仮想関数で、このクラスには実装されていない
			this->process();

			if (this->keyCommand == 'e')
			{
				break;
			}
			this->keyCommand = Serial.read();
		}
		this->keyCommand = NULL;
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

class WAV : public AbstructProgram
{
public:
	WAV() {};
	~WAV() {};

private:
	int numList = 0;

	void testMenu()
	{
		Serial.println(F("[s] Stop playing"));
		Serial.println(F("Caution : You can NOT use the [e] command during music playback"));
	}
	void process()
	{
		initPlayer();
		int count = 0;

	START:
		//選曲
		Serial.print(F("Please input a music name : "));
		while (Serial.available() == 0);
		String musicName = Serial.readString();
		Serial.println(musicName);
		File myFile = SD.open(musicName);
		if (!myFile) {
			Serial.println(F("error opening"));
			goto START;
		}

		const int S = 1024; // Number of samples to read in block
		short buffer[S];

		Serial.print(F("Playing"));
		// until the file is not finished
		while (myFile.available()) {
			// read from the file into buffer
			myFile.read(buffer, sizeof(buffer));

			// Prepare samples
			int volume = 1024;
			Audio.prepare(buffer, S, volume);
			// Feed samples to audio
			Audio.write(buffer, S);

			// Every 100 block print a '.'
			count++;
			if (count == 100) {
				Serial.print(F("."));
				count = 0;
			}

			//曲再生中のコマンド
			if (Serial.available() != 0)
			{
				if (Serial.read() == 's')
				{
					Serial.println(F("Stop playing"));
					break;
				}
				else if (Serial.read() == ' ')
				{
					Serial.println(F("Pause"));
					while (Serial.read() != ' ');
					Serial.println(F("Playing"));
				}
			}
		}
		myFile.close();
		Audio.end();
		Serial.println(F("End of file. Thank you for listening!"));
		Serial.println(F("Do you want to end the test?"));
		Serial.println(F("To exit, enter the [e] command"));
		Serial.println(F("Please press any key"));
		while (Serial.available() == 0);
		if (Serial.read() == 'e') { this->keyCommand = 'e'; }
		Serial.println(this->keyCommand);
		delay(500);
	}

	void initPlayer() {
		//オーディオ初期化
		//サンプルレート88200bps, バッファ100ms
		Audio.begin(88200, 100);

		//ミュージックリスト表示
		File root = SD.open("/");
		printDirectory(root);
		Serial.print(F("Number of the music : "));
		Serial.println(this->numList);
		root.close();
	}

	//ファイルを一覧表示
	void printDirectory(File dir) {
		this->numList = 0;
		while (true) {
			File entry = dir.openNextFile();
			if (!entry) {
				// no more files
				break;
			}
			this->numList++;
			Serial.println(entry.name());
			entry.close();
		}
	}
};

//子クラスをインスタンス化
//これで新しいクラスができても変更が楽
AbstructProgram *pTests[6] = { new Motor, new Uss, new Ir,new Tape, new Encoder, new WAV };

//テスト内容を選択
void selector(char command) {
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
