L298N_omuni driver = L298N_omuni(MTR_1ENA, MTR_N1, MTR_N2, MTR_S1, MTR_S2, MTR_1ENB,
                                 MTR_2ENA, MTR_E1, MTR_E2, MTR_W1, MTR_W2, MTR_2ENB);
int time_delay = 0;
void motor_set(int pwm_n, int pwm_e, int pwm_s, int pwm_w) {
  int pwm[4] = {pwm_n, pwm_e, pwm_s, pwm_w};
  //pwm[0] *= -1;
  //pwm[1] *= -1;
  pwm[2] *= -1;
  pwm[3] *= -1;

  if (pwm[0] >  255) pwm[0] =  255;
  if (pwm[0] < -255) pwm[0] = -255;
  if (pwm[1] >  255) pwm[1] =  255;
  if (pwm[1] < -255) pwm[1] = -255;
  if (pwm[2] >  255) pwm[2] =  255;
  if (pwm[2] < -255) pwm[2] = -255;
  if (pwm[3] >  255) pwm[3] =  255;
  if (pwm[3] < -255) pwm[3] = -255;

  if(omuni_state == OMN_STOP && run_state != STOP){
    if(run_state == STR_N){
      driver.forward(pwm[4],time_delay);
    }
    else if(run_state == STR_S) {
      driver.backward(pwm[4],time_delay);
    }
    else if(run_state == STR_E) {
      driver.right(pwm[4],time_delay);
    }
    else if(run_state == STR_W) {
      driver.left(pwm[4],time_delay);
    }
    else if(run_state == STR_NE) {
      driver.rightForward(pwm[4],time_delay);
    }
     else if(run_state == STR_NW) {
      driver.leftForward(pwm[4],time_delay);
    }
    else if(run_state == STR_SE) {
      driver.rightBackward(pwm[4],time_delay);
    }
    else if(run_state == STR_SW) {
      driver.leftBackward(pwm[4],time_delay);
    }
  }
  else if(omuni_state != OMN_STOP && run_state == STOP){
    if(omuni_state == OMN_N || omuni_state == OMN_NDE || omuni_state == OMN_NDW){
      driver.forward(pwm[4],time_delay);
    }
    else if(omuni_state == OMN_S || omuni_state == OMN_SDE || omuni_state == OMN_SDW) {
      driver.backward(pwm[4],time_delay);
    }
    else if(omuni_state == OMN_E || omuni_state == OMN_EDN || omuni_state == OMN_EDS) {
      driver.right(pwm[4],time_delay);
    }
    else if(omuni_state == OMN_W || omuni_state == OMN_WDN || omuni_state == OMN_WDS) {
      driver.left(pwm[4],time_delay);
    }
  }
  else if(omuni_state == OMN_STOP && run_state == STOP){
    driver.fullStop(time_delay);
  }
}
