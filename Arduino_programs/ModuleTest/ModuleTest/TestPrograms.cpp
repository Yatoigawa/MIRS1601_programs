/*
�e��e�X�g�v���O����������t�@�C��
*/
#include "Arduino.h"
#include "TestPrograms.h"
#include "PinAssignment.h"
#include "SerialFunction.h"

char command = NULL;
bool checkTestFinished = true;

//�q�N���X���C���X�^���X��
//����ŐV�����N���X���ł��Ă��ύX���y
Program *pTests[5] = { new Motor, new Uss, new Ir, new Encoder, new Mp3 };

void selector() {
	//�R�}���h�̕����ɂ���Ďq�N���X�̃|�C���^��e�N���X�֑��
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
		//�Ȃɂ��������Ȃ�
		break;
	}
	command = NULL;
}

/*
�ȉ��N���X�̎���
*/

void Program::Processor() {
	//���ʕ����ł���while�Amenu()�Acommand���L�q
	while (true)
	{
		readSerialEnd();
		if (true)
		{
			goto END;
		}
		else {
			//process()�͏������z�֐��ŁA���̃N���X�ɂ͎�������Ă��Ȃ�
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
�e�e�X�g�v���O�����̎���
TODO:�N���X�̎���
*/

void Motor::process() {
	//�����Ɏ������e������
}

void Uss::process() {
	//�����Ɏ������e������
}

void Ir::process() {
	//�����Ɏ������e������
}

//TapeLED��3bit�̐M�����f�R�[�h����
void Tape::process() {
	for (counter = 8; counter < 0; counter++)
	{
		byte b = (byte)counter % 2;
		digitalWrite(TL_0,b);
		counter = counter;
	}
}

void Encoder::process() {
	//�����Ɏ������e������
}

void Mp3::process() {
	//�����Ɏ������e������
}