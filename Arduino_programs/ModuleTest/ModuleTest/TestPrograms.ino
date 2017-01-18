#include "Arduino.h"
#include "PinAssignment.h"

//各種テストプログラムがあるファイル
//
//***テストプログラムの実装方法***
//TestPrograms.inoに各テストプログラムのクラスがあります。
//各クラスにprocessメソッドがあるので、中に処理内容を実装してください。
//必要に応じてフィールドやメソッドを追加しても構いませんが、誤動作を防ぐためにも全てprivateで宣言してください。

class AbstructProgram {
public:
	//処理メソッド
	void Processor(char& command) {
		//メニュー表示
		Serial.print(F("Test : "));
		Serial.println(command, HEX);
		Serial.println(F("COMMANDS:"));
		Serial.println(F("[e] Finish test"));
		this->testMenu();

		Serial.println(F("Please press any key to start"));
		while (Serial.available() == 0);

		while (true) {
			//process()は純粋仮想関数で、このクラスには実装されていない
			this->process();

			if (this->key_command == 'e') break;
			this->key_command = Serial.read();
		}
		this->key_command = NULL;
		menu();
	}

protected:
	char key_command = NULL;

	//この関数をオーバーライドすることで、子クラス(各テストプログラム)によって処理を変えられる
	virtual void testMenu() = 0;
	virtual inline void process() = 0;
};

class Motor : public AbstructProgram {
public:
	Motor() {};
	~Motor() {};

private:
	int timeDelay = 500;	//ms
	int speed = 150;	//0~225
	char key_command_old;

	void testMenu() {
		Serial.println(F("[8] forward"));
		Serial.println(F("[2] backward"));
		Serial.println(F("[6] right"));
		Serial.println(F("[4] left"));
		Serial.println(F("[9] rightForward"));
		Serial.println(F("[3] rightBackward"));
		Serial.println(F("[7] leftForward"));
		Serial.println(F("[1] leftBackward"));
		Serial.println(F("[5] full stop"));
		Serial.println(F("[+] speed up"));
		Serial.println(F("[-] speed down"));
		Serial.println(F("Caution : Please use the numeric keypad"));
	}

	void process() {
		if (this->key_command != NULL) {
			branchOrder(this->key_command);
		}
		if (this->key_command == '+' || this->key_command == '-') {
			if (this->key_command == '+') {
				this->speed += 10;
				Serial.print(F("speed up: "));
			}
			else if (this->key_command == '-') {
				this->speed -= 10;
				Serial.print(F("speed down: "));
			}
			this->isSafeSpeed();
			Serial.println(this->speed);
			branchOrder(this->key_command_old);
		}
		flashLED(13, 100);
	}

	void isSafeSpeed() {
		if (this->speed > 225) {
			this->speed = 225;
		}
		if (this->speed < 0) {
			this->speed = 0;
		}
	}

	void branchOrder(char key_command) {
		switch (key_command) {
			//テンキーで操作
			case '8':
				Serial.println(F("forward"));
				omuni.forward(this->speed, timeDelay);
				this->key_command_old = key_command;
				break;
			case '2':
				Serial.println(F("backward"));
				omuni.backward(this->speed, timeDelay);
				this->key_command_old = key_command;
				break;
			case '6':
				Serial.println(F("right"));
				omuni.right(this->speed, timeDelay);
				this->key_command_old = key_command;
				break;
			case '4':
				Serial.println(F("left"));
				omuni.left(this->speed, timeDelay);
				this->key_command_old = key_command;
				break;
			case '9':
				Serial.println(F("rightForward"));
				omuni.rightForward(this->speed, timeDelay);
				this->key_command_old = key_command;
				break;
			case '3':
				Serial.println(F("rightBackward"));
				omuni.rightBackward(this->speed, timeDelay);
				this->key_command_old = key_command;
				break;
			case '7':
				Serial.println(F("leftForward"));
				omuni.leftForward(this->speed, timeDelay);
				this->key_command_old = key_command;
				break;
			case '1':
				Serial.println(F("leftBackward"));
				omuni.leftBackward(this->speed, timeDelay);
				this->key_command_old = key_command;
				break;
			case '5':
				Serial.println(F("full stop"));
				omuni.fullStop(timeDelay);
				this->key_command_old = key_command;
				break;
			default:
				break;
		}
	}
};

class Uss : public AbstructProgram {
public:
	Uss() {};
	~Uss() {};

private:
	long cm[4];

	void testMenu() {}
	void process()
	{
		for (int i = 0; i < sizeof(ussArray) / sizeof(ussArray[0]); i++) {
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

//Ir素子の問題で使わなくなったため書かなくていい
class Ir : public AbstructProgram {
public:
	Ir() {};
	~Ir() {};

private:
	void testMenu() {}
	void process() {}
};

class Tape : public AbstructProgram {
public:
	Tape() {};
	~Tape() {};

private:
	int count;

	void testMenu() {}
	void process() {
		this->count++;
		tapeLED.BlinkLED(this->count, 1000);
		flashLED(13, 1000);
		this->count = this->count >= 8 ? 0 : this->count;
	}
};

class TestEnc : public AbstructProgram {
public:
	TestEnc() {};
	~TestEnc() {};

private:
	long old_position[4] = { -999 };
	long new_position[4] = {};

	void testMenu() {}
	void process() {
		for (int i = 0; sizeof(old_position) / sizeof(old_position[0]); i++) {
			new_position[i] = encoder_array[i].read();
			if (new_position[i] != old_position[0]) {
				old_position[i] = new_position[i];
			}
		}
		Serial.print("N: ");
		Serial.print(new_position[0]);
		Serial.print(" E: ");
		Serial.print(new_position[1]);
		Serial.print(" S: ");
		Serial.print(new_position[2]);
		Serial.print(" W: ");
		Serial.print(new_position[3]);
		Serial.println();
		flashLED(13, 100);
	}
};

class WAV : public AbstructProgram {
public:
	WAV() {};
	~WAV() {};

private:
	int numList = 0;
	String music_command;

	void testMenu() {
		Serial.println(F("[s] Stop playing"));
		Serial.println(F("Caution : You can NOT use the [e] command during music playback"));
	}

	void process() {
		initPlayerAndMusicSelect();

		File myFile = SD.open(this->music_command);
		//そもそも曲を再生するのか判断する
		if (this->music_command == "e") {
			Serial.println(F("To exit, enter the [e] command"));
			while (Serial.available() == 0);
			if (Serial.read() == 'e') this->key_command = 'e';
			if (myFile) myFile.close();	//万が一"e"というファイルが開けてしまった場合
		}
		//例外処理
		else if (!myFile) {
			Serial.println(F("error opening"));
		}
		else {
			playing(myFile);

			//再生終了時の処理
			myFile.close();
			Serial.println(F("End of file. Thank you for listening!"));
			Serial.println(F("Do you want to end the test?"));
			Serial.println(F("To exit, enter the [e] command"));
			Serial.println(F("Please press any key"));
			while (Serial.available() == 0);
			if (Serial.read() == 'e') this->key_command = 'e';
		}
		Audio.end();
		delay(500);
	}

	//music_commandが書き換わる
	void initPlayerAndMusicSelect() {
		//オーディオ初期化
		//サンプルレート88200bps, バッファ100ms
		Audio.begin(88200, 100);

		//ミュージックリスト表示
		File root = SD.open("/");
		printDirectory(root);
		Serial.print(F("Number of the music : "));
		Serial.println(this->numList);
		root.close();

		//選曲
		Serial.print(F("Please input a music name : "));
		while (Serial.available() == 0);
		this->music_command = Serial.readString();
		Serial.println(this->music_command);
	}

	//ファイルを一覧表示
	void printDirectory(File& root) {
		this->numList = 0;
		while (true) {
			File entry = root.openNextFile();
			if (!entry) break; // no more files
			this->numList++;
			Serial.println(entry.name());
			entry.close();
		}
	}

	//再生
	void playing(File& myFile) {
		int count = 0;

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
			if (Serial.available() != 0) {
				char c = Serial.read();
				if (c == 's') {
					Serial.println(F("Stop playing"));
					break;
				}
				else if (c == ' ') {
					Serial.println(F("Pause"));
					while (Serial.read() != ' ');
					Serial.println(F("Playing"));
				}
			}
		}
	}
};

//子クラスをインスタンス化
AbstructProgram *pTests[6] = { new Motor, new Uss, new Ir, new Tape, new TestEnc, new WAV };

//テスト内容を選択
void selector(char& command) {
	switch (command) {
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

		case 'w':
			pTests[5]->Processor(command);
			break;

		default:
			break;
	}
}