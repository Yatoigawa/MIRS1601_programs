static run_state_t run_state = STOP;
static double speed_ref = 0.0;
static double speed_curr = 0.0;
static double dist_ref = 0.0;
static double dist_curr = 0.0;

void run_ctrl_execute() {
	// 直進制御において減速を開始する距離 [cm]
	const double dist_vel_down = 0.0;

	// 回転制御において減速を開始する角度 [deg]
	const double angle_vel_down = 0.0;

	// 直進制御における左右のタイヤの距離差の補正ゲイン
	const double Ks = 40.0;

	// 回転制御における左右のタイヤの距離差の補正ゲイン
	const double Kr = 0.0;

	int sign;
	double d_n, d_s, d_e, d_w, v_n, v_s, v_e, v_w, ratio, vel_ref, vel_mod;

	// 負の指令値に対応
	if (dist_ref >= 0.0) {
		sign = 1;
	}
	else {
		sign = -1;
	}

	distance_get(&d_n, &d_s, &d_e, &d_w);
	vel_ctrl_get(&v_n, &v_s, &v_e, &v_w);

	switch (run_state) {
	case STOP:
		//全停止
		vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
		break;

	case STR_FB:
		//機体の前後方向に直進するモード　動くモーターはEとW
		dist_curr = (d_e + d_w) / 2.0;
		speed_curr = (v_e + v_w) / 2.0 * sign;

		// 減速率
		ratio = sign * (dist_ref - dist_curr) / dist_vel_down;
		if (ratio < 0.0) ratio = 0.0;
		if (ratio > 1.0) ratio = 1.0;

		if (speed_ref == 0.0 || dist_ref == 0.0 || ratio == 0.0) {
			run_state = STOP;
			vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
		}
		else {
			// 減速の実行
			vel_ref = sign * speed_ref * ratio;

			// 左右のタイヤの距離差の補正
			vel_mod = (d_e - d_w) * Ks;

			vel_ctrl_set(0.0, (vel_ref - vel_mod), 0.0, (vel_ref + vel_mod));
		}

		break;

	case STR_LR:
		//機体の左右方向に直進するモード　動くモーターはNとS
		dist_curr = (d_n + d_s) / 2.0;
		speed_curr = (v_n + v_s) / 2.0 * sign;

		// 減速率
		ratio = sign * (dist_ref - dist_curr) / dist_vel_down;
		if (ratio < 0.0) ratio = 0.0;
		if (ratio > 1.0) ratio = 1.0;

		if (speed_ref == 0.0 || dist_ref == 0.0 || ratio == 0.0) {
			run_state = STOP;
			vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
		}
		else {
			// 減速の実行
			vel_ref = sign * speed_ref * ratio;

			// 左右のタイヤの距離差の補正
			vel_mod = (d_n - d_s) * Ks;

			vel_ctrl_set((vel_ref - vel_mod), 0.0, (vel_ref + vel_mod), 0.0);
		}

		break;

	case STR_FR_BL:
		//機体の右前、左後（北東と南西）方向に直進するモード　北東を正とする　動くモーターはNとEが正転 SとWが逆転
		dist_curr = (sqrt(pow(d_n,2.0) + pow(d_e,2.0)) + sqrt(pow(d_s,2.0) + pow(d_w,2.0))) / 2.0;
		speed_curr = (sqrt(pow(v_n,2.0) + pow(v_e,2.0)) + sqrt(pow(v_s,2.0) + pow(v_w,2.0))) / 2.0 * sign;

		// 減速率
		ratio = sign * (dist_ref - dist_curr) / dist_vel_down;
		if (ratio < 0.0) ratio = 0.0;
		if (ratio > 1.0) ratio = 1.0;

		if (speed_ref == 0.0 || dist_ref == 0.0 || ratio == 0.0) {
			run_state = STOP;
			vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
		}
		else {
			// 減速の実行
			vel_ref = sign * speed_ref * ratio;

			// 左右のタイヤの距離差の補正
			vel_mod = (sqrt(pow(d_n,2.0) + pow(d_e,2.0)) - sqrt(pow(d_s,2.0) + pow(d_w,2.0))) * Ks;

			vel_ctrl_set((vel_ref - vel_mod), (vel_ref - vel_mod), -(vel_ref + vel_mod), -(vel_ref - vel_mod));
		}

		break;

	case STR_FL_BR:
		//機体の左前、右後（北西と南東）方向に直進するモード　北東を正とする　動くモーターはNとEが正転 SとWが逆転
		dist_curr = (d_n + d_w - d_s - d_e) / 2.0;
		speed_curr = (v_n + v_w - v_s - v_e) / 2.0 * sign;

		// 減速率
		ratio = sign * (dist_ref - dist_curr) / dist_vel_down;
		if (ratio < 0.0) ratio = 0.0;
		if (ratio > 1.0) ratio = 1.0;

		if (speed_ref == 0.0 || dist_ref == 0.0 || ratio == 0.0) {
			run_state = STOP;
			vel_ctrl_set(0.0, 0.0, 0.0, 0.0);
		}
		else {
			// 減速の実行
			vel_ref = sign * speed_ref * ratio;

			// 左右のタイヤの距離差の補正
			vel_mod = (sqrt(pow(d_n,2.0) + pow(d_w,2.0)) - sqrt(pow(d_s,2.0) + pow(d_e,2.0))) * Ks;

			vel_ctrl_set((vel_ref - vel_mod), -(vel_ref - vel_mod), -(vel_ref + vel_mod), (vel_ref - vel_mod));
		}

		break;

	/*回転制御は行わないものとする。必要に駆られたら作る。
        case ROT:
		// 回転角度
		dist_curr = -(d_l - d_r) / D_TIRE * 180.0 / PI;
		speed_curr = -(v_l - v_r) / D_TIRE * 180.0 / PI * sign;

		// 減速率
		ratio = sign * (dist_ref - dist_curr) / angle_vel_down;
		if (ratio < 0.0) ratio = 0.0;
		if (ratio > 1.0) ratio = 1.0;

		if (speed_ref == 0.0 || dist_ref == 0.0 || ratio == 0.0) {
			run_state = STOP;
			vel_ctrl_set(0.0, 0.0);
		}
		else {
			// 減速の実行＆角速度指令値→速度指令値に変換
			vel_ref = sign * speed_ref * ratio * D_TIRE / 2.0 * PI / 180.0;

			// 左右のタイヤの距離差の補正
			vel_mod = -(d_l + d_r) * Kr;

			vel_ctrl_set(-(vel_ref - vel_mod), (vel_ref + vel_mod));
		}

		break;
        */
	}
}

void run_ctrl_set(run_state_t state, double speed, double dist) {
	run_state = state;
	speed_ref = abs(speed);
	dist_ref = dist;
	vel_ctrl_reset();
}

void run_ctrl_get(run_state_t *state, double *speed, double *dist) {
	*state = run_state;
	*speed = speed_curr;
	*dist = dist_curr;
}
