
/*
file   : L298N_omuni.h
Create : 2016/12/02
Author : R. Hirayama
Board  : Arduino Due
feture :
2つのL298Nで4個のモーターを制御します。
あらかじめ前後左右、左右斜め前・後ろ、左右旋回が簡単に出来る様になっています。
setupMotor、driveMotor関数を直接使用することで、モーターを好きなように動かせます。
*/
#ifndef _L298N_OMUNI_h
#define _L298N_OMUNI_h

#include "Arduino.h"

class L298N_omuni
{
public:
	static const int MOTOR_N = 0;
	static const int MOTOR_S = 0;
	static const int MOTOR_E = 0;
	static const int MOTOR_W = 0;

	L298N_omuni(int A_ena, int A_in1, int A_in2, int A_in3, int A_in4, int A_enb,
		int B_ena, int B_in1, int B_in2, int B_in3, int B_in4, int B_enb);

	void forward(int speed, int delay_time);
	void backward(int speed, int delay_time);

	void right(int speed, int delay_time);
	void left(int speed, int delay_time);

	void rightForward(int speed, int delay_time);
	void leftForward(int speed, int delay_time);
	void rightBackward(int speed, int delay_time);
	void leftBackward(int speed, int delay_time);

	void turnRight(int speed, int delay_time);
	void turnLeft(int speed, int delay_time);

	void fullStop(int delay_time);

	void driveMotors(int speed);
	void driveMotor(int motor_index, int speed);
	void setupMotors(int state1, int state2, int state3, int state4, int state5, int state6, int state7, int state8);
	void setupMotor(int motor_index, int state1, int state2);

private:
	struct Motor;
	int _A_ena;
	int _A_in1;
	int _A_in2;
	int _A_in3;
	int _A_in4;
	int _A_enb;
	int _B_ena;
	int _B_in1;
	int _B_in2;
	int _B_in3;
	int _B_in4;
	int _B_enb;
};

static void L298N_omuni::setupMotors(int state1, int state2, int state3, int state4, int state5, int state6, int state7, int state8)
{
	L298N_omuni::setupMotor(this->MOTOR_N, state1, state2);
	L298N_omuni::setupMotor(this->MOTOR_S, state3, state4);
	L298N_omuni::setupMotor(this->MOTOR_E, state5, state6);
	L298N_omuni::setupMotor(this->MOTOR_W, state7, state8);
}

static void L298N_omuni::setupMotor(int motorIndex, int state1, int state2)
{
	digitalWrite(motors[motorIndex].in1, state1);
	digitalWrite(motors[motorIndex].in2, state2);
}

static void L298N_omuni::driveMotors(int speed)
{
	this->driveMotor(this->MOTOR_N, speed);
	this->driveMotor(this->MOTOR_S, speed);
	this->driveMotor(this->MOTOR_E, speed);
	this->driveMotor(this->MOTOR_W, speed);
}
static void L298N_omuni::driveMotor(int motorIndex, int speed)
{
	analogWrite(motors[motorIndex].pwm, speed);
}


#endif
