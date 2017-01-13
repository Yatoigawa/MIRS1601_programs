#include <Scheduler.h>

typedef union {
  uint16_t val;
  struct {
    uint8_t lsb;
    uint8_t msb;
  };
} infrared_data_t;

const int BAUDRATE = 115200;

infrared_data_t data;
int i = 0;

void setup() {
  Serial.begin(BAUDRATE);
  Serial2.begin(BAUDRATE);
  Scheduler.startLoop( serial_task );
}

void loop() {
  Serial2.write(i + 0x80);
  Serial.print("count bef: ");
  Serial.print(i);
  delay(50);
  if (data.val > 0) {
    Serial.print(" count aft: ");
    Serial.print(i);
    Serial.print(" data: ");
    Serial.print(data.val, DEC);
  }
  Serial.println("");
//  i++;
//  if (i > 7) {
//    i = 0;
//  }
  delay(200);
}

void serial_task() {
  if (Serial2.available() > 2) {
    if (Serial2.read() == 0xA4) {
      data.msb = (Serial2.read() /* & 0x0F */);
      data.lsb =  Serial2.read();
    }
  }
  delay(10);
  yield();
}

