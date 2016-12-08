static double dist_prev_l = 0.0;
static double dist_prev_r = 0.0;
static double err_prev_l  = 0.0;
static double err_prev_r  = 0.0;
static double err_sum_l   = 0.0;
static double err_sum_r   = 0.0;
static double vel_curr_l  = 0.0;
static double vel_curr_r  = 0.0;
static double vel_ref_l   = 0.0;
static double vel_ref_r   = 0.0;

void vel_ctrl_execute() {
  // PIDゲイン
  const double Kp = 0.5;
  const double Ki = 0.7;
  const double Kd = 0.0;

  int pwm_l, pwm_r;
  double dist_curr_l, dist_curr_r, err_curr_l, err_curr_r;

  // 速度 [cm/s] = 距離の差分 [cm] / (制御周期 [ms] / 1000)
  distance_get(&dist_curr_l, &dist_curr_r);
  vel_curr_l = (dist_curr_l - dist_prev_l) / T_CTRL * 1000.0;
  vel_curr_r = (dist_curr_r - dist_prev_r) / T_CTRL * 1000.0;

  // 誤差の計算
  err_curr_l = vel_ref_l - vel_curr_l;
  err_curr_r = vel_ref_r - vel_curr_r;
  err_sum_l += err_curr_l;
  err_sum_r += err_curr_r;

  // PID制御
  pwm_l = Kp * err_curr_l + Ki * err_sum_l + Kd * (err_curr_l - err_prev_l);
  pwm_r = Kp * err_curr_r + Ki * err_sum_r + Kd * (err_curr_r - err_prev_r);

  // 速度指令値 = 0 なら強制的に停止
  if (vel_ref_l == 0.0) pwm_l = 0;
  if (vel_ref_r == 0.0) pwm_r = 0;

  motor_set(pwm_l, pwm_r);

  dist_prev_l = dist_curr_l;
  dist_prev_r = dist_curr_r;
  err_prev_l  = err_curr_l;
  err_prev_r  = err_curr_r;
}

void vel_ctrl_set(double vel_l, double vel_r) {
  vel_ref_l = vel_l;
  vel_ref_r = vel_r;
}

void vel_ctrl_get(double *vel_l, double *vel_r) {
  *vel_l = vel_curr_l;
  *vel_r = vel_curr_r;
}

void vel_ctrl_reset() {
  dist_prev_l = 0.0;
  dist_prev_r = 0.0;
  err_prev_l  = 0.0;
  err_prev_r  = 0.0;
  err_sum_l   = 0.0;
  err_sum_r   = 0.0;
  vel_ref_l   = 0.0;
  vel_ref_r   = 0.0;

  motor_set(0, 0);
  encoder_reset();
}
