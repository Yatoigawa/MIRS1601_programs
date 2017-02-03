void distance_get(double *dist_n, double *dist_s, double *dist_e, double *dist_w) {
  long enc_n, enc_e, enc_s, enc_w;

  encoder_get(&enc_n, &enc_s, &enc_e, &enc_w);

  // 走行距離 [cm] = エンコーダ積算値 * タイヤ円周 [cm] / 分解能 / タイヤとエンコーダの回転比
  *dist_n = enc_n * R_TIRE * 2.0 * PI / ENC_RANGE / T_E_RATIO;
  *dist_e = enc_e * R_TIRE * 2.0 * PI / ENC_RANGE / T_E_RATIO;
  *dist_s = enc_s * R_TIRE * 2.0 * PI / ENC_RANGE / T_E_RATIO * N_S_RATIO;
  *dist_w = enc_w * R_TIRE * 2.0 * PI / ENC_RANGE / T_E_RATIO * E_W_RATIO;
}
