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
    distance_get(&dist_n, &dist_e, &dist_s, &dist_w);
    sprintf(str, "dist_n = %s, dist_e = %s, dist_s = %s, dist_w = %s\n",
            sprintf(str_n, "%6, 1f", dist_n),
            sprintf(str_e, "%6, 1f", dist_e),
            sprintf(str_s, "%6, 1f", dist_s),
            sprintf(str_w, "%6, 1f", dist_w));
    Serial.print(str);
    delay(T_CTRL);
  }
}

//前後方向へ進むモータテスト（動くモーターは東と西）
void test_motor_fb(int pwm_e, int pwm_w) {
  motor_set(0, pwm_e, 0, pwm_w);
  while (1) {}
}


//左右方向へ進むモータテスト（動くモーターは北と南）
void test_motor_lr(int pwm_n, int pwm_s) {
  motor_set(pwm_n, 0, pwm_s, 0);
  while (1) {}
}

//全方向へ進むモーターテスト(引数4つで動くモーターを指定、引数の順番は　北　東　南　西)
void test_motor(int pwm_n, int pwm_e, int pwm_s, int pwm_w) {
  motor_set(pwm_n, pwm_e, pwm_s, pwm_w);
  while (1) {}
}


//前後方向へ進む速度テスト（動くモーターは東と西）
void test_vel_ctrl_fb(double vel_e, double vel_w) {
  int i = 0;
  char str[100], str_e[10], str_w[10];

  vel_ctrl_set(0, vel_e, 0, vel_w);

  while (1) {
    vel_ctrl_execute();
    if (i >= 10) {
      vel_ctrl_get(0, &vel_e, 0, &vel_w);
      sprintf(str, "vel_e = %s, vel_w = %s\n",
             sprintf(str_e, "%6, 1f", vel_e),
             sprintf(str_w, "%6, 1f", vel_w));
      Serial.print(str);
      i = 0;
    }
    i++;
    delay(T_CTRL);
  }
}

//左右方向へ進む速度テスト（動くモーターは北と南）
void test_vel_ctrl_lr(double vel_n, double vel_s) {
  int i = 0;
  char str[100], str_n[10], str_e[10],str_s[10], str_w[10];

  vel_ctrl_set(vel_n, 0, vel_s, 0);

  while (1) {
    vel_ctrl_execute();
    if (i >= 10) {
      vel_ctrl_get(&vel_n, 0, &vel_s, 0);
      sprintf(str, "vel_n = %s, vel_s = %s\n",
              sprintf(str_n, "%6, 1f", vel_n),
              sprintf(str_s, "%6, 1f", vel_s));
      Serial.print(str);
      i = 0;
    }
    i++;
    delay(T_CTRL);
  }
}

//全方向へ進む速度テスト（引数で動かしたいモーターに速度を入力する、引数の順番は　北　東　南　西）
void test_vel_ctrl_lr(double vel_n, double vel_e, double vel_s, double vel_w) {
  int i = 0;
  char str[100], str_n[10], str_e[10],str_s[10], str_w[10];

  vel_ctrl_set(vel_n, vel_e, vel_w, vel_s);

  while (1) {
    vel_ctrl_execute();
    if (i >= 10) {
      vel_ctrl_get(&vel_n, &vel_e, &vel_s, &vel_w);
      sprintf(str, "vel_n = %s, vel_e = %s, vel_s = %s\n, vel_w = %s\n",
              sprintf(str_n, "%6, 1f", vel_n),
              sprintf(str_e, "%6, 1f", vel_e),
              sprintf(str_s, "%6, 1f", vel_s),
              sprintf(str_w, "%6, 1f", vel_w));
      Serial.print(str);
      i = 0;
    }
    i++;
    delay(T_CTRL);
  }
}



void test_run_ctrl(run_state_t state, double speed, double dist) {
  int i = 0;
  char str[100], str_dist[10], str_speed[10];

  run_ctrl_set(state, speed, dist);

  while (1) {
    run_ctrl_execute();
    vel_ctrl_execute();
    if (i >= 10) {
      run_ctrl_get(&state, &speed, &dist);
      sprintf(str, "state = %s, speed = %s, dist = %s\n",
              ((state == STR_FB) ? "STR_FB" : (state == STR_LR) ? "STR_LR" : "STOP"),
              sprintf(str_speed, "%6, 1f", speed),
              sprintf(str_dist, "%6, 1f", dist));
      Serial.print(str);
      i = 0;
    }
    i++;
    delay(T_CTRL);
  }
}

void test_batt() {
  double batt;
  char str[100], str_batt[10];

  while (1) {
    batt = io_get_batt();
    sprintf(str, "volt = %s\n", sprintf(str_batt, "%4.2f", batt));
    Serial.print(str);
    delay(T_CTRL);
  }
}

void test_decode() {
  command_data_t command_data = {30000, -255, 0};
  middle_data_t  middle_data;
  serial_data_t  serial_data;

  while (1) {
    middle_data  = raspi_encode2(command_data);
    serial_data  = raspi_encode1(middle_data);
    middle_data  = raspi_decode1(serial_data);
    command_data = raspi_decode2(middle_data);
    Serial.println(command_data.val[0]);
    Serial.println(command_data.val[1]);
    Serial.println(command_data.val[2]);
    delay(1000);
  }
}
