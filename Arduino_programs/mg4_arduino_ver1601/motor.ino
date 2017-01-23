L298N_omuni driver = L298N_omuni(MTR_1ENA, MTR_N1, MTR_N2, MTR_S1, MTR_S2, MTR_1ENB,
               MTR_2ENA, MTR_E1, MTR_E2, MTR_W1, MTR_W2, MTR_2ENB);
int time_delay = 0;

void motor_open() {
  pinMode(PIN_DIR_L, OUTPUT);
  pinMode(PIN_PWM_L, OUTPUT);
  pinMode(PIN_DIR_R, OUTPUT);
  pinMode(PIN_PWM_R, OUTPUT);
  analogWrite(PIN_PWM_L, 0);
  analogWrite(PIN_PWM_R, 0);
  
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
  //pwm_e *= -1;
  pwm_s *= -1;
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
    driver.setupMotor(0,LOW,HIGH);
    driver.driveMotor(0,pwm_n);
    delay(time_delay);
  } else {
    driver.setupMotor(0,HIGH,LOW);
    driver.driveMotor(0,pwm_n);
    delay(time_delay);
  }
  if (pwm_e > 0) {
    driver.setupMotor(2,LOW,HIGH);
    driver.driveMotor(2,pwm_e);
    delay(time_delay);
  } else {
    driver.setupMotor(2,HIGH,LOW);
    driver.driveMotor(2,pwm_e);
    delay(time_delay);
  }
    if (pwm_s > 0) {
    driver.setupMotor(1,LOW,HIGH);
    driver.driveMotor(1,pwm_s);
    delay(time_delay);
  } else {
    driver.setupMotor(1,HIGH,LOW);
    driver.driveMotor(1,pwm_s);
    delay(time_delay);
  }
    if (pwm_w > 0) {
    driver.setupMotor(3,LOW,HIGH);
    driver.driveMotor(3,pwm_w);
    delay(time_delay);
  } else {
    driver.setupMotor(3,HIGH,LOW);
    driver.driveMotor(3,pwm_w);
    delay(time_delay);
  }
}
