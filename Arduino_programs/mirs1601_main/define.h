#include <Arduino.h>
#include <stdlib.h>

#define DEBUG_MODE

/* 変数型の定義 */

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

typedef union {
  uint16_t val;
  struct {
    uint8_t lsb;
    uint8_t msb;
  };
} infrared_data_t;

int infrared_i = 0;

const byte forward       = B01010000;
const byte backward      = B10010000;
const byte right         = B00001001;
const byte left          = B00000110;
const byte rightForward  = B01101001;
const byte leftForward   = B10011001;
const byte rightBackward = B01100110;
const byte leftBackward  = B10010110;


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
#define MTR_S1 35
#define MTR_S2 36
#define MTR_E1 37
#define MTR_E2 38
#define MTR_W1 39
#define MTR_W2 40
//USS
#define USS_N 25
#define USS_S 26
#define USS_E 27
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
#define T_CTRL      20 // 動作周期 [ms]
#define T_CTRL_VEL  24.6

#define R_TIRE      6.25  // タイヤ半径 [cm]
#define D_TIRE      25.0  // タイヤ間隔 [cm]
#define ENC_RANGE   360/2   // エンコーダ分解能 (A相立上り/立下りを利用するため2倍)
#define T_E_RATIO   2.0   // タイヤに対するエンコーダの回転比
#define E_W_RATIO   1.0   // 東タイヤに対する西タイヤの回転比
#define N_S_RATIO   1.0   // 北タイヤに対する南タイヤの回転比

