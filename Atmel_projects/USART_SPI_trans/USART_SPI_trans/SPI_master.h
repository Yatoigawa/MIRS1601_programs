 //SPI Master Sample Code
 //Target Device: ATmega328p
 //Author: easy labo
 //Created: 2014.11.02
 
 #include <avr/io.h>
 
 void InitSpiMaster(void)
 {
	 //Set MOSI(PB3) and SCK(PB5) output, all others input in Port B
	 DDRB = (1<<DDB3)|(1<<DDB5);
	 //Enable SPI, Master, set clock rate fck/16
	 SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	 //Double SPI Speed -> fck/8 = 2MHz (fck = 16MHz)
	 SPSR |= _BV(SPI2X);
 }
 
 void TransSpiMaster(char tData){
	 //Start transmission
	 SPDR = tData;
	 // Wait for transmission complete
	 while(!(SPSR & (1<<SPIF)));
 }
 
 char RecieveSpiMaster(void)
 {
	 char rData;
	 //Output Clock without data
	 SPDR = 0;
	 // Wait for transmission complete
	 while(!(SPSR & (1<<SPIF)));
	 //Receive 1 byte data
	 rData = SPDR;
	 return rData;
 }
 
 char TransceiverSpiMaster(char tData)
 {
	 char rData;
	 //Start transmission
	 SPDR = tData;
	 // Wait for transmission complete
	 while(!(SPSR & (1<<SPIF)));
	 //Receive 1 byte data
	 rData = SPDR;
	 return rData;
 }