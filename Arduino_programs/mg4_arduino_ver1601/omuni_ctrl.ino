static omuni_state_t omuni_state = OMN_STOP; 
static double omuni_speed_ref = 0.0;
static double omuni_speed_curr = 0.0;

void omuni_ctrl_execute(){

  int uss_n = 1;
  int uss_e = 2;
  int uss_s = 3;
  int uss_w = 4;

  int dist_wall_n = 20; //北側の壁との目標距離
  int dist_wall_e  = 20; //東側の壁との目標距離
  int dist_wall_s = 20; //南側の壁との目標距離
  int dist_wall_w  = 20; //西側の壁との目標距離
  
  int err_n;  //北側の壁まで距離と現在地の差
  int err_e;  //東側の壁まで距離と現在地の差
  int err_s;  //南側の壁まで距離と現在地の差
  int err_w;  //西側の壁まで距離と現在地の差
  
  double adj_vel;      //加算or減算する修正値 adjust value
  double Kp = 1.0;     //差分距離err_Xと加減速補正add_velに対する比例ゲイン
  double dist_vel_down = 0.0; //残距離に応じて減速するための係数
  double  v_n, v_s, v_e, v_w, ratio, vel_ref;

  USS distNorth(uss_n);
  USS distEast(uss_e);
  USS distSouth(uss_e);
  USS distWest(uss_w);

  vel_ctrl_get(&v_n, &v_s, &v_e, &v_w);

  switch(omuni_state){
    
  case OMN_STOP:  //全停止
    vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
    break;
  
  case OMN_E:     //北と南側の壁を基準として東方向へ走行
    omuni_speed_curr = (v_n + v_s) / 2.0;
    err_n = dist_wall_n - distNorth.getCM();
    err_e = dist_wall_e - distEast.getCM();
    err_s = dist_wall_s - distSouth.getCM();
    ratio = err_e / dist_vel_down;  //減速率
    if (ratio < 0.0){
      ratio = 0.0;
    }
    if (ratio > 1.0){
      ratio = 1.0;
    }
    if(err_e <= dist_wall_e){
      //東側の壁との距離が目標距離以内なら全停止
      omuni_state = OMN_STOP;
      vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
    }else if(err_n >= dist_wall_n || err_s <= dist_wall_s){
      //北側の壁から離れ、南側の壁に近づいている場合
      vel_ref = omuni_speed_ref * ratio;
      adj_vel = Kp * (dist_wall_n + dist_wall_s) / 2; 
      vel_ctrl_set(vel_ref - adj_vel, 0, vel_ref + adj_vel, 0);
    }else if(err_n <= dist_wall_n || err_s >= dist_wall_s){
      //南側の壁から離れ、北側の壁に近づいている場合
      vel_ref = omuni_speed_ref * ratio;
      adj_vel = Kp * (dist_wall_n + dist_wall_s) / 2; 
      vel_ctrl_set(vel_ref + adj_vel, 0, vel_ref - adj_vel, 0);
    }
    break;

    case OMN_W:     //北と南側の壁を基準として西方向へ走行
    omuni_speed_curr = (v_n + v_s) / 2.0;
    err_n = dist_wall_n - distNorth.getCM();
    err_w = dist_wall_w - distWest.getCM();
    err_s = dist_wall_s - distSouth.getCM();
    ratio = err_w / dist_vel_down;  //減速率
    if (ratio < 0.0){
      ratio = 0.0;
    }
    if (ratio > 1.0){
      ratio = 1.0;
    }
    if(err_w <= dist_wall_w){
      //西側の壁との距離が目標距離以内なら全停止
      omuni_state = OMN_STOP;
      vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
    }else if(err_n >= dist_wall_n || err_s <= dist_wall_s){
      //北側の壁から離れ、南側の壁に近づいている場合
      vel_ref = omuni_speed_ref * ratio;
      adj_vel = Kp * (dist_wall_n + dist_wall_s) / 2; 
      vel_ctrl_set(-vel_ref + adj_vel, 0, -vel_ref - adj_vel, 0);
    }else if(err_n <= dist_wall_n || err_s >= dist_wall_s){
      //南側の壁から離れ、北側の壁に近づいている場合
      vel_ref = omuni_speed_ref * ratio;
      adj_vel = Kp * (dist_wall_n + dist_wall_s) / 2; 
      vel_ctrl_set(-vel_ref - adj_vel, 0, -vel_ref + adj_vel, 0);
    }
    break;

    case OMN_N:     //東と西側の壁を基準として北方向へ走行
    omuni_speed_curr = (v_e + v_w) / 2.0;
    err_n = dist_wall_n - distNorth.getCM();
    err_e = dist_wall_e - distEast.getCM();
    err_w = dist_wall_w - distWest.getCM();
    ratio = err_n / dist_vel_down;  //減速率
    if (ratio < 0.0){
      ratio = 0.0;
    }
    if (ratio > 1.0){
      ratio = 1.0;
    }
    if(err_n <= dist_wall_n){
      //北側の壁との距離が目標距離以内なら全停止
      omuni_state = OMN_STOP;
      vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
    }else if(err_e >= dist_wall_e || err_w <= dist_wall_e){
      //東側の壁から離れ、西側の壁に近づいている場合
      vel_ref = omuni_speed_ref * ratio;
      adj_vel = Kp * (dist_wall_n + dist_wall_s) / 2; 
      vel_ctrl_set(0, vel_ref - adj_vel, 0, vel_ref + adj_vel);
    }else if(err_e <= dist_wall_e || err_w >= dist_wall_w){
      //西側の壁から離れ、東側の壁に近づいている場合
      vel_ref = omuni_speed_ref * ratio;
      adj_vel = Kp * (dist_wall_n + dist_wall_s) / 2; 
      vel_ctrl_set(0, vel_ref + adj_vel, 0, vel_ref - adj_vel);
    }
    break;

    case OMN_S:     //東と西側の壁を基準として南方向へ走行
    omuni_speed_curr = (v_e + v_w) / 2.0;
    err_s = dist_wall_s - distSouth.getCM();
    err_e = dist_wall_e - distEast.getCM();
    err_w = dist_wall_w - distWest.getCM();
    ratio = err_s / dist_vel_down;  //減速率
    if (ratio < 0.0){
      ratio = 0.0;
    }
    if (ratio > 1.0){
      ratio = 1.0;
    }
    if(err_s <= dist_wall_s){
      //南側の壁との距離が目標距離以内なら全停止
      omuni_state = OMN_STOP;
      vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
    }else if(err_e >= dist_wall_e || err_w <= dist_wall_e){
      //東側の壁から離れ、西側の壁に近づいている場合
      vel_ref = omuni_speed_ref * ratio;
      adj_vel = Kp * (dist_wall_n + dist_wall_s) / 2; 
      vel_ctrl_set(0, -vel_ref + adj_vel, 0, -vel_ref - adj_vel);
    }else if(err_e <= dist_wall_e || err_w >= dist_wall_w){
      //西側の壁から離れ、東側の壁に近づいている場合
      vel_ref = omuni_speed_ref * ratio;
      adj_vel = Kp * (dist_wall_n + dist_wall_s) / 2; 
      vel_ctrl_set(0, -vel_ref - adj_vel, 0, -vel_ref + adj_vel);
    }
    break;    
  }  
}

void omuni_ctrl_set(omuni_state_t state, double speed) {
  omuni_state = state;
  omuni_speed_ref = abs(speed);
  vel_ctrl_reset();
}
