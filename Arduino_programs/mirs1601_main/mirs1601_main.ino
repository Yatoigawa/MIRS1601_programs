#include "define.h"
#include <L298N_omuni.h>
#include <USS.h>
#include <Scheduler.h>

void setup() {
  encoder_open();
  cpu_open();
  infrared_open();
}

void loop() {
  //test_infrared();
  
  sequence_main();
  //sequence_mainer();
  //test_distance();
  //test_omuni_ctrl(OMN_SDE, 190, 400);
  //test_motor(0, 0, 255, 255, B10010110);
  //test_sequence();
}
