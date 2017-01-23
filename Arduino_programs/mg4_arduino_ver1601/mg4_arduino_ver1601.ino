#include "define.h"

void setup() {
  encoder_open();
  motor_open();
  cpu_open();
  infrared_open();
}

void loop() {
  mirsak_main();

  //test_encoder();
  //test_distance();

  //test_motor(0, 0);

  //test_vel_ctrl(25, 25);

  //test_run_ctrl(STR, 25, 100);
  //test_run_ctrl(ROT, 45, 90);

  //test_batt();

  //test_decode();
}

