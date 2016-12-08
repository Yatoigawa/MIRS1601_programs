/* 変数型の定義 */
typedef enum {
  STP = 0,
  STR,
  ROT
} run_state_t;

typedef struct {
  unsigned char val[7];
} serial_data_t;

typedef struct {
  unsigned char val[6];
} middle_data_t;

typedef struct {
  signed short val[3];
} command_data_t;

/* ピン配置 */
#define PIN_ENC_A_L  2
#define PIN_ENC_B_L  4
#define PIN_ENC_A_R  3
#define PIN_ENC_B_R  7
#define PIN_DIR_L    8
#define PIN_PWM_L    9
#define PIN_DIR_R   12
#define PIN_PWM_R   11
#define PIN_SW      10
#define PIN_LED     13
#define PIN_BATT    19

/* パラメータ */
#define T_CTRL 10 // 動作周期 [ms]

#define R_TIRE     3.2    // タイヤ半径 [cm]
#define D_TIRE    25.0    // タイヤ間隔 [cm]
#define ENC_RANGE (100*2) // エンコーダ分解能 (A相立上り/立下りを利用するため2倍)
#define T_E_RATIO 16.0    // タイヤに対するエンコーダの回転比
#define L_R_RATIO  1.0    // 左タイヤに対する右タイヤの回転比

#define V_RATIO 0.25 // バッテリ入力の分圧比
