void slave() {
  double speed, dist, dist_l, dist_r, dist_f, dist_b ;
  run_state_t state;
  command_data_t command_data;

  while (1) {
    if (raspi_receive(&command_data) == 0) {
      switch (command_data.val[0]) {
        case 1:
          run_ctrl_set(STOP, 0, 0);
          break;
        case 2:
          run_ctrl_set(STR_FB, command_data.val[1], command_data.val[2]);
          break;
        case 3:
          run_ctrl_set(STR_LR, command_data.val[1], command_data.val[2]);
          break;
        case 4:
          run_ctrl_set(ROT, command_data.val[1], command_data.val[2]);
          break;
          
        case 9:
          run_ctrl_get(&state, &speed, &dist);
          command_data.val[0] = ((state == STR_FB) ? 2 : (state == ROT) ? 3 : 1);
          command_data.val[1] = (short)speed;
          command_data.val[2] = (short)dist;
          raspi_send(command_data);
          break;
          
        case 10:
          run_ctrl_get(&state, &speed, &dist);
          command_data.val[0] = ((state == STR_LR) ? 2 : (state == ROT) ? 3 : 1);
          command_data.val[1] = (short)speed;
          command_data.val[2] = (short)dist;
          raspi_send(command_data);
          break;
        case 11:
          distance_get(&dist_l, &dist_r, &dist_f, &dist_b);
          command_data.val[0] = (short)dist_l;
          command_data.val[1] = (short)dist_r;
          command_data.val[2] = (short)dist_f;
          command_data.val[3] = (short)dist_b;
          raspi_send(command_data);
          break;
        case 12:
          command_data.val[0] = (short)(io_get_batt() * 100.0);
          raspi_send(command_data);
          break;
        default:
          break;
      }
    }
    run_ctrl_execute();
    vel_ctrl_execute();
    delay(T_CTRL);
  }
}

