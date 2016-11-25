#ifndef _TESTPROGRAMS_h
#define _TESTPROGRAMS_h

#include "Arduino.h"

extern char command;

void selector();

/*
各テストプログラムはProgramクラスを継承する
デザインパターンの一つであるテンプレートメソッドパターンを取り入れている
C++のtemplateとは違うので注意
*/

//インスタンス化しないように
class Program
{
public:
	boolean *isEnd = false;

	void Processor();	//処理メソッド
	void readSerialEnd();

	//この関数をオーバーライドすることで、子クラス(各テストプログラム)によって処理を変えられる
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