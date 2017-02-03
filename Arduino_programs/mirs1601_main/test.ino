void test_encoder() {
  long enc_n, enc_e, enc_s, enc_w;
  char str[100];

  while (1) {
    encoder_get(&enc_n, &enc_e, &enc_s, &enc_w);
    sprintf(str, "enc_n = %6ld , enc_e = %6ld , enc_s = %6ld , enc_w = %6ld\n", enc_n, enc_e, enc_s, enc_w);
    Serial.print(str);
    delay(T_CTRL);
  }
}

void test_distance() {
  double dist_n, dist_e, dist_s, dist_w;
  char str[100], str_n[10], str_e[10], str_s[10], str_w[10];

  while (1) {
    distance_get(&dist_n, &dist_s, &dist_e, &dist_w);
    sprintf(str_n, "%6.1f", dist_n);
    sprintf(str_e, "%6.1f", dist_e);
    sprintf(str_s, "%6.1f", dist_s);
    sprintf(str_w, "%6.1f", dist_w);
    sprintf(str, "dist_n = %s, dist_s = %s, dist_e = %s, dist_w = %s\n", str_n, str_s, str_e, str_w);
    Serial.print(str);
    delay(T_CTRL);
  }
}

void test_motor(int pwm_n, int pwm_s, int pwm_e, int pwm_w, byte state) {
  motor_set(pwm_n, pwm_s, pwm_e, pwm_w, state);
  while (1) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == 's') {
        motor_set(0, 0, 0, 0, B00000000);
        delay(100000000);
      }
    }
  }
}

void test_omuni_ctrl(omuni_state_t state, int pwm, int dist) {
  omuni_ctrl_set(state, pwm, dist);
  while (1) {
    omuni_ctrl_execute();
    if (Serial.available()) {
      char c = Serial.read();
      if (c == 's') {
        motor_set(0, 0, 0, 0, B00000000);
        delay(100000000);
      }
    }
  }
}

void test_sequence() {
  char c;
  int ret;

start:
  motor_set(0, 0, 0, 0, B00000000);

  while (1) {
    ret = cpu_com_read(&c);
    if (ret == 0) {
      break;
    }
    delay(2);
  }

  motor_set(0, 0, 100, 0, B10101010);
  delay(1000);

  switch (c) {
    case 'l':
      while (1) {
        motor_set(0, 0, 100, 100, B01100000);
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
      }
      break;

    case 'r':
      while (1) {
        motor_set(100, 100, 0, 0, B00001001);
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
      }
      break;
  }
}

void test_infrared() {
  Scheduler.startLoop( infrared_serial_task );
  while (1) {
    Serial.print("infrared_num: ");
    Serial.print(infrared_i);
    Serial.print(" data: ");
    Serial.println(infrared_data[infrared_i].val);
    delay(500);
  }
}
