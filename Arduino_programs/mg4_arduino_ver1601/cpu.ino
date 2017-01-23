void cpu_open(void){
  Serial.begin(115200);

  // バッファクリア
  while (Serial.available() > 0) {
    Serial.read();
  }
}

void cpu_num_trans(uint8_t cam_no){
  uint8_t ret_data;
  Serial.write(0xA0);
  Serial.write(cam_no);
  while(true){
    if(Serial.available() > 0){
      if(Serial.read() == 'n'){
        ret_data = Serial.read();
        ret_data = Serial.read();
        break;
      }
    }
  }
}



