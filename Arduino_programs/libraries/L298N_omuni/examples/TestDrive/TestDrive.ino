#include <L298N_omuni.h>
const int A_ENA = 13;
const int A_IN1 = 12;
const int A_IN2 = 11;
const int A_IN3 = 10;
const int A_IN4 = 9;
const int A_ENB = 8;

const int B_ENA = 7;
const int B_IN1 = 6;
const int B_IN2 = 5;
const int B_IN3 = 4;
const int B_IN4 = 3;
const int B_ENB = 2;
L298N_omuni driver(A_ENA,A_IN1,A_IN2,A_IN3,A_IN4,B_ENB,B_ENA,B_IN1,B_IN2,B_IN3,B_IN4,B_ENB); 
int time_delay = 500;
int speed = 150;
void setup()
{
}

void loop()
{
  driver.forward(speed,time_delay);
  driver.fullStop(time_delay);
  driver.turnRight(speed,time_delay);
  driver.fullStop(time_delay);
  driver.turnLeft(speed,time_delay);
  driver.fullStop(time_delay);
  driver.backward(speed,time_delay);
  driver.fullStop(time_delay);
  driver.rightForward(speed,time_delay);
  driver.fullStop(time_delay);
  driver.leftForward(speed,time_delay);
  driver.fullStop(time_delay);
  driver.rightBackward(speed,time_delay);
  driver.fullStop(time_delay);
  driver.leftBackward(speed,time_delay);
}
