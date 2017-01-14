void motor_open() {
  
  pinMode(MTR_1ENA, OUTPUT);
  pinMode(MTR_1ENB, OUTPUT);
  pinMode(MTR_2ENA, OUTPUT);
  pinMode(MTR_2ENB, OUTPUT);
  pinMode(MTR_N1, OUTPUT);
  pinMode(MTR_N2, OUTPUT);
  pinMode(MTR_E1, OUTPUT);
  pinMode(MTR_E2, OUTPUT);
  pinMode(MTR_S1, OUTPUT);
  pinMode(MTR_S2, OUTPUT);
  pinMode(MTR_W1, OUTPUT);
  pinMode(MTR_W2, OUTPUT);
  
  analogWrite(MTR_1ENA, 0);
  analogWrite(MTR_1ENB, 0);
  analogWrite(MTR_2ENA, 0);
  analogWrite(MTR_2ENB, 0);
}

void motor_set(int pwm_n, int pwm_e, int pwm_s, int pwm_w) {
  // モータ回転方向の補正
  //pwm_n *= -1;
  pwm_e *= -1;
  //pwm_s *= -1;
  pwm_w *= -1;

  if (pwm_n >  255) pwm_n =  255;
  if (pwm_n < -255) pwm_n = -255;
  if (pwm_e >  255) pwm_e =  255;
  if (pwm_e < -255) pwm_e = -255;
  if (pwm_s >  255) pwm_s =  255;
  if (pwm_s < -255) pwm_s = -255;
  if (pwm_w >  255) pwm_w =  255;
  if (pwm_w < -255) pwm_w = -255;

  if (pwm_n > 0) {
    digitalWrite(MTR_N1, HIGH);
    analogWrite(MTR_1ENA, pwm_n);
  } else {
    digitalWrite(MTR_N1, LOW);
    analogWrite(MTR_1ENA, -pwm_n);
  }
  if (pwm_e > 0) {
    digitalWrite(MTR_E1, HIGH);
    analogWrite(MTR_1ENB, pwm_e);
  } else {
    digitalWrite(MTR_E1, LOW);
    analogWrite(MTR_1ENB, -pwm_e);
  }
    if (pwm_s > 0) {
    digitalWrite(MTR_S1, HIGH);
    analogWrite(MTR_2ENA, pwm_s);
  } else {
    digitalWrite(MTR_S1, LOW);
    analogWrite(MTR_2ENA, -pwm_s);
  }
    if (pwm_w > 0) {
    digitalWrite(MTR_W1, HIGH);
    analogWrite(MTR_2ENB, pwm_w);
  } else {
    digitalWrite(MTR_W1, LOW);
    analogWrite(MTR_2ENB, -pwm_w);
  }
}
