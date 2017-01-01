/*
 * USART_ver1.h
 *
 *    Created: 2014/02/17 8:26:02
 * LastUpdate: 2015/06/18 21:30:00
 *     Author: Shunya.Iida
 *       Type: ATmega328P family
 *    Version: 1.1
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

#ifndef UsartReadMax
#define UsartReadMax 10
#endif


#if UsartReadMax>200
#error "UsartReadMaxの値が大きすぎます"
#endif


#ifndef USART_VER_1_H
#define USART_VER_1_H

uint8_t Usart_Init(uint8_t baudratemode,uint16_t baudrate);
void Usart_Begin(void);
void Usart_End(void);
void Usart_Write(uint8_t writedata);
uint8_t Usart_Read (uint8_t *_readdata);
uint8_t Usart_ReadDataBaff(uint8_t *_readdata,uint8_t _mode);
uint8_t Usart_Available(void);

uint8_t Usart_Init(uint8_t baudratemode,uint16_t baudrate){
	
	UCSR0A=0x00;
	UCSR0B=0x00;
	UCSR0C=0x00;
	if(baudrate>0x0FFF){
		return 0xFE;
	}
	switch(baudratemode){
	case 1: UCSR0A=(_BV(U2X0));
			break;
	case 0: break;
	default: return 0xFF;
				break;
	}
	UBRR0=baudrate;
	UCSR0C=(_BV(UCSZ01) | _BV(UCSZ00) );
	UCSR0B=_BV(RXCIE0);
	return 0;
}

void Usart_Begin(void){
	UCSR0B|=( _BV(RXEN0) | _BV(TXEN0) );
}

void Usart_End(void){
	while( !(UCSR0A & _BV(UDRE0)));
	UCSR0B&=~( _BV(RXEN0) | _BV(TXEN0) );
}

uint8_t Usart_Read (uint8_t *_readdata){
	
	uint8_t _mode;
	uint8_t i;
	_mode=Usart_ReadDataBaff(&i,1);
	*_readdata=i;
	Usart_Write(i);
	return _mode;
}

void Usart_Write(uint8_t _writedata){
	while( !(UCSR0A & _BV(UDRE0))){;}
	UDR0=_writedata;
}

uint8_t Usart_Available(void){
	uint8_t i;
	return Usart_ReadDataBaff(&i,2);
}

uint8_t Usart_ReadDataBaff(uint8_t *_readdata,uint8_t _mode){
	
	static uint8_t _buffamout=0;
	static uint8_t UsartReadDataBaffer[UsartReadMax];

	uint8_t _usart_output=0;
	uint8_t i;
	
	if(_mode==0){		//書き込みモード
		if(UsartReadMax>_buffamout){
			UsartReadDataBaffer[_buffamout]=*_readdata;
		}else{
			for(i=0;i<UsartReadMax;i++){
				UsartReadDataBaffer[i]=UsartReadDataBaffer[i+1];
			}
			UsartReadDataBaffer[UsartReadMax-1]=*_readdata;
		}
		_buffamout++;
		
	}else if(_mode==1){		//読み込みモード
		if(_buffamout<=0){
			_buffamout=0;
			_usart_output=0;
		}else{
			*_readdata=UsartReadDataBaffer[0];
			_usart_output=_buffamout;
			if(_buffamout<UsartReadMax){	//ReadDataがオーバーフローしていないとき
				for(i=0;i<_buffamout;i++){	
					UsartReadDataBaffer[i]=UsartReadDataBaffer[i+1];
				}
			}
			else{		//オーバーフローしているまたはぴったりのとき
				_buffamout=UsartReadMax-1;
				for(i=1;i<_buffamout;i++){
					UsartReadDataBaffer[i-1]=UsartReadDataBaffer[i];
				}
			}
			_buffamout--;
		}
	}
	else if(_mode == 2){ //確認モード
		_usart_output = _buffamout;
	}
	return _usart_output;
}

ISR(USART_RX_vect){
	uint8_t _Usart_UDR;
	_Usart_UDR=UDR0;
	Usart_ReadDataBaff(&_Usart_UDR,0);
}

#endif

/*********************************************************
 Copyright (c) 2014-2015  Shunya Iida
 All rights reserved.
 
 本プログラムは上記の者(以下「著作者」という。)によって製作されています。
 本プログラムは
  ・著作者が本プログラムにおける全ての行為、損害について一切の責任を負わないこと
  ・改変後のプログラムにも著作者および免責事項を含めること
  ・改変者は上記の著作者に名を記すこと
 上記2点を条件に本プログラムの使用、複製、改変、頒布、複製等の
 一切の行為を無断で行うことを認めます。
 *******************************************************/

