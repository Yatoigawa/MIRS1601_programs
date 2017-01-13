void cpu_open(void){
  Serial.begin(115200);

  // バッファクリア
  while (Serial.available() > 0) {
    Serial.read();
  }
}

int cpu_read(){
  int i;
  while(Serial.available() > 0){
    
  }
}

