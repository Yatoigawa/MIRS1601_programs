void omuni_dist_ctrl_execute(void) {
  double Kenc = 7;

  int pwm_n, pwm_s, pwm_e, pwm_w;
  int pwm_ref = 220;
  double ratio = 0;
  double dist_curr_n, dist_curr_e, dist_curr_s, dist_curr_w, err_dist, dist_m;
  double adj_pwm;
  int dist_pwm_down = 70;

  ratio_n_s = 0;
  ratio_e_w = 0;

  distance_get(&dist_curr_n, &dist_curr_s, &dist_curr_e, &dist_curr_w);

  switch (omuni_state) {
    case OMN_N:
      ratio_e_w = 10;
      dist_m = dist_ref - (( abs(dist_curr_e) + abs(dist_curr_w) ) / 2.0);
      ratio = dist_m / (dist_pwm_down - 10);    // 減速率
      ratio += 0.5;
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (ratio  < 0) {
        ratio = 0.0;
      }
      pwm_e = (int)(ratio * pwm_ref);
      pwm_w = (int)(ratio * pwm_ref);

      if (dist_m < 0 /*|| count > 10*/) {   // 目標地以上に進んでいる
        omuni_state = OMN_STOP;
        motor_set(0, 0, 0, 0, B00000000);
        omuni_end_flag = 1;
      }
      else {
        err_dist = (abs(dist_curr_e - dist_prev_e)) - (abs(dist_curr_w - dist_prev_w));
        adj_pwm = Kenc * abs(err_dist);
        if (err_dist > 0) {  // 東のほうが進んでいる
          pwm_e -= (int)adj_pwm;
          pwm_w += (int)adj_pwm;
        }
        else if (err_dist < 0) { // 西のほうが進んでいる
          pwm_e += (int)adj_pwm;
          pwm_w -= (int)adj_pwm;
        }
      }
      break;

    case OMN_W:
    case OMN_E:
      ratio_n_s = -10;
      ratio_e_w = 5;
      dist_m = dist_ref - (( abs(dist_curr_n) + abs(dist_curr_s) ) / 2.0);
      ratio = dist_m / (dist_pwm_down - 10);    // 減速率
      ratio += 0.5;
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (ratio  < 0) {
        ratio = 0.0;
      }
      pwm_n = (int)(ratio * pwm_ref);
      pwm_s = (int)(ratio * pwm_ref);

      if (dist_m < 0 /*|| count > 10*/) {   // 目標地以上に進んでいる
        omuni_state = OMN_STOP;
        motor_set(0, 0, 0, 0, B00000000);
        omuni_end_flag = 1;
      }
      else {
        err_dist = (abs(dist_curr_n - dist_prev_n)) - (abs(dist_curr_s - dist_prev_s));
        adj_pwm = Kenc * abs(err_dist);
        if (err_dist > 0) {  // 東のほうが進んでいる
          pwm_n -= (int)adj_pwm;
          pwm_s += (int)adj_pwm;
        }
        else if (err_dist < 0) { // 西のほうが進んでいる
          pwm_n += (int)adj_pwm;
          pwm_s -= (int)adj_pwm;
        }
      }
      break;

  }

  pwm_n += ratio_n_s;
  pwm_s -= ratio_n_s;
  pwm_e += ratio_e_w;
  pwm_w -= ratio_e_w;

  dist_prev_n = dist_curr_n;
  dist_prev_s = dist_curr_s;
  dist_prev_e = dist_curr_e;
  dist_prev_w = dist_curr_w;

  if (pwm_n < 25) {
    pwm_n = 0;
  }
  if (pwm_s < 25) {
    pwm_s = 0;
  }
  if (pwm_e < 25) {
    pwm_e = 0;
  }
  if (pwm_w < 25) {
    pwm_w = 0;
  }

  if ((int)(ratio * 100) == (int)(prev_ratio * 100)) {
    count++;
  }
  else {
    count = 0;
  }
  prev_ratio = ratio;
  motor_set(pwm_n, pwm_s, pwm_e, pwm_w, motor_state);
}

void omuni_dist_ctrl_set(omuni_state_t state, int dist) {
  omuni_state = state;
  dist_ref = dist;
  count = 0;
  // モータ側からホイールを見て、右回り  -> B01
  //                             左回り  -> B10
  //                             慣停    -> B00
  //  北、東 -> 正

  switch (state) {
    case OMN_N:
      motor_state = B01100000;
      break;
    case OMN_S:
      motor_state = B10010000;
      break;
    case OMN_E:
      motor_state = B00001001;
      break;
    case OMN_W:
      motor_state = B00000110;
      break;
  }
  motor_set(0, 0, 0, 0, B00000000);
  encoder_reset();
  dist_prev_n         = 0;
  dist_prev_e         = 0;
  dist_prev_s         = 0;
  dist_prev_w         = 0;
  omuni_end_flag = 0;
}
