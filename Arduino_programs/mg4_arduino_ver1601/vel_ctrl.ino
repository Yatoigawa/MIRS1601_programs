static double dist_prev_n = 0.0;
static double dist_prev_e = 0.0;
static double dist_prev_s = 0.0;
static double dist_prev_w = 0.0;
static double err_prev_n  = 0.0;
static double err_prev_e  = 0.0;
static double err_prev_s  = 0.0;
static double err_prev_w  = 0.0;
static double err_sum_n   = 0.0;
static double err_sum_e   = 0.0;
static double err_sum_s   = 0.0;
static double err_sum_w   = 0.0;
static double vel_curr_n  = 0.0;
static double vel_curr_e  = 0.0;
static double vel_curr_s  = 0.0;
static double vel_curr_w  = 0.0;
static double vel_ref_n   = 0.0;
static double vel_ref_e   = 0.0;
static double vel_ref_s   = 0.0;
static double vel_ref_w   = 0.0;

void vel_ctrl_execute() {
  // PIDゲイン
  const double Kp = 0.5;
  const double Ki = 0.7;
  const double Kd = 0.0;

  int pwm_n, pwm_e, pwm_s, pwm_w;
  double dist_curr_n, err_curr_n, dist_curr_e, err_curr_e, dist_curr_s, err_curr_s, dist_curr_w, err_curr_w;

  // 速度 [cm/s] = 距離の差分 [cm] / (制御周期 [ms] / 1000)
  distance_get(&dist_curr_n, &dist_curr_e, &dist_curr_s, &dist_curr_w);
  vel_curr_n = (dist_curr_n - dist_prev_n) / T_CTRL * 1000.0;
  vel_curr_e = (dist_curr_e - dist_prev_e) / T_CTRL * 1000.0;
  vel_curr_s = (dist_curr_s - dist_prev_s) / T_CTRL * 1000.0;
  vel_curr_w = (dist_curr_w - dist_prev_w) / T_CTRL * 1000.0;


  // 誤差の計算
  err_curr_n = vel_ref_n - vel_curr_n;
  err_curr_e = vel_ref_e - vel_curr_e;
  err_curr_s = vel_ref_s - vel_curr_s;
  err_curr_w = vel_ref_w - vel_curr_w;
  err_sum_n += err_curr_n;
  err_sum_e += err_curr_e;
  err_sum_s += err_curr_s;
  err_sum_w += err_curr_w;

  // PID制御
  pwm_n = Kp * err_curr_n + Ki * err_sum_n + Kd * (err_curr_n - err_prev_n);
  pwm_e = Kp * err_curr_e + Ki * err_sum_e + Kd * (err_curr_e - err_prev_e);
  pwm_s = Kp * err_curr_s + Ki * err_sum_s + Kd * (err_curr_s - err_prev_s);
  pwm_w = Kp * err_curr_w + Ki * err_sum_w + Kd * (err_curr_w - err_prev_w);

  // 速度指令値 = 0 なら強制的に停止
  if (vel_ref_n == 0.0) pwm_n = 0;
  if (vel_ref_e == 0.0) pwm_e = 0;
  if (vel_ref_s == 0.0) pwm_s = 0;
  if (vel_ref_w == 0.0) pwm_w = 0;

  motor_set(pwm_n, pwm_e, pwm_s, pwm_w);

  dist_prev_n = dist_curr_n;
  dist_prev_e = dist_curr_e;
  dist_prev_s = dist_curr_s;
  dist_prev_w = dist_curr_w;
  err_prev_n  = err_curr_n;
  err_prev_e  = err_curr_e;
  err_prev_s  = err_curr_s;
  err_prev_w  = err_curr_w;
}

void vel_ctrl_set(double vel_n, double vel_e, double vel_s, double vel_w) {
  vel_ref_n = vel_n;
  vel_ref_e = vel_e;
  vel_ref_s = vel_s;
  vel_ref_w = vel_w;
}

void vel_ctrl_get(double *vel_n, double *vel_e, double *vel_s, double *vel_w) {
  *vel_n = vel_curr_n;
  *vel_e = vel_curr_e;
  *vel_s = vel_curr_s;
  *vel_w = vel_curr_w;
}

void vel_ctrl_reset() {
  dist_prev_n = 0.0;
  dist_prev_e = 0.0;
  dist_prev_s = 0.0;
  dist_prev_w = 0.0;
  err_prev_n  = 0.0;
  err_prev_e  = 0.0;
  err_prev_s  = 0.0;
  err_prev_w  = 0.0;
  err_sum_n   = 0.0;
  err_sum_e   = 0.0;
  err_sum_s   = 0.0;
  err_sum_w   = 0.0;
  vel_ref_n   = 0.0;
  vel_ref_e   = 0.0;
  vel_ref_s   = 0.0;
  vel_ref_w   = 0.0;

  motor_set(0, 0, 0, 0);
  encoder_reset();
}
