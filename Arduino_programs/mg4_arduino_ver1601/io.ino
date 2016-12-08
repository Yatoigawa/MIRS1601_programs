void io_open() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_SW, INPUT);
  pinMode(PIN_BATT, INPUT);
  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_SW, HIGH);
  digitalWrite(PIN_BATT, LOW);
}

void io_set_led(int val) {
  digitalWrite(PIN_LED, val);
}

int io_get_led() {
  return digitalRead(PIN_LED);
}

int io_get_sw() {
  return digitalRead(PIN_SW);
}

double io_get_batt() {
  return analogRead(PIN_BATT) * 5.0 / 1024.0 / V_RATIO;
}
