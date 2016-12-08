void distance_get(double *dist_l, double *dist_r) {
  long enc_l, enc_r;

  encoder_get(&enc_l, &enc_r);

  // 走行距離 [cm] = エンコーダ積算値 * タイヤ円周 [cm] / 分解能 / タイヤとエンコーダの回転比
  *dist_l = enc_l * R_TIRE * 2.0 * PI / ENC_RANGE / T_E_RATIO;
  *dist_r = enc_r * R_TIRE * 2.0 * PI / ENC_RANGE / T_E_RATIO * L_R_RATIO;
}
