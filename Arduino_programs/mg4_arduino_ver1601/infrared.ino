void infrared_open(void) {
	Serial2.begin(BAUDRATE);

	// バッファクリア
	while(Serial2.available() > 0){
		Serial2.read();
	}
}

