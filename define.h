#include <Arduino.h>
#include <stdlib.h>
#include "USS.h"
#include "L298N_omuni.h"
/* 変数型の定義 */
typedef enum {
  STOP = 0,
  STR_N,
  STR_E,
  STR_S,
  STR_W,
  STR_NE,
  STR_SW,
  STR_NW,
  STR_SE,
  ROT
} run_state_t;

typedef enum {
  OMN_STOP,
  OMN_N,
  OMN_E,
  OMN_S,
  OMN_W,
  OMN_NDE,
  OMN_NDW,
  OMN_EDS,
  OMN_EDN,
  OMN_SDE,
  OMN_SDW,
  OMN_WDS,
  OMN_WDN
} omuni_state_t;


static run_state_t run_state = STOP;
static omuni_state_t omuni_state = OMN_STOP;

typedef struct {
  unsigned char val[7];
} serial_data_t;

typedef struct {
  unsigned char val[6];
} middle_data_t;

typedef struct {
  signed short val[3];
} command_data_t;

typedef union {
  uint16_t val;
  struct {
    uint8_t lsb;
    uint8_t msb;
  };
} infrared_data_t;

/* ピン配置 */
//ENCODER
#define ENC_N1 44
#define ENC_N2 45
#define ENC_E1 46
#define ENC_E2 47
#define ENC_S1 48
#define ENC_S2 49
#define ENC_W1 50
#define ENC_W2 51
//MOTOR
#define MTR_1ENA 4 //PWM N
#define MTR_1ENB 5 //    S
#define MTR_2ENA 6 //    E
#define MTR_2ENB 7 //    W
#define MTR_N1 33  //Digital
#define MTR_N2 34
#define MTR_E1 35
#define MTR_E2 36
#define MTR_S1 37
#define MTR_S2 38
#define MTR_W1 39
#define MTR_W2 40
//USS
#define USS_N 25
#define USS_E 26
#define USS_S 27
#define USS_W 28
//IR_A,IR_B
#define IR_CS 23
#define IR_CLK 42
//TAPELED
#define TL_0 29
#define TL_1 30
#define TL_2 32
//MP3_A,MP3_B
#define MP3_CS 24

#define PIN_SW      10
#define PIN_LED     13
#define PIN_BATT    19

/* パラメータ */
#define T_CTRL 10 // 動作周期 [ms]

#define R_TIRE      6.75  // タイヤ半径 [cm]
#define D_TIRE      25.0  // タイヤ間隔 [cm]
#define ENC_RANGE   360/2   // エンコーダ分解能 (A相立上り/立下りを利用するため2倍)
#define T_E_RATIO   2.0   // タイヤに対するエンコーダの回転比
#define E_W_RATIO   1.0   // 東タイヤに対する西タイヤの回転比
#define N_S_RATIO   1.0   // 北タイヤに対する南タイヤの回転比

#define V_RATIO 0.25 // バッテリ入力の分圧比
