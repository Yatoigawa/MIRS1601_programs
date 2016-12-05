# このライブラリについて
このライブラリは4輪オムニホイールを制御します。  
機体を上から見て北、東をそれぞれ正としています。  
あらかじめ前後左右、左右斜め前・後ろ、左右旋回が簡単に出来る様になっています。  

# 使用方法
L298Nのデータシートを参考に、コンストラクタに左から順に北、南、東、西にあるモーターの適切なピン番号を入力して初期化してください。  
メイン実行部で各種メンバ関数を呼び出し、pwm値(speed)と回る時間(time_delay)[ms]を渡すことで、モーターを動かせます。  
fullStop関数を呼び出さないと回りっぱなしになるので注意してください。

```C++
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
```

# 発展
ライブラリ内部でモーターには北、南、東、西の順に0,1,2,3の数字が割り振られています。  
メンバ関数のsetupMotor、driveMotorを直接使用することで、モーターを個別に動かせます。
```C++
driver.setupMotor(1,LOW,HIGH);
driver.driveMotor(1,speed);
delay(time_delay);
```
この場合、南のモーターが正転します。
