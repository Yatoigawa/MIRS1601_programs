#include <Scheduler.h>

void setup() {
  Serial.begin(9600);

  // スケジューラ
  Scheduler.startLoop(loop2);
  delay(1000);
  Scheduler.startLoop(loop3);
  delay(1000);
}

void loop() {
  Serial.println("loop is starting");
  delay(100000000);
}

void loop2(){
  Serial.println("loop2 is starting");
  delay(100000000);
}

void loop3(){
  Serial.println("loop3 is starting");
  delay(100000000);
}
