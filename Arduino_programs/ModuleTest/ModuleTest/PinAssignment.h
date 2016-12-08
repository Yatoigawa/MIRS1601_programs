/*
ピンファイル
バス回路のピン配置に基づいて設定しているのでピン番号を勝手に変えないでください
*/

//インクルードガード...重複インクルードを避ける
#ifndef __PINASSIGNMENT_H__
#define __PINASSIGNMENT_H__

#include "Arduino.h"

//TODO:適切なピン名に変更する
//MOTOR
#define MTR_1ENA 26 //Dingtal
#define MTR_1ENB 27
#define MTR_2ENA 29
#define MTR_2ENB 30
//#define MTR_A3 28
//#define MTR_B3 31
#define P_N1 2  //PWM
#define P_N2 3
#define P_E1 4
#define P_E2 5
#define P_S1 6
#define P_S2 7
#define P_W1 8
#define P_W2 9

//ENCODER
#define ENC_N1 32
#define ENC_N2 33
#define ENC_E1 34
#define ENC_E2 35
#define ENC_S1 36
#define ENC_S2 37
#define ENC_W1 38
#define ENC_W2 39

//USS
#define USS_N 40 //Dingtal
#define USS_E 41
#define USS_S 42
#define USS_W 43

//INFRARED
#define IR 22 //CS

//TAPELED
#define TL_0 44 //Digital
#define TL_1 45
#define TL_2 46

//MP3_A,MP3_B
#define MP3_1 23 //CS
#define MP3_2 24
#define MP3_3 25

#endif
