# このライブラリについて
このライブラリは4輪オムニホイールを制御します。  
機体を上から見て北、東をそれぞれ正としています。  
あらかじめ前後左右、左右斜め前・後ろ移動が簡単に出来る様になっています。  

# 使用方法
L298Nのデータシートを参考に、コンストラクタに左から順に北、南、東、西にあるモーターの適切なピン番号を入力することで初期化されます。  
メイン実行部で各種メンバ関数を呼び出すことで、モーターを動かせます。  
fullStop関数を呼び出さないと回りっぱなしになるので注意してください。

# メンバー
## コンストラクタ
|コンストラクタ|説明|
|:------------|:--|
|L298N_omuni(<br>int A_ena, int A_in1, int A_in2, int A_in3, int A_in4, int A_enb,<br>int B_ena, int B_in1, int B_in2, int B_in3, int B_in4, int B_enb)|A、Bがそれぞれモータードライバーです。データーシートを確認して、適切なピン番号を入れてください。|
|L298N_omuni(<br>const int (&motor_driver_A)[6], <br>const int (&motor_driver_B)[6])|上記のコンストラクタの引数が多かったため改善したものです。どちらを使っても動作に差し障りはありません。|

## メンバ関数
|修飾子と型|メンバ関数|説明|
|:--------|:--------|:---|
|void     |forward(int speed, int delay_time)|モーターを正転させます。speedにPWM値、delay_timeに最低限回す時間を入れてください。|
|void     |backward(int speed, int delay_time)|モーターを逆転させます。|
|void     |right(int speed, int delay_time);|モーターを右回転させます。|
|void     |left(int speed, int delay_time);|モーターを左回転させます。|
|void     |rightForward(int speed, int delay_time);|機体をを右斜め前へ移動させます。|
|void     |leftForward(int speed, int delay_time);|機体をを左斜め前へ移動させます。|
|void     |rightBackward(int speed, int delay_time);|機体をを右斜め後ろへ移動させます。|
|void     |leftBackward(int speed, int delay_time);|機体をを左斜め後ろへ移動させます。|
|void     |fullStop(int delay_time);|全モーターを停止させます。|
|void     |setupMotors(byte state)|setupMotorの便利関数です。全てのモーターのHigh,Lowを制御でき、0,1ビット目が北,2,3ビット目が南、4,5ビット目が東、6,7ビット目が西のモータに対応しています。|
|void     |setupMotor(int motorIndex, int state1, int state2)|モーターのHigh,Lowを制御できます。この関数を使わずにsetupMotorsの使用を推奨します。|
|void     |driveMotors(int speed)|driveMotorの便利関数です。全てのモーターをPWM制御します。|
|void     |driveMotor(int motorIndex, int speed)|モーターをPWM制御します。|

# 例
以下のコードは機体を0.5秒ごとに正転、逆転、停止を繰り返すプログラムです。
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

cosnt int[6] driverA = {A_ENA, A_IN1, A_IN2, A_IN3, A_IN4, A_ENB};
cosnt int[6] driverB = {B_ENA, B_IN1, B_IN2, B_IN3, B_IN4, B_ENB};

L298N_omuni driver = L208N_omuni(driverA, driverB);

int time_delay = 500;
int speed = 150;

void setup() {}

void loop() {
  driver.forward(speed,time_delay);
  driver.backward(speed, time_delay);
  driver.fullStop(time_delay);
}
```

# 機能拡張
メンバ関数のsetupMotors、driveMotorsを直接使用することで、モーターを自在に動かせます。

|Input|Function|
|:----|:-------|
|下位bit=1,上位bit=0|正転|
|下位bit=0,上位bit=1|逆転|
|下位bit=上位bit|停止|
```C++
driver.setupMotors(00000100);
driver.driveMotor(1,speed);
delay(time_delay);
```
この場合、南のモーターが逆転します。
