void cpu_open(void){
  Serial.begin(BAUDRATE);

  // バッファクリア
  while (Serial.available() > 0) {
    Serial.read();
  }
}

int cpu_read(){
  int i;
  
}

