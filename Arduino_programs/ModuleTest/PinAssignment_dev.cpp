/*
	�s���̏�����������cpp�t�@�C��
	�o�X��H�̃s���z�u�Ɋ�Â��Đݒ肵�Ă���̂Ńs���ԍ�������ɕς��Ȃ��ł�������
*/
#include "Arduino.h"
#include <map>
#include <string>
#include <iostream>
#include <utility>
#include "PinAssignment.h"

/*
�L�[��string�A�l��int��map
size���g��������map���g�p
�L�[���d�����������ꍇ��multimap���g�p���邱��(�񐄏�)
*/

extern std::map<std::string, int> pinOut;
extern std::map<std::string, int> pinIn;

void initPins() {
	//TODO:SPI�ʐM�p�̃s���̏�����
	//TODO:�s������K�؂Ȗ��O�ɕύX����
	//map�֗v�f����
	//MOTOR
	pinOut.insert("MTR_A1", 26);	//Digital
	pinOut["MTR_A2"] = 27;
	pinOut["MTR_A3"] = 28;
	pinOut["MTR_B1"] = 29;
	pinOut["MTR_B2"] = 30;
	pinOut["MTR_B3"] = 31;
	pinOut["P_N1"] = 2;		//PWM
	pinOut["P_N2"] = 3;
	pinOut["P_E1"] = 4;
	pinOut["P_E2"] = 5;
	pinOut["P_S1"] = 6;
	pinOut["P_S2"] = 7;
	pinOut["P_W1"] = 8;
	pinOut["P_W2"] = 9;

	//ENCODER
	pinOut["ENC_N1"] = 32;	//Digital
	pinOut["ENC_N2"] = 33;
	pinOut["ENC_E1"] = 34;
	pinOut["ENC_E2"] = 35;
	pinOut["ENC_S1"] = 36;
	pinOut["ENC_S2"] = 37;
	pinOut["ENC_W1"] = 38;
	pinOut["ENC_W2"] = 39;

	//USS
	pinOut["ENC_N"] = 40;		//Digital
	pinOut["ENC_E"] = 41;
	pinOut["ENC_S"] = 42;
	pinOut["ENC_W"] = 43;

	//INFRARED
	pinOut["IR"] = 22;		//CS

	//TAPELED
	pinOut["TL_0"] = 44;		//Digital
	pinOut["TL_1"] = 45;
	pinOut["TL_2"] = 46;

	//MP3_A,MP3_B
	pinOut["MP3_1"] = 23;		//CS
	pinOut["MP3_2"] = 24;
	pinOut["MP3_3"] = 25;

	//������
	for (auto itr = pinOut.begin(); itr != pinOut.end(); ++itr) {
		pinMode(itr->second, OUTPUT);
	}
}