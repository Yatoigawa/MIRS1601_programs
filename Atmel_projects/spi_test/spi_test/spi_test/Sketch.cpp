/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio

Usart usart;

void setup() {
  usart.US_WPMR |= (US_WPMR_WPEN);
  usart.US_MR   |= (US_MR_USART_MODE_SPI_MASTER);
  pinMode(13, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
