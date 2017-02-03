static byte omuni_tri_state = 0;

void omuni_tri_ctrl_execute() {
  double dist_curr_n, dist_curr_e, dist_curr_s, dist_curr_w, err_dist_n_s, err_dist_e_w, err_ang, dist_m;
  double dist_avg_n_s, dist_avg_e_w;
  double err_dist_n, err_dist_s, err_dist_e, err_dist_w;
  double dist_pwm_down = 70;
  double ratio, adj_pwm;
  int pwm_n = 0, pwm_s = 0, pwm_e = 0, pwm_w = 0;
  pwm_ref = 230;
  double Kenc = 5;
  double Kang = 5;

  dist_ref = 225;

  ratio_n_s = 0;
  ratio_e_w = 0;

  distance_get(&dist_curr_n, &dist_curr_s, &dist_curr_e, &dist_curr_w);
  dist_avg_n_s = abs((dist_curr_n + dist_curr_s) / 2.0);
  dist_avg_e_w = abs((dist_curr_e + dist_curr_w) / 2.0);
  dist_m = dist_ref - (sqrt(pow(dist_avg_n_s, 2) + pow(dist_avg_e_w, 2)));
  ratio = dist_m / (dist_pwm_down - 10);
  ratio += 0.5;
  if (ratio > 1.0) {
    ratio = 1.0;
  }
  if (ratio  < 0) {
    ratio = 0.0;
  }
  pwm_n = (int)(ratio * pwm_ref);
  pwm_s = (int)(ratio * pwm_ref);
  pwm_e = (int)(ratio * pwm_ref);
  pwm_w = (int)(ratio * pwm_ref);

  if (dist_m < 0 /*|| count > 10*/) {
    omuni_state = OMN_STOP;
    motor_set(0, 0, 0, 0, B00000000);
    omuni_end_flag = 1;
  }

  err_dist_n_s = abs(dist_curr_n - dist_curr_s);
  adj_pwm = (int)(err_dist_n_s * Kenc);
  if (err_dist_n_s > 0) {
    pwm_n -= adj_pwm;
    pwm_s += adj_pwm;
  }
  else if (err_dist_n_s < 0) {
    pwm_n += adj_pwm;
    pwm_s -= adj_pwm;
  }
  err_dist_e_w = abs(dist_curr_e - dist_curr_w);
  adj_pwm = (int)(err_dist_e_w * Kenc);
  if (err_dist_e_w > 0) {
    pwm_e -= adj_pwm;
    pwm_w += adj_pwm;
  }
  else if (err_dist_n_s < 0) {
    pwm_e += adj_pwm;
    pwm_w -= adj_pwm;
  }
  err_ang = dist_avg_n_s - dist_avg_e_w;
  adj_pwm = (int)(err_ang * Kang);
  if (err_ang > 0) {
    pwm_n -= adj_pwm;
    pwm_s -= adj_pwm;
    pwm_e += adj_pwm;
    pwm_w += adj_pwm;
  }
  else if (err_ang < 0) {
    pwm_n += adj_pwm;
    pwm_s += adj_pwm;
    pwm_e -= adj_pwm;
    pwm_w -= adj_pwm;
  }
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
  if((int)(ratio * 100) == (int)(prev_ratio * 100)){
    count++;
  }
  else {
    count = 0;
  }
  
  prev_ratio = ratio;
  motor_set(pwm_n, pwm_s, pwm_e, pwm_w, omuni_tri_state);
}

void omuni_tri_ctrl_set(byte state) {
  omuni_tri_state = state;
  dist_prev_n = 0;
  dist_prev_e = 0;
  dist_prev_s = 0;
  dist_prev_w = 0;
  encoder_reset();
  motor_set(0, 0, 0, 0, B00000000);
  omuni_end_flag = 0;
}

