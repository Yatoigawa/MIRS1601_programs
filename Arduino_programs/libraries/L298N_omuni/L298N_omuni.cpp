/*
file   : L298N_omuni.cpp
Create : 2016/12/02
Author : R. Hirayama
Board  : Arduino Due
feture :
2つのL298Nで4個のモーターを制御します。
あらかじめ前後左右、左右斜め前・後ろ、左右旋回が簡単に出来る様になっています。
setupMotor、driveMotor関数を直接使用することで、モーターを好きなように動かせます。
*/
#include "Arduino.h"
#include "L298N_omuni.h"

L298N_omuni::L298N_omuni(int A_ena, int A_in1, int A_in2, int A_in3, int A_in4, int A_enb,
						 int B_ena, int B_in1, int B_in2, int B_in3, int B_in4, int B_enb)
	: _motors{	{ A_in1, A_in2, A_ena },
				{ A_in3, A_in4, A_enb },
				{ B_in1, B_in2, B_ena },
				{ B_in3, B_in4, B_enb } }
{
	pinMode(A_ena, OUTPUT);
	pinMode(A_in1, OUTPUT);
	pinMode(A_in2, OUTPUT);
	pinMode(A_in3, OUTPUT);
	pinMode(A_in4, OUTPUT);
	pinMode(A_enb, OUTPUT);

	pinMode(B_ena, OUTPUT);
	pinMode(B_in1, OUTPUT);
	pinMode(B_in2, OUTPUT);
	pinMode(B_in3, OUTPUT);
	pinMode(B_in4, OUTPUT);
	pinMode(B_enb, OUTPUT);
}

/*
北、東を正とする
NSEW
N_in1,N_in2,S_in1,S_in2,E_in1,E_in2,W_in1,W_in2
*/
void L298N_omuni::forward(int speed, int delay_time)
{
	this->setupMotors(B00001001);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::backward(int speed, int delay_time)
{
	this->setupMotors(B00000110);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::right(int speed, int delay_time)
{
	this->setupMotors(B10010000);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::left(int speed, int delay_time)
{
	this->setupMotors(B01100000);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::rightForward(int speed, int delay_time)
{
	this->setupMotors(B10011001);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::leftForward(int speed, int delay_time)
{
	this->setupMotors(B01101001);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::rightBackward(int speed, int delay_time)
{
	this->setupMotors(B10010110);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::leftBackward(int speed, int delay_time)
{
	this->setupMotors(B01100110);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::turnRight(int speed, int delay_time)
{
	this->setupMotors(B10010110);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::turnLeft(int speed, int delay_time)
{
	this->setupMotors(B01101001);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::fullStop(int delay_time)
{
	this->setupMotors(B00000000);
	this->driveMotors(0);
	delay(delay_time);
}

//引数に8ビットの二進数を入力　charをモータのHigh Low制御に割り当てた。
//0,1ビット目が北　2,3ビット目が南、4,5ビット目が東、6,7ビット目が西
void L298N_omuni::setupMotors(byte state)
{
	L298N_omuni::setupMotor(this->MOTOR_N, state & B00000001, state & B00000010);
	L298N_omuni::setupMotor(this->MOTOR_S, state & B00000100, state & B00001000);
	L298N_omuni::setupMotor(this->MOTOR_E, state & B00010000, state & B00100000);
	L298N_omuni::setupMotor(this->MOTOR_W, state & B01000000, state & B10000000);
}

void L298N_omuni::setupMotor(int motorIndex, int state1, int state2)
{
	digitalWrite(_motors[motorIndex].in1, state1);
	digitalWrite(_motors[motorIndex].in2, state2);
}

void L298N_omuni::driveMotors(int speed)
{
	this->driveMotor(this->MOTOR_N, speed);
	this->driveMotor(this->MOTOR_S, speed);
	this->driveMotor(this->MOTOR_E, speed);
	this->driveMotor(this->MOTOR_W, speed);
}
void L298N_omuni::driveMotor(int motorIndex, int speed)
{
	analogWrite(_motors[motorIndex].pwm, speed);
}
