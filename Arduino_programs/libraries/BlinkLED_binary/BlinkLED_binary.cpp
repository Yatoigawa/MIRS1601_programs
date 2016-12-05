/*
file   : BlinkLED_binary.cpp
Create : 2016/12/02
Author : R. Hirayama
Board  : Arduino Due

feture :
0~8の数字を3bitの2進数にエンコードした後、各桁に対応するLEDを光らせます。
*/

#include "Arduino.h"
#include "BlinkLED_binary.h"

//初期化子リスト C++0x以降でないと使えない模様
BlinkLED_binary::BlinkLED_binary(int LED1, int LED2, int LED3) : _LED{ LED1,LED2,LED3 }
{
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
}