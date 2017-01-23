
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

class L298N_omuni {
public:
	L298N_omuni(
		int A_ena, int A_in1, int A_in2, int A_in3, int A_in4, int A_enb,
		int B_ena, int B_in1, int B_in2, int B_in3, int B_in4, int B_enb);

	L298N_omuni(const int (&motor_driver_A)[6], const int (&motor_driver_B)[6]);

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
	void setupMotors(byte state);
	void setupMotor(int motor_index, int state1, int state2);

private:
	static const int MOTOR_N = 0;
	static const int MOTOR_S = 1;
	static const int MOTOR_E = 2;
	static const int MOTOR_W = 3;
	
	static const byte Bforward = B00001001;
	static const byte Bbackward = B00000110;
	static const byte Bright = B01100000;
	static const byte Bleft = B10010000;
	static const byte BrightForward = B01101001;
	static const byte BleftForward = B10011001;
	static const byte BrightBackward = B01100110;
	static const byte BleftBackward = B10010110;
	
	struct Motor {
		int in1;
		int in2;
		int pwm;
	};

	const L298N_omuni::Motor _motors[4];
};

#endif
