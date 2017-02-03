static infrared_data_t infrared_data[4];

void infrared_open(void) {
  Serial2.begin(115200);

  // バッファクリア
  while(Serial2.available() > 0){
    Serial2.read();
  }
}

void infrared_serial_task(void){
  Serial2.write(infrared_i + 0x80);
  while(!(Serial2.available() > 3)){
    Serial.println("waiting...");
    delay(50);
  }
  Serial.println("Success!");
  if(Serial2.read() == 0xA4){
    infrared_data[infrared_i].msb = (Serial2.read() & 0x0F);
    infrared_data[infrared_i].lsb =  Serial2.read();
  }
  infrared_i++;
  if(infrared_i > 4){
    infrared_i = 0;
  }
  delay(10);
  yield();
}

