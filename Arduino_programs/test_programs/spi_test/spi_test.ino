Usart usart;

void setup() {
  usart.US_WPMR |= (US_WPMR_WPEN);
  usart.US_MR   |= (US_MR_USART_MODE_SPI_MASTER);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
