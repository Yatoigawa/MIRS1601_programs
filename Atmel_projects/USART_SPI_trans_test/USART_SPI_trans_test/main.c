/*
 * USART_SPI_trans_test.c
 *
 * Created: 2016/12/30 18:23:20
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
	SPI_master_init();

	// SS pin -> PB2
	DDRB = _BV(PB2);

	// 16MHz，115.2k[bps] -> See Datasheet
	Usart_Init(1, 16);

	// Set Enable Interrupt
	sei();

	// USART start
	Usart_Begin();
}


int main(void) {
	uint8_t i,readData, sendData[2];
	setup();
	while (1) {
		if(Usart_Available() > 0) {
			i = Usart_Read(&readData);
			if (i != 0x00) {
				sendData[0] = readData - 0x80 + 0xF0;
				sendData[1] = readData - 0x80 + 0xC0;
				Usart_Write(0xA4);			// 先頭バイト指定
				Usart_Write(sendData[0]);
				Usart_Write(sendData[1]);
			}
		}
		_delay_ms(5);
	}
}