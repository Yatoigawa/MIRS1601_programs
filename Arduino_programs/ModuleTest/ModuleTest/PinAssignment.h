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
#define MTR_1ENA 4 //PWM
#define MTR_1ENB 5
#define MTR_2ENA 6
#define MTR_2ENB 7
#define MTR_N1 33  //Digital
#define MTR_N2 34
#define MTR_E1 35
#define MTR_E2 36
#define MTR_S1 37
#define MTR_S2 38
#define MTR_W1 39
#define MTR_W2 40

//ENCODER
#define ENC_N1 44
#define ENC_N2 45
#define ENC_E1 46
#define ENC_E2 47
#define ENC_S1 48
#define ENC_S2 49
#define ENC_W1 50
#define ENC_W2 51

//USS
#define USS_N 25 //Dingtal
#define USS_E 26
#define USS_S 27
#define USS_W 28

//IR_A,IR_B
#define IR_CS 23
#define IR_CLK 42

//TAPELED
#define TL_0 29 //Digital
#define TL_1 30
#define TL_2 32

//MP3_A,MP3_B
#define MP3_CS 24

#endif