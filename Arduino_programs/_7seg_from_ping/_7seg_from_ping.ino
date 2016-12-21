#define SERIAL_SPEED      9600

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

void setup() {
  Serial.begin(SERIAL_SPEED);
  for (i = 0; i < 7; i++) {
    pinMode(output_pins_one[i], OUTPUT);
    pinMode(output_pins_ten[i], OUTPUT);
  }
}

void loop() {
  uint8_t data;
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
