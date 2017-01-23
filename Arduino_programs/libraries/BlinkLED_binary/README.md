# このライブラリについて
このクラスはピンを初期化し、0~8の数字をデコードして、各桁に対応する3bitのLEDを光らせます。

# 使用方法
最初にインスタンス化することで初期化されます。その後はメイン実行部でBlinkLEDを呼び出すことで光ります。  

# メンバー
## コンストラクタ
|コンストラクタ|説明|
|:------------|:--|
|BlinkLED_binary(int LED1, int LED2, int LED3)|LED1が1bit目、LED2が2bit目、LED3が3bit目に当たります。|

## メンバ関数
|修飾子と型|メンバ関数|説明|
|:--------|:--------|:---|
|void     |BlinkLED(int dec, int delayTime)|指定したLEDを指定した時間だけ光らせ、消えます。|

# 例
以下のコードは11,12番ピンのLEDを1秒間光らせるプログラムです。
```C++
#include <BlinkLED_binary.h>

BlinkLED_binary hoge = BlinkLED_binary(11, 12, 13);

void setup() {}

void loop() {
  hoge.BlinkLED(3, 1000);
}
```

# 機能拡張
4bit目以上を光らせたい場合は、  
BlinkLED_binary.hの
```C++
public:
  BlinkLED_binary(int LED1, int LED2, int LED3);
  ...
private:
  int _LED[3];
```
この部分のコンストラクタの引数と、配列メンバ変数の要素数を増やし、  
BlinkLED_binary.cppの
```C++
BlinkLED_binary::BlinkLED_binary(int LED1, int LED2, int LED3)
    : _LED{ LED1,LED2,LED3 }
```
この行の初期化子リスト```_LED```の要素を増やしてしてください。
