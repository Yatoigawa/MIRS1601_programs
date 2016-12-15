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

/* 
 *  エレキ詳細設計書
 *  http://www2.denshi.numazu-ct.ac.jp/mirsdoc2/mirs1601/elec/num0001a/index.html 
 *  
 *  Atmel SAM3X / SAM3A Series datasheet
 *  http://www.atmel.com/Images/Atmel-11057-32-bit-Cortex-M3-Microcontroller-SAM3X-SAM3A_Datasheet.pdf
 */

/* パラメータ */
#define T_CTRL 10 // 動作周期 [ms]

#define R_TIRE     3.2    // タイヤ半径 [cm]
#define D_TIRE    25.0    // タイヤ間隔 [cm]
#define ENC_RANGE (100*2) // エンコーダ分解能 (A相立上り/立下りを利用するため2倍)
#define T_E_RATIO 16.0    // タイヤに対するエンコーダの回転比
#define L_R_RATIO  1.0    // 左タイヤに対する右タイヤの回転比

#define V_RATIO 0.25 // バッテリ入力の分圧比
