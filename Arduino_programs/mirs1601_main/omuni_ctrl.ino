static double pwm_ref             = 0.0;
static omuni_state_t omuni_state  = OMN_STOP;
static int dist_wall_n            = 20; //北側の壁との目標距離
static int dist_wall_e            = 20; //東側の壁との目標距離
static int dist_wall_s            = 20; //南側の壁との目標距離
static int dist_wall_w            = 20; //西側の壁との目標距離
static byte motor_state           = B00000000;
static int omuni_end_flag         = 0;
static int dist_ref               = 0;
static double dist_prev_n         = 0;
static double dist_prev_e         = 0;
static double dist_prev_s         = 0;
static double dist_prev_w         = 0;

static double ratio_e_w           = 0;
static double ratio_n_s           = 0;
static int count                  = 0;
static double prev_ratio          = 0;

void omuni_ctrl_execute() {
  const double Kenc = 5;
  const double Kuss = 10;

  USS distNorth(USS_N);
  USS distSouth(USS_S);
  USS distEast(USS_E);
  USS distWest(USS_W);

  double dist_curr_n, dist_curr_e, dist_curr_s, dist_curr_w, err_dist, dist_m;
  double err_dist_n, err_dist_s, err_dist_e, err_dist_w;
  double dist_pwm_down = 70;
  double ratio, adj_pwm;
  int pwm_n = 0, pwm_s = 0, pwm_e = 0, pwm_w = 0;
  int err_n;  //北側の壁まで距離と現在地の差
  int err_e;  //東側の壁まで距離と現在地の差
  int err_s;  //南側の壁まで距離と現在地の差
  int err_w;  //西側の壁まで距離と現在地の差
  int err_uss;

  ratio_n_s = 0;
  ratio_e_w = 0;

  distance_get(&dist_curr_n, &dist_curr_s, &dist_curr_e, &dist_curr_w);
  //    dist_curr_n *= 0.8;
  //    dist_curr_s *= 0.8;
  //    dist_curr_e *= 0.8;
  //    dist_curr_w *= 0.8;

  switch (omuni_state) {
    case OMN_STOP:    // モータ全停止
      motor_set(0, 0, 0, 0, B00000000);
      break;

    //    case OMN_N:
    //      err_n = distNorth.getCM() - dist_wall_n;
    //      err_uss = distEast.getCM() - distWest.getCM();
    //      ratio = err_n / dist_pwm_down;    // 減速率
    //      if (ratio < 0.0) {
    //        ratio = 0.0;
    //      }
    //      else if (ratio > 1.0) {
    //        ratio = 1.0;
    //      }
    //      pwm_e = (int)(ratio * pwm_ref);
    //      pwm_w = (int)(ratio * pwm_ref);
    //
    //      if (err_n <= 0) {   // 目標地以上に進んでいる
    //        omuni_state = OMN_STOP;
    //        motor_set(0, 0, 0, 0, B00000000);
    //        omuni_end_flag = 1;
    //      }
    //      else {
    //        err_dist = abs(dist_curr_e) - abs(dist_curr_w);
    //        adj_pwm = Kenc * abs(err_dist);
    //        if (err_dist > 0) {  // 東のほうが進んでいる
    //          pwm_e -= (int)adj_pwm;
    //          pwm_w += (int)adj_pwm;
    //        }
    //        else if (err_dist < 0) { // 西のほうが進んでいる
    //          pwm_e += (int)adj_pwm;
    //          pwm_w -= (int)adj_pwm;
    //        }
    //        adj_pwm = Kuss * abs(err_uss);
    //        if (err_uss > 0) {    // 東のほうが大きい->西に寄っている
    //          motor_state |= B00001001;
    //        }
    //        else if (err_uss < 0) { // 西のほうが大きい->東に寄っている
    //          motor_state |= B00000110;
    //        }
    //        pwm_n = (int)adj_pwm;
    //        pwm_s = (int)adj_pwm;
    //      }
    //      break;
    //
    //    case OMN_S:
    //      err_s = distSouth.getCM() - dist_wall_s;
    //      err_uss = distEast.getCM() - distWest.getCM();
    //      ratio = err_s / dist_pwm_down;    // 減速率
    //      if (ratio < 0.0) {
    //        ratio = 0.0;
    //      }
    //      else if (ratio > 1.0) {
    //        ratio = 1.0;
    //      }
    //      pwm_e = (int)(ratio * pwm_ref);
    //      pwm_w = (int)(ratio * pwm_ref);
    //
    //      if (err_s <= 0) {   // 目標地以上に進んでいる
    //        omuni_state = OMN_STOP;
    //        motor_set(0, 0, 0, 0, B00000000);
    //        omuni_end_flag = 1;
    //      }
    //      else {
    //        err_dist = abs(dist_curr_e) - abs(dist_curr_w);
    //        adj_pwm = Kenc * abs(err_dist);
    //        if (err_dist > 0) {  // 東のほうが進んでいる
    //          pwm_e -= (int)adj_pwm;
    //          pwm_w += (int)adj_pwm;
    //        }
    //        else if (err_dist < 0) { // 西のほうが進んでいる
    //          pwm_e += (int)adj_pwm;
    //          pwm_w -= (int)adj_pwm;
    //        }
    //        adj_pwm = Kuss * abs(err_uss);
    //        if (err_uss > 0) {    // 東のほうが大きい->西に寄っている
    //          motor_state |= B00001001;
    //        }
    //        else if (err_uss < 0) { // 西のほうが大きい->東に寄っている
    //          motor_state |= B00000110;
    //        }
    //        pwm_n = (int)adj_pwm;
    //        pwm_s = (int)adj_pwm;
    //      }
    //      break;
    //
    //    case OMN_E:
    //      err_e = distEast.getCM() - dist_wall_e;
    //      err_uss = distNorth.getCM() - distSouth.getCM();
    //      ratio = err_e / dist_pwm_down;    // 減速率
    //      if (ratio < 0.0) {
    //        ratio = 0.0;
    //      }
    //      else if (ratio > 1.0) {
    //        ratio = 1.0;
    //      }
    //      pwm_n = (int)(ratio * pwm_ref);
    //      pwm_s = (int)(ratio * pwm_ref);
    //
    //      if (err_e <= 0) {   // 目標地以上に進んでいる
    //        omuni_state = OMN_STOP;
    //        motor_set(0, 0, 0, 0, B00000000);
    //        omuni_end_flag = 1;
    //      }
    //      else {
    //        err_dist = abs(dist_curr_n) - abs(dist_curr_s);
    //        adj_pwm = Kenc * abs(err_dist);
    //        if (err_dist > 0) {  // 北のほうが進んでいる
    //          pwm_n -= (int)adj_pwm;
    //          pwm_s += (int)adj_pwm;
    //        }
    //        else if (err_dist < 0) { // 南のほうが進んでいる
    //          pwm_n += (int)adj_pwm;
    //          pwm_s -= (int)adj_pwm;
    //        }
    //        adj_pwm = Kuss * abs(err_uss);
    //        if (err_uss > 0) {    // 北のほうが大きい->南に寄っている
    //          motor_state |= B01100000;
    //        }
    //        else if (err_uss < 0) { // 南のほうが大きい->北に寄っている
    //          motor_state |= B10010000;
    //        }
    //        pwm_e = (int)adj_pwm;
    //        pwm_w = (int)adj_pwm;
    //      }
    //      break;
    //
    //    case OMN_W:
    //      err_w = distWest.getCM() - dist_wall_w;
    //      err_uss = distNorth.getCM() - distSouth.getCM();
    //      ratio = err_w / dist_pwm_down;    // 減速率
    //      if (ratio < 0.0) {
    //        ratio = 0.0;
    //      }
    //      else if (ratio > 1.0) {
    //        ratio = 1.0;
    //      }
    //      pwm_n = (int)(ratio * pwm_ref);
    //      pwm_s = (int)(ratio * pwm_ref);
    //
    //      if (err_w <= 0) {   // 目標地以上に進んでいる
    //        omuni_state = OMN_STOP;
    //        motor_set(0, 0, 0, 0, B00000000);
    //        omuni_end_flag = 1;
    //      }
    //      else {
    //        err_dist = abs(dist_curr_n) - abs(dist_curr_s);
    //        adj_pwm = Kenc * abs(err_dist);
    //        if (err_dist > 0) {  // 北のほうが進んでいる
    //          pwm_n -= (int)adj_pwm;
    //          pwm_s += (int)adj_pwm;
    //        }
    //        else if (err_dist < 0) { // 南のほうが進んでいる
    //          pwm_n += (int)adj_pwm;
    //          pwm_s -= (int)adj_pwm;
    //        }
    //        adj_pwm = Kuss * abs(err_uss);
    //        if (err_uss > 0) {    // 北のほうが大きい->南に寄っている
    //          motor_state |= B01100000;
    //        }
    //        else if (err_uss < 0) { // 南のほうが大きい->北に寄っている
    //          motor_state |= B10010000;
    //        }
    //        pwm_e = (int)adj_pwm;
    //        pwm_w = (int)adj_pwm;
    //      }
    //      break;

    // ---------------------------------------------------------------------------------

    case OMN_NDE:
    case OMN_SDE:
      ratio_n_s = 0;
      ratio_e_w = 10;
      dist_wall_e = 18;
      err_uss = distEast.getCM() - dist_wall_e;
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

      if (dist_m < 0 /*|| count > 30*/) {   // 目標地以上に進んでいる
        omuni_state = OMN_STOP;
        motor_set(50, 50, 50, 50, B11111111);
        delay(500);
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
        adj_pwm = Kuss * abs(err_uss);
        if (err_uss < 0) {    // 東に近い
          motor_state |=  (B00000110);
          motor_state &= ~(B00001001);
        }
        else if (err_uss > 0) { // 東から遠い
          motor_state |=  (B00001001);
          motor_state &= ~(B00000110);
        }
        pwm_n  = (int)adj_pwm;
        pwm_n += 115;
        pwm_s  = (int)adj_pwm;
        pwm_s += 115;
      }
      break;

    case OMN_NDW:
    case OMN_SDW:
      ratio_n_s = 7;
      ratio_e_w = 10;
      dist_wall_w = 18;
      err_uss = distWest.getCM() - dist_wall_w;
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

      if (dist_m < 0 || count > 10) {   // 目標地以上に進んでいる
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
        adj_pwm = Kuss * abs(err_uss);
        if (err_uss < 0) {    // 西に近い
          motor_state |=  (B00001001);
          motor_state &= ~(B00000110);
        }
        else if (err_uss > 0) { // 西から遠い
          motor_state |=  (B00000110);
          motor_state &= ~(B00001001);
        }
        pwm_n  = (int)adj_pwm;
        pwm_n += 115;
        pwm_s  = (int)adj_pwm;
        pwm_s += 115;
      }
      break;

    case OMN_EDN:
    case OMN_WDN:
      ratio_e_w = 10;
      ratio_n_s = 10;
      dist_wall_n = 20;
      err_uss = distNorth.getCM() - dist_wall_n;
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

      if (dist_m < 0 || count > 10) {   // 目標地以上に進んでいる
        omuni_state = OMN_STOP;
        motor_set(0, 0, 0, 0, B00000000);
        omuni_end_flag = 1;
      }
      else {
        err_dist = (abs(dist_curr_n - dist_prev_n)) - (abs(dist_curr_s - dist_prev_s));
        adj_pwm = Kenc * abs(err_dist);
        if (err_dist > 0) {  // 北のほうが進んでいる
          pwm_n -= (int)adj_pwm;
          pwm_s += (int)adj_pwm;
        }
        else if (err_dist < 0) { // 南のほうが進んでいる
          pwm_n += (int)adj_pwm;
          pwm_s -= (int)adj_pwm;
        }
        adj_pwm = Kuss * abs(err_uss);
        if (err_uss < 0) {    // 北に近い
          motor_state |=  (B10010000);
          motor_state &= ~(B01100000);
        }
        else if (err_uss > 0) { // 北から遠い
          motor_state |=  (B01100000);
          motor_state &= ~(B10010000);
        }
        pwm_e  = (int)adj_pwm;
        pwm_e += 115;
        pwm_w  = (int)adj_pwm;
        pwm_w += 115;
      }
      break;

    case OMN_EDS:
    case OMN_WDS:
      dist_wall_s = 18;
      err_uss = distSouth.getCM() - dist_wall_s;
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

      if (dist_m < 0) {   // 目標地以上に進んでいる
        omuni_state = OMN_STOP;
        motor_set(50, 50, 50, 50, B11111111);
        delay(1000);
        motor_set(0, 0, 0, 0, B00000000);
        omuni_end_flag = 1;
      }
      else {
        err_dist = (abs(dist_curr_n - dist_prev_n)) - (abs(dist_curr_s - dist_prev_s));
        adj_pwm = Kenc * abs(err_dist);
        if (err_dist > 0) {  // 北のほうが進んでいる
          pwm_n -= (int)adj_pwm;
          pwm_s += (int)adj_pwm;
        }
        else if (err_dist < 0) { // 南のほうが進んでいる
          pwm_n += (int)adj_pwm;
          pwm_s -= (int)adj_pwm;
        }
        adj_pwm = Kuss * abs(err_uss);
        if (err_uss < 0) {    // 南に近い
          motor_state |=  (B01100000);
          motor_state &= ~(B10010000);
        }
        else if (err_uss > 0) { // 南から遠い
          motor_state |=  (B10010000);
          motor_state &= ~(B01100000);
        }
        pwm_e  = (int)adj_pwm;
        pwm_e += 115;
        pwm_w  = (int)adj_pwm;
        pwm_w += 115;
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

  //  if ((int)(ratio * 100) == (int)(prev_ratio * 100)) {
  //    count++;
  //  }
  //  else {
  //    count = 0;
  //  }

  prev_ratio = ratio;
  motor_set(pwm_n, pwm_s, pwm_e, pwm_w, motor_state);

}

void omuni_ctrl_set(omuni_state_t state, double speed, int dist) {
  omuni_state = state;
  pwm_ref = speed;
  dist_ref = dist;
  count = 0;
  // モータ側からホイールを見て、右回り  -> B01
  //                             左回り  -> B10
  //                             慣停    -> B00
  //  北、東 -> 正


  switch (state) {
    case OMN_N:
    case OMN_NDE:
    case OMN_NDW:
      motor_state = B01100000;
      break;
    case OMN_S:
    case OMN_SDE:
    case OMN_SDW:
      motor_state = B10010000;
      break;
    case OMN_E:
    case OMN_EDN:
    case OMN_EDS:
      motor_state = B00001001;
      break;
    case OMN_W:
    case OMN_WDN:
    case OMN_WDS:
      motor_state = B00000110;
      break;
  }
  dist_prev_n = 0;
  dist_prev_e = 0;
  dist_prev_s = 0;
  dist_prev_w = 0;
  motor_set(0, 0, 0, 0, B00000000);
  encoder_reset();
  omuni_end_flag = 0;
}

void omuni_ctrl_reset() {
  pwm_ref = 0.0;
  dist_ref = 0;
  omuni_state = OMN_STOP;
  motor_state = B00000000;
  motor_set(0, 0, 0, 0, B00000000);
  encoder_reset();
  dist_prev_n = 0;
  dist_prev_e = 0;
  dist_prev_s = 0;
  dist_prev_w  = 0;
  omuni_end_flag = 0;
}
