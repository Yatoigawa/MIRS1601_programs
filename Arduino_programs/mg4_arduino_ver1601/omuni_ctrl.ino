static omuni_state_t omuni_state = OMN_STOP;
static double omuni_speed_ref = 0.0;
static double omuni_speed_curr = 0.0;
static int omuni_end_flag = 0;

static int dist_wall_n = 10; //北側の壁との目標距離
static int dist_wall_e  = 10; //東側の壁との目標距離
static int dist_wall_s = 10; //南側の壁との目標距離
static int dist_wall_w  = 10; //西側の壁との目標距離

void omuni_ctrl_execute() {

  int uss_n = USS_N;
  int uss_e = USS_E;
  int uss_s = USS_S;
  int uss_w = USS_W;

  int err_n;  //北側の壁まで距離と現在地の差
  int err_e;  //東側の壁まで距離と現在地の差
  int err_s;  //南側の壁まで距離と現在地の差
  int err_w;  //西側の壁まで距離と現在地の差

  double adj_vel;      //加算or減算する修正値 adjust value
  double Kp = 1.0;     //差分距離err_Xと加減速補正add_velに対する比例ゲイン
  double dist_vel_down = 0.0; //残距離に応じて減速し始める距離[cm]
  double  v_n, v_s, v_e, v_w, ratio, vel_ref;

  USS distNorth(uss_n);
  USS distEast(uss_e);
  USS distSouth(uss_e);
  USS distWest(uss_w);

  vel_ctrl_get(&v_n, &v_s, &v_e, &v_w);

  switch (omuni_state) {

    case OMN_STOP:  //全停止
      vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
      break;

    case OMN_N:     //東と西側の壁を基準として北方向へ走行
      omuni_speed_curr = (v_e + v_w) / 2.0;
      err_n = distNorth.getCM() - dist_wall_n;  //壁との距離
      err_e = distEast.getCM() - dist_wall_e;
      err_w = distWest.getCM() - dist_wall_w;
      ratio = err_n / dist_vel_down;  //減速率
      if (ratio < 0.0) {
        ratio = 0.0;
      }
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (err_n <= 0) {
        //北側の壁との距離が目標距離以内なら全停止
        omuni_state = OMN_STOP;
        vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
        omuni_end_flag = 1;
      } else if (err_e >= 0 || err_w <= 0) {
        //東側の壁から離れ、西側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * (abs(err_e) + abs(err_w)) / 2;
        vel_ctrl_set(0, vel_ref - adj_vel, 0, vel_ref + adj_vel);
      } else if (err_e <= 0 || err_w >= 0) {
        //西側の壁から離れ、東側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * (abs(err_e) + abs(err_w)) / 2;
        vel_ctrl_set(0, vel_ref + adj_vel, 0, vel_ref - adj_vel);
      }
      break;

    case OMN_E:     //北と南側の壁を基準として東方向へ走行
      omuni_speed_curr = (v_n + v_s) / 2.0;
      err_n = distNorth.getCM() - dist_wall_n;  //壁との距離
      err_e = distEast.getCM() - dist_wall_e;
      err_s = distSouth.getCM() - dist_wall_s;
      ratio = err_e / dist_vel_down;  //壁との距離/減速し始める距離
      if (ratio < 0.0) {
        ratio = 0.0;
      }
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (err_e <= 0) {
        //東側の壁との距離が目標距離以内なら全停止
        omuni_state = OMN_STOP;
        vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
        omuni_end_flag = 1;
      } else if (err_n >= 0 || err_s <= 0) {
        //北側の壁から離れ、南側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * (abs(err_n) + abs(err_s)) / 2;
        vel_ctrl_set(vel_ref - adj_vel, 0, vel_ref + adj_vel, 0);
      } else if (err_n <= 0 || err_s >= 0) {
        //南側の壁から離れ、北側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * (abs(err_n) + abs(err_s)) / 2;
        vel_ctrl_set(vel_ref + adj_vel, 0, vel_ref - adj_vel, 0);
      }
      break;

    case OMN_S:     //東と西側の壁を基準として南方向へ走行
      omuni_speed_curr = (v_e + v_w) / 2.0;
      err_w = distWest.getCM() - dist_wall_w;  //壁との距離
      err_e = distEast.getCM() - dist_wall_e;
      err_s = distSouth.getCM() - dist_wall_s;
      ratio = err_s / dist_vel_down;  //減速率
      if (ratio < 0.0) {
        ratio = 0.0;
      }
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (err_s <= 0) {
        //南側の壁との距離が目標距離以内なら全停止
        omuni_state = OMN_STOP;
        vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
        omuni_end_flag = 1;
      } else if (err_e >= 0 || err_w <= 0) {
        //東側の壁から離れ、西側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * (abs(err_e) + abs(err_w)) / 2;
        vel_ctrl_set(0, -vel_ref + adj_vel, 0, -vel_ref - adj_vel);
      } else if (err_e <= 0 || err_w >= 0) {
        //西側の壁から離れ、東側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * (abs(err_e) + abs(err_w)) / 2;
        vel_ctrl_set(0, -vel_ref - adj_vel, 0, -vel_ref + adj_vel);
      }
      break;

    case OMN_W:     //北と南側の壁を基準として西方向へ走行
      omuni_speed_curr = (v_n + v_s) / 2.0;
      err_n = distNorth.getCM() - dist_wall_n;  //壁との距離
      err_w = distWest.getCM() - dist_wall_w;
      err_s = distSouth.getCM() - dist_wall_s;
      ratio = err_w / dist_vel_down;  //減速率
      if (ratio < 0.0) {
        ratio = 0.0;
      }
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (err_w <= 0) {
        //西側の壁との距離が目標距離以内なら全停止
        omuni_state = OMN_STOP;
        vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
        omuni_end_flag = 1;
      } else if (err_n >= 0 || err_s <= 0) {
        //北側の壁から離れ、南側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * (abs(err_n) + abs(err_s)) / 2;
        vel_ctrl_set(-vel_ref + adj_vel, 0, -vel_ref - adj_vel, 0);
      } else if (err_n <= 0 || err_s >= 0) {
        //南側の壁から離れ、北側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * (abs(err_n) + abs(err_s)) / 2;
        vel_ctrl_set(-vel_ref - adj_vel, 0, -vel_ref + adj_vel, 0);
      }
      break;
    //----------------------------------------------------------------------------------

    case OMN_NDE: //東側の壁のみを基準にして北向きに走行する場合
      omuni_speed_curr = (v_n + v_s) / 2.0;
      err_e = distEast.getCM() - dist_wall_e;  //壁との距離
      err_n = distNorth.getCM() - dist_wall_n;
      ratio = err_e / dist_vel_down;  //減速率
      if (ratio < 0.0) {
        ratio = 0.0;
      }
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (err_n <= 0) {
        //北側の壁との距離が目標距離以内なら全停止
        omuni_state = OMN_STOP;
        vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
        omuni_end_flag = 1;
      } else if (err_e <= 0) {
        //東側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_e);
        vel_ctrl_set(0, vel_ref + adj_vel, 0, vel_ref - adj_vel);
      } else if (err_e >= 0) {
        //東側の壁から離れている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_e);
        vel_ctrl_set(0, vel_ref - adj_vel, 0, vel_ref + adj_vel);
      }
      break;

    case OMN_NDW: //西側の壁のみを基準にして北向きに走行する場合
      omuni_speed_curr = (v_n + v_s) / 2.0;
      err_w = distWest.getCM() - dist_wall_w;  //壁との距離
      err_n = distNorth.getCM() - dist_wall_n;
      ratio = err_n / dist_vel_down;  //減速率
      if (ratio < 0.0) {
        ratio = 0.0;
      }
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (err_n <= 0) {
        //北側の壁との距離が目標距離以内なら全停止
        omuni_state = OMN_STOP;
        vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
        omuni_end_flag = 1;
      } else if (err_w <= 0) {
        //西側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_w);
        vel_ctrl_set(0, vel_ref - adj_vel, 0, vel_ref + adj_vel);
      } else if (err_w >= 0) {
        //西側の壁から離れている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_w);
        vel_ctrl_set(0, vel_ref + adj_vel, 0, vel_ref - adj_vel);
      }
      break;

    case OMN_EDS: //南側の壁のみを基準にして東向きに走行する場合
      omuni_speed_curr = (v_n + v_s) / 2.0;
      err_e = distEast.getCM() - dist_wall_e;  //壁との距離
      err_s = distSouth.getCM() - dist_wall_s;
      ratio = err_e / dist_vel_down;  //減速率
      if (ratio < 0.0) {
        ratio = 0.0;
      }
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (err_e <= 0) {
        //東側の壁との距離が目標距離以内なら全停止
        omuni_state = OMN_STOP;
        vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
        omuni_end_flag = 1;
      } else if (err_s <= 0) {
        //南側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_s);
        vel_ctrl_set(vel_ref - adj_vel, 0, vel_ref + adj_vel, 0);
      } else if (err_s >= 0) {
        //南側の壁から離れている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_s);
        vel_ctrl_set(vel_ref + adj_vel, 0, vel_ref - adj_vel, 0);
      }
      break;

    case OMN_EDN: //北側の壁のみを基準にして東向きに走行する場合
      omuni_speed_curr = (v_n + v_s) / 2.0;
      err_e = distEast.getCM() - dist_wall_e;  //壁との距離
      err_n = distNorth.getCM() - dist_wall_n;
      ratio = err_e / dist_vel_down;  //減速率
      if (ratio < 0.0) {
        ratio = 0.0;
      }
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (err_e <= 0) {
        //東側の壁との距離が目標距離以内なら全停止
        omuni_state = OMN_STOP;
        vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
        omuni_end_flag = 1;
      } else if (err_n <= 0) {
        //北側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_n);
        vel_ctrl_set(vel_ref + adj_vel, 0, vel_ref - adj_vel, 0);
      } else if (err_n >= 0) {
        //北側の壁から離れている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_n);
        vel_ctrl_set(vel_ref - adj_vel, 0, vel_ref + adj_vel, 0);
      }
      break;

    case OMN_SDE: //東側の壁のみを基準にして南向きに走行する場合
      omuni_speed_curr = (v_e + v_w) / 2.0;
      err_e = distEast.getCM() - dist_wall_e;  //壁との距離
      err_s = distSouth.getCM() - dist_wall_s;
      ratio = err_s / dist_vel_down;  //減速率
      if (ratio < 0.0) {
        ratio = 0.0;
      }
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (err_s <= 0) {
        //南側の壁との距離が目標距離以内なら全停止
        omuni_state = OMN_STOP;
        vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
        omuni_end_flag = 1;
      } else if (err_e <= 0) {
        //東側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_e);
        vel_ctrl_set(0, -vel_ref - adj_vel, 0, -vel_ref + adj_vel);
      } else if (err_e >= 0) {
        //東側の壁から離れている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_e);
        vel_ctrl_set(0, -vel_ref + adj_vel, 0, -vel_ref - adj_vel);
      }
      break;

    case OMN_SDW: //西側の壁のみを基準にして南向きに走行する場合
      omuni_speed_curr = (v_e + v_w) / 2.0;
      err_w = distWest.getCM() - dist_wall_w;  //壁との距離
      err_s = distSouth.getCM() - dist_wall_s;
      ratio = err_s / dist_vel_down;  //減速率
      if (ratio < 0.0) {
        ratio = 0.0;
      }
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (err_s <= 0) {
        //南側の壁との距離が目標距離以内なら全停止
        omuni_state = OMN_STOP;
        vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
        omuni_end_flag = 1;
      } else if (err_w <= 0) {
        //西側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_w);
        vel_ctrl_set(0, -vel_ref + adj_vel, 0, -vel_ref - adj_vel);
      } else if (err_w >= 0) {
        //東側の壁から離れている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_w);
        vel_ctrl_set(0, -vel_ref - adj_vel, 0, -vel_ref + adj_vel);
      }
      break;

    case OMN_WDS: //南側の壁のみを基準にして西向きに走行する場合
      omuni_speed_curr = (v_n + v_s) / 2.0;
      err_w = distWest.getCM() - dist_wall_w;  //壁との距離
      err_s = distSouth.getCM() - dist_wall_s;
      ratio = err_w / dist_vel_down;  //減速率
      if (ratio < 0.0) {
        ratio = 0.0;
      }
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (err_w <= 0) {
        //西側の壁との距離が目標距離以内なら全停止
        omuni_state = OMN_STOP;
        vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
        omuni_end_flag = 1;
      } else if (err_s <= 0) {
        //南側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_s);
        vel_ctrl_set(-vel_ref + adj_vel, 0, -vel_ref - adj_vel, 0);
      } else if (err_s >= 0) {
        //南側の壁から離れている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_s);
        vel_ctrl_set(-vel_ref - adj_vel, 0, -vel_ref + adj_vel, 0);
      }
      break;

    case OMN_WDN: //北側の壁のみを基準にして西向きに走行する場合
      omuni_speed_curr = (v_n + v_s) / 2.0;
      err_w = distWest.getCM() - dist_wall_w;  //壁との距離
      err_n = distNorth.getCM() - dist_wall_n;
      ratio = err_w / dist_vel_down;  //減速率
      if (ratio < 0.0) {
        ratio = 0.0;
      }
      if (ratio > 1.0) {
        ratio = 1.0;
      }
      if (err_w <= 0) {
        //南側の壁との距離が目標距離以内なら全停止
        omuni_state = OMN_STOP;
        vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
        omuni_end_flag = 1;
      } else if (err_n <= 0) {
        //南側の壁に近づいている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_n);
        vel_ctrl_set(-vel_ref - adj_vel, 0, -vel_ref + adj_vel, 0);
      } else if (err_n >= 0) {
        //南側の壁から離れている場合
        vel_ref = omuni_speed_ref * ratio;
        adj_vel = Kp * abs(err_n);
        vel_ctrl_set(-vel_ref + adj_vel, 0, -vel_ref - adj_vel, 0);
      }
      break;
  }
}

void omuni_ctrl_set(omuni_state_t state, double speed, int dist_wall) {
  omuni_state = state;
  switch (state){
    case OMN_N:
    case OMN_NDE:
    case OMN_NDW:
      dist_wall_n = dist_wall;
      break;
    case OMN_E:
    case OMN_EDN:
    case OMN_EDS:
      dist_wall_e = dist_wall;
      break;
    case OMN_S:
    case OMN_SDE:
    case OMN_SDW:
      dist_wall_s = dist_wall;
      break;
    case OMN_W:
    case OMN_WDN:
    case OMN_WDS:
      dist_wall_w = dist_wall;
      break;
  }
  omuni_speed_ref = abs(speed);
  vel_ctrl_reset();
  omuni_end_flag = 0;
}