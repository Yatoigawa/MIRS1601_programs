/*
 *  ping_test.ino
 *  created : 2016/10/20
 *  
 *  Arduino.ccのサンプルプログラム
 *  https://www.arduino.cc/en/Tutorial/Ping
 *  
 */


// デジタルPINで取得可能
#define PING_PIN 7

void setup() {
  Serial.begin(9600);
}

// プロトタイプ宣言
long microsecondsToCentimeters(long microseconds);

void loop() {
  long duration, cm;

  // PING)))による距離計測ルーチン
  pinMode(PING_PIN, OUTPUT);
  digitalWrite(PING_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(PING_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(PING_PIN, LOW);

  pinMode(PING_PIN, INPUT);
  duration = pulseIn(PING_PIN, HIGH);
  cm = microsecondsToCentimeters(duration);
  
  // cmで表示
  Serial.print(cm);
  Serial.println("cm");
  delay(100);
}

long microsecondsToCentimeters(long microseconds){
  // 
  return microseconds / 29 / 2;
}

