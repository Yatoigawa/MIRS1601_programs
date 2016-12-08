#include "define.h"

void setup() {
  io_open();
  encoder_open();
  motor_open();
  raspi_open();
}

void loop() {
  slave();

  //test_encoder();
  //test_distance();

  //test_motor(0, 0);

  //test_vel_ctrl(25, 25);

  //test_run_ctrl(STR, 25, 100);
  //test_run_ctrl(ROT, 45, 90);

  //test_batt();

  //test_decode();
}

