static infrared_data_t infrared_data;

void infrared_open(void) {
	Serial2.begin(115200);

	// バッファクリア
	while(Serial2.available() > 0){
		Serial2.read();
	}
}

void infrared_serial_task(void){
  int i = 0;
  Serial2.write(i + 0x80);
  while(!(Serial2.available() > 2));
  if(Serial2.read() == 0xA4){
    infrared_data.msb = (Serial2.read() & 0x0F);
    infrared_data.lsb =  Serial2.read();
  }
  delay(10);
  yield();
}

