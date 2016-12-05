# このライブラリについて
このライブラリは0~8の数字をエンコードし、3bitの2進数にした後、各桁に対応する3bitのLEDを光らせます。

# 使用方法
```C++
#include <BlinkLED_binary.h>

BlinkLED_binary TapeLED(11, 12, 13);
```
このソースコードの場合、11ピンが1bit目、12ピンが2bit目、13ピンが3bit目です。
```C++
void loop()
{
  TapeLED.BlinkLED(3,1000);
}
```
10進数の数字と、光る時間を渡します。  
この場合、10進数の3は2進数では011なので、11,12ピンが1秒間点灯します。

# 機能拡張
4bit目以上を光らせたい場合は、  
BlinkLED_binary.hの
```C++
BlinkLED_binary(int LED1, int LED2, int LED3);

int _LED[3];
```
ここのコンストラクタの引数と、配列メンバ変数の要素数を増やし、  
BlinkLED_binary.cppの
```C++
BlinkLED_binary::BlinkLED_binary(int LED1, int LED2, int LED3) : _LED{ LED1,LED2,LED3 }
```
この行の初期化子リスト```_LED```の要素数を増やしてしてください。
