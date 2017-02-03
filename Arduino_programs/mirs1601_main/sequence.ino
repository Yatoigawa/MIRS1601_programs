  void sequence_main(void) {
  char c = 0;
  int ret;
  USS sequenceSouth(USS_S);
  USS sequenceEast(USS_E);
  USS sequenceWest(USS_W);
  int diff_s;
  int diff_e;
  int diff_w;

start:     // スタート初期
  motor_set(0, 0, 0, 0, B00000000);
  omuni_ctrl_reset();

  while (1) {
    ret = cpu_com_read(&c);
    if (ret == 0) {
      break;
    }
    delay(2);
  }

  if (c == 'e') {
    goto east;
  }
  if (c == 'w') {
    goto west;
  }

  switch (c) {
    case 'l':
      //goto deb;
      omuni_ctrl_set(OMN_SDE, 230, 420);
      while (1) {
        omuni_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      omuni_ctrl_reset();

      // 実際の南との差を計測して、補正
      diff_s = 50 - (12 + sequenceSouth.getCM());
      if (diff_s > 0) {   // 南に近い
        omuni_ctrl_set(OMN_NDE, 230, diff_s);
      }
      else if (diff_s < 0) {
        omuni_ctrl_set(OMN_SDE, 230, diff_s);
      }
      else {
        omuni_ctrl_set(OMN_STOP, 0, 0);
      }
      while (1) {
        omuni_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      delay(1000);

      omuni_ctrl_reset();
deb:
      omuni_dist_ctrl_set(OMN_W, 130);
      while (1) {
        omuni_dist_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      delay(500);

      diff_w = 50 - (12 + sequenceWest.getCM());
      if (diff_w > 0) {   // 西に近い
        omuni_ctrl_set(OMN_EDS, 230, diff_w);
      }
      else if (diff_w < 0) {
        omuni_ctrl_set(OMN_WDS, 230, diff_w);
      }
      else {
        omuni_ctrl_set(OMN_STOP, 0, 0);
      }
      while (1) {
        omuni_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      delay(500);

      cpu_num_trans(2);
      delay(500);

east:
      omuni_dist_ctrl_set(OMN_N, 80);
      while (1) {
        omuni_dist_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      delay(500);

      omuni_dist_ctrl_set(OMN_W, 80);
      while (1) {
        omuni_dist_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      delay(500);

      omuni_tri_ctrl_set(rightForward);
      while (1) {
        omuni_tri_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      delay(500);

#ifdef DEBUG_MODE
      goto start;
#endif
      break;

    case 'r':
      omuni_ctrl_set(OMN_SDW, 230, 410);
      while (1) {
        omuni_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      delay(500);

      // 実際の南との差を計測して、補正
      diff_s = 50 - (12 + sequenceSouth.getCM());
      if (diff_s > 0) {   // 南に近い
        omuni_ctrl_set(OMN_NDW, 220, diff_s);
      }
      else if (diff_s < 0) {
        omuni_ctrl_set(OMN_SDW, 220, diff_s);
      }
      else {
        omuni_ctrl_set(OMN_STOP, 0, 0);
      }
      while (1) {
        omuni_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      delay(500);

      omuni_ctrl_set(OMN_EDS, 220, 120);
      while (1) {
        omuni_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      delay(500);

      diff_e = 50 - (12 - sequenceEast.getCM());
      if (diff_e > 0) {   // 東に近い
        omuni_ctrl_set(OMN_EDS, 220, diff_w);
      }
      else if (diff_e < 0) {
        omuni_ctrl_set(OMN_WDS, 220, diff_w);
      }
      else {
        omuni_ctrl_set(OMN_STOP, 0, 0);
      }
      while (1) {
        omuni_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      delay(500);

      cpu_num_trans(2);
      delay(500);

west:
      omuni_dist_ctrl_set(OMN_N, 80);
      while (1) {
        omuni_dist_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      delay(500);

      omuni_dist_ctrl_set(OMN_E, 80);
      while (1) {
        omuni_dist_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(T_CTRL);
      }
      delay(500);

#ifdef DEBUG_MODE
      goto start;
#endif
      break;
  }

}
