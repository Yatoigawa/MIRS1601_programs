<io.ino>
void io_open()
その他I/Oポートの設定

void io_set_led(int val)
LEDの操作

int io_get_led()
LEDの状態取得

int io_get_sw()
タッチスイッチの状態取得

double io_get_batt()
バッテリ電圧の取得

<encoder.ino>
void encoder_open()
エンコーダで使用するポートの設定

void encoder_get(long *cnt_l, long *cnt_r)
エンコーダ値の取得

void encoder_reset()
エンコーダのリセット

<distance.c>
void distance_get(double *dist_l, double *dist_r)
走行距離の取得

<motor.ino>
void motor_open()
モータで使用するポートの設定

void motor_set(int pwm_l, int pwm_r)
モータのPWM動作

<vel_ctrl.c>
void vel_ctrl_execute()
速度制御の実行

void vel_ctrl_set(double vel_l, double vel_r)
目標速度の入力

void vel_ctrl_set(double *vel_l, double *vel_r)
現在の速度の取得

void vel_ctrl_reset()
走行制御モジュールの内部データのリセット

<run_ctrl.c>
void run_ctrl_cancel()
走行制御スレッドの実行

void run_ctrl_set(run_state_t state, double speed, double dist)
走行モード、目標速度、目標距離の入力

void run_ctrl_get(run_state_t *run_state, double *speed, double *dist)
現在の走行モード、目標速度、目標距離の取得
