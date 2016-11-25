#ifndef _TESTPROGRAMS_h
#define _TESTPROGRAMS_h

#include "Arduino.h"

extern char command;

void selector();

/*
�e�e�X�g�v���O������Program�N���X���p������
�f�U�C���p�^�[���̈�ł���e���v���[�g���\�b�h�p�^�[����������Ă���
C++��template�Ƃ͈Ⴄ�̂Œ���
*/

//�C���X�^���X�����Ȃ��悤��
class Program
{
public:
	boolean *isEnd = false;

	void Processor();	//�������\�b�h
	void readSerialEnd();

	//���̊֐����I�[�o�[���C�h���邱�ƂŁA�q�N���X(�e�e�X�g�v���O����)�ɂ���ď�����ς�����
	virtual void process() = 0;
};

class Motor : public Program
{
public:
	Motor() {};
	void process();
};

class Uss : public Program
{
public:
	Uss() {};
	void process();
};

class Ir : public Program
{
public:
	Ir() {};
	void process();
};

class Tape : public Program
{
public:
	int counter;

	Tape() {};
	void process();
};

class Encoder : public Program
{
public:
	Encoder() {};
	void process();
};

class Mp3 : public Program
{
public:
	Mp3() {};
	void process();
};
#endif