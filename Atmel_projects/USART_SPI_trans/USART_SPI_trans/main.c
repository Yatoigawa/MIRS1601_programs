/*
 * USART_SPI_trans.c
 *
 * Created: 2016/12/24 22:35:15
 * Author : Yatoigawa
 */ 

#define F_CPU			16000000UL		// set CPU Clock: 16MHz
#define UsartReadMax	100				// Received Data Buffer size : 100

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART_ver1.h"
#include "SPI_master.h"

// prototype declaration
void setup(void);

void setup(void){
	// DDRB = (1 << DDB3) | (1 << DDB5);
	// PB3(MOSI) and PB5(SCK) are output setting.
	InitSpiMaster();

	// 16MHz，115.2k[bps] -> See Datasheet
	Usart_Init(1, 16);

	// Set Enable Interrupt
	sei();

	// USART start
	Usart_Begin();
}


int main(void) {
	uint8_t i;
	uint8_t readdata;
	setup();
	while (1) {
		// 先頭ビットチェックループ
		while(1){
			if(Usart_Available() > 1){
				i = Usart_Read(&readdata);
				if(readdata == 0xA4){	// 先頭ビットチェック
					break;
				}
			}
		}
		i = Usart_Read(&readdata);

	}
}

