/*
attention :
このプログラムはArduinoDueでしか動作しません。

file   : USS.cpp
Create : 2016/12/05
Author : R. Hirayama
Board  : Arduino Due

feture :
超音波センサ1個分のクラスです。
Arduino DUEに合わせて高速化しています。
*/
#include "Arduino.h"
#include "USS.h"

USS::USS(int pin)
{
	this->pin = pin;
}