static run_state_t run_state = STP;
static double speed_ref  = 0.0;
static double speed_curr = 0.0;
static double dist_ref   = 0.0;
static double dist_curr  = 0.0;

void run_ctrl_execute() {
  // 直進制御において減速を開始する距離 [cm]
  const double dist_vel_down = 0.0;

  // 回転制御において減速を開始する角度 [deg]
  const double angle_vel_down = 0.0;

  // 直進制御における左右のタイヤの距離差の補正ゲイン
  const double Ks = 40.0;

  // 回転制御における左右のタイヤの距離差の補正ゲイン
  const double Kr = 0.0;

  int sign;
  double d_l, d_r, v_l, v_r, ratio, vel_ref, vel_mod;

  // 負の指令値に対応
  if (dist_ref >= 0.0) {
    sign = 1;
  } else {
    sign = -1;
  }

  distance_get(&d_l, &d_r);
  vel_ctrl_get(&v_l, &v_r);

  switch (run_state) {
    case STP:
      vel_ctrl_set(0.0, 0.0);
      break;
    case STR:
      // 直進距離
      dist_curr  = (d_l + d_r) / 2.0;
      speed_curr = (v_l + v_r) / 2.0 * sign;

      // 減速率
      ratio = sign * (dist_ref - dist_curr) / dist_vel_down;
      if (ratio < 0.0) ratio = 0.0;
      if (ratio > 1.0) ratio = 1.0;

      if (speed_ref == 0.0 || dist_ref == 0.0 || ratio == 0.0) {
        run_state = STP;
        vel_ctrl_set(0.0, 0.0);
      } else {
        // 減速の実行
        vel_ref = sign * speed_ref * ratio;

        // 左右のタイヤの距離差の補正
        vel_mod = (d_l - d_r) * Ks;

        vel_ctrl_set((vel_ref - vel_mod), (vel_ref + vel_mod));
      }

      break;
    case ROT:
      // 回転角度
      dist_curr  = -(d_l - d_r) / D_TIRE * 180.0 / PI;
      speed_curr = -(v_l - v_r) / D_TIRE * 180.0 / PI * sign;

      // 減速率
      ratio = sign * (dist_ref - dist_curr) / angle_vel_down;
      if (ratio < 0.0) ratio = 0.0;
      if (ratio > 1.0) ratio = 1.0;

      if (speed_ref == 0.0 || dist_ref == 0.0 || ratio == 0.0) {
        run_state = STP;
        vel_ctrl_set(0.0, 0.0);
      } else {
        // 減速の実行＆角速度指令値→速度指令値に変換
        vel_ref = sign * speed_ref * ratio * D_TIRE / 2.0 * PI / 180.0;

        // 左右のタイヤの距離差の補正
        vel_mod = -(d_l + d_r) * Kr;

        vel_ctrl_set(-(vel_ref - vel_mod), (vel_ref + vel_mod));
      }

      break;
  }
}

void run_ctrl_set(run_state_t state, double speed, double dist) {
  run_state = state;
  speed_ref = abs(speed);
  dist_ref = dist;
  vel_ctrl_reset();
}

void run_ctrl_get(run_state_t *state, double *speed, double *dist) {
  *state = run_state;
  *speed = speed_curr;
  *dist = dist_curr;
}
