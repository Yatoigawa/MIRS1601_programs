#define SERIAL_SPEED      9600
#define PING_PIN 7
#define HIGH_LOW_JUDGE(n) ((n == 1) ? HIGH : LOW)

const int output_pins_one[7] = {53, 50, 49, 46 , 45, 42, 41};
const int output_pins_ten[7] = {35, 32, 31, 28, 27, 24, 23};

const int svn_segment_array[10][7] = {    // 7seg表示用配列
  {1, 1, 1, 1, 1, 1, 0},      // 0
  {0, 1, 1, 0, 0, 0, 0},      // 1
  {1, 1, 0, 1, 1, 0, 1},      // 2
  {1, 1, 1, 1, 0, 0, 1},      // 3
  {0, 1, 1, 0, 0, 1, 1},      // 4
  {1, 0, 1, 1, 0, 1, 1},      // 5
  {1, 0, 1, 1, 1, 1, 1},      // 6
  {1, 1, 1, 0, 0, 0, 0},      // 7
  {1, 1, 1, 1, 1, 1, 1},      // 8
  {1, 1, 1, 1, 0, 1, 1}       // 9
};

int i;
long microsecondsToCentimeters(long microseconds);

void setup() {
  Serial.begin(SERIAL_SPEED);
  for (i = 0; i < 7; i++) {
    pinMode(output_pins_one[i], OUTPUT);
    pinMode(output_pins_ten[i], OUTPUT);
  }
}

void loop() {
  uint8_t data;
  /*
    テスト用:  Arduino Dueは3V3動作の為PING)))の動作が不安定
    //long duration;

    // PING)))による距離計測ルーチン
    pinMode(PING_PIN, OUTPUT);
    digitalWrite(PING_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(PING_PIN, HIGH);
    delayMicroseconds(5);
    digitalWrite(PING_PIN, LOW);

    pinMode(PING_PIN, INPUT);
    duration = pulseIn(PING_PIN, HIGH);
    data = microsecondsToCentimeters(duration);
  */
  if (Serial.available() > 0) {
    data = Serial.read();
    if (data < 100) {
      for (i = 0; i < 7; i++) {
        digitalWrite(output_pins_one[i], svn_segment_array[ (data % 10) ][i] );
        digitalWrite(output_pins_ten[i], svn_segment_array[ (data / 10) ][i] );
      }
    }
  }
  else {
    for (i = 0; i < 7; i++) {
      digitalWrite(output_pins_one[i], LOW);
      digitalWrite(output_pins_ten[i], LOW);
    }
  }
  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
