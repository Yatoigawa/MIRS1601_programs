void sequence_main(void) {
  char c = 0;
  int ret;
start:     // スタート初期
  vel_ctrl_reset();

  while ( ! ( ( ret = cpu_com_read(&c) ) == 0 ) );

  switch (c) {
    case 'l':
      omuni_ctrl_set(OMN_SDE, 100, 40);
      while (1) {
        omuni_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(10);
      }
      omuni_ctrl_set(OMN_WDS, 100, 50);
      while (1) {
        omuni_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(10);
      }
      cpu_num_trans(1);
      goto start;
      break;
    
    case 'r':
      omuni_ctrl_set(OMN_SDW, 100, 40);
      while (1) {
        omuni_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(10);
      }
      omuni_ctrl_set(OMN_EDS, 100, 50);
      while (1) {
        omuni_ctrl_execute();
        ret = cpu_com_read(&c);
        if (c == 's') {
          goto start;
        }
        if (omuni_end_flag == 1) {
          break;
        }
        delay(10);
      }
      cpu_num_trans(2);
      goto start;
      break;
  }
}
