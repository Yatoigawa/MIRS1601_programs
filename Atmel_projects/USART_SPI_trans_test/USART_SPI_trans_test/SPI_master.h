/*
 * SPI_master.h
 *
 * Created		: 2016/12/28
 * Original		: easy lab
 * Changed by	: Yatoigawa
 */

//SPI Master Sample Code
//Author: easy lab
//Created: 2014.11.02

#include <avr/io.h>
 
void SPI_master_init(void) { 
	//Set MOSI(PB3) and SCK(PB5) output, all others input in Port B
	DDRB = (1<<DDB3)|(1<<DDB5);
	//Enable SPI, Master, set clock rate fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	//Double SPI Speed -> fck/8 = 2MHz (fck = 16MHz)
	SPSR |= _BV(SPI2X);
}
 
void SPI_master_trans(uint8_t tData) {
	//Start transmission
	SPDR = tData;
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));
}
 
uint8_t SPI_master_recieve(void) {
	uint8_t rData;
	//Output Clock without data
	SPDR = 0;
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));
	//Receive 1 byte data
	rData = SPDR;
	return rData;
}
 
 // Arduino‚ÌSPI.transfer‚Æ“¯‹`‚ÌŠÖ”
uint8_t SPI_master_transfer(uint8_t tData) {
	//Start transmission
	SPDR = tData;
	// Wait for transmission complete
	asm volatile("nop");
	while(!(SPSR & (1<<SPIF)));
	//Receive 1 byte data
	return SPDR;
}