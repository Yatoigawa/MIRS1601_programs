L298N_omuni driver = L298N_omuni(MTR_1ENA, MTR_N1, MTR_N2, MTR_S1, MTR_S2, MTR_1ENB,
                                 MTR_2ENA, MTR_E1, MTR_E2, MTR_W1, MTR_W2, MTR_2ENB);
int time_delay = 0;

void motor_set(int pwm_n, int pwm_s, int pwm_e, int pwm_w, byte state) {
  // モータ側からホイールを見て、右回り  -> B01
  //                             左回り  -> B10
  //                             慣停    -> B00
  //  北、東 -> 正
  /*                ↑ North
   * 
   *              →
   *            ______
   *   
   *  01 
   *  w  |                  |   e
   *  ↑ |                  | ↓
   *     |                  |
   *     
   *            ______
   *              ←
   *                  s
   */
  int pwm[4] = {pwm_n, pwm_s, pwm_e, pwm_w};

  for(int i = 0; i < 4; i++){
    if(pwm[i] > 255){
      pwm[i] = 255;
    }
  }
  driver.setupMotors(state);
  driver.driveMotors(pwm);
  delay(time_delay);
}
