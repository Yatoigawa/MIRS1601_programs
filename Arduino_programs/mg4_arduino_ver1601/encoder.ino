// 割り込みに使用する変数 (volatileをつけて宣言)
static volatile long count_n = 0;
static volatile long count_e = 0;
static volatile long count_s = 0;
static volatile long count_w = 0;


void encoder_open() {
  pinMode(ENC_N1, INPUT);
  pinMode(ENC_N2, INPUT);
  pinMode(ENC_E1, INPUT);
  pinMode(ENC_E2, INPUT);
  pinMode(ENC_S1, INPUT);
  pinMode(ENC_S2, INPUT);
  pinMode(ENC_W1, INPUT);
  pinMode(ENC_W2, INPUT);
  digitalWrite(ENC_N1, HIGH);
  digitalWrite(ENC_N2, HIGH);
  digitalWrite(ENC_E1, HIGH);
  digitalWrite(ENC_E2, HIGH);
  digitalWrite(ENC_S1, HIGH);
  digitalWrite(ENC_S2, HIGH);
  digitalWrite(ENC_W1, HIGH);
  digitalWrite(ENC_W2, HIGH);
  
  
  
  attachInterrupt(0, enc_change_n, CHANGE);
  attachInterrupt(1, enc_change_e, CHANGE);
  attachInterrupt(2, enc_change_s, CHANGE);
  attachInterrupt(3, enc_change_w, CHANGE);
}

void encoder_get(long *cnt_n, long *cnt_e, long *cnt_s, long *cnt_w) {
  *cnt_n = count_n;
  *cnt_e = count_e;
  *cnt_s = count_s;
  *cnt_w = count_w;

  // エンコーダ回転方向の補正
  //*cnt_n *= -1;
  *cnt_e *= -1;
  //*cnt_s *= -1;
  *cnt_w *= -1;
}

void encoder_reset() {
  count_n = 0;
  count_e = 0;
  count_s = 0;
  count_w = 0;
}

static void enc_change_n() {
  int a_curr, b_curr;
  static int a_prev = LOW, b_prev = LOW;

  a_curr = digitalRead(ENC_N1);
  b_curr = digitalRead(ENC_N2);

  // 正転 : [L, H]→(L, L)→[H, L]→(H, H)→[L, H]
  if (a_prev ==  LOW && b_prev == HIGH && a_curr == HIGH && b_curr ==  LOW) count_n++;
  if (a_prev == HIGH && b_prev ==  LOW && a_curr ==  LOW && b_curr == HIGH) count_n++;

  // 逆転 : [L, L]→(L, H)→[H, H]→(H, L)→[L, L]
  if (a_prev ==  LOW && b_prev ==  LOW && a_curr == HIGH && b_curr == HIGH) count_n--;
  if (a_prev == HIGH && b_prev == HIGH && a_curr ==  LOW && b_curr ==  LOW) count_n--;

  a_prev = a_curr;
  b_prev = b_curr;
}

static void enc_change_e() {
  int a_curr, b_curr;
  static int a_prev = LOW, b_prev = LOW;

  a_curr = digitalRead(ENC_E1);
  b_curr = digitalRead(ENC_E2);

  // 正転 : [L, H]→(L, L)→[H, L]→(H, H)→[L, H]
  if (a_prev ==  LOW && b_prev == HIGH && a_curr == HIGH && b_curr ==  LOW) count_e++;
  if (a_prev == HIGH && b_prev ==  LOW && a_curr ==  LOW && b_curr == HIGH) count_e++;

  // 逆転 : [L, L]→(L, H)→[H, H]→(H, L)→[L, L]
  if (a_prev ==  LOW && b_prev ==  LOW && a_curr == HIGH && b_curr == HIGH) count_e--;
  if (a_prev == HIGH && b_prev == HIGH && a_curr ==  LOW && b_curr ==  LOW) count_e--;

  a_prev = a_curr;
  b_prev = b_curr;
}

static void enc_change_s() {
  int a_curr, b_curr;
  static int a_prev = LOW, b_prev = LOW;

  a_curr = digitalRead(ENC_S1);
  b_curr = digitalRead(ENC_S2);

  // 正転 : [L, H]→(L, L)→[H, L]→(H, H)→[L, H]
  if (a_prev ==  LOW && b_prev == HIGH && a_curr == HIGH && b_curr ==  LOW) count_s++;
  if (a_prev == HIGH && b_prev ==  LOW && a_curr ==  LOW && b_curr == HIGH) count_s++;

  // 逆転 : [L, L]→(L, H)→[H, H]→(H, L)→[L, L]
  if (a_prev ==  LOW && b_prev ==  LOW && a_curr == HIGH && b_curr == HIGH) count_s--;
  if (a_prev == HIGH && b_prev == HIGH && a_curr ==  LOW && b_curr ==  LOW) count_s--;

  a_prev = a_curr;
  b_prev = b_curr;
}

static void enc_change_w() {
  int a_curr, b_curr;
  static int a_prev = LOW, b_prev = LOW;

  a_curr = digitalRead(ENC_W1);
  b_curr = digitalRead(ENC_W2);

  // 正転 : [L, H]→(L, L)→[H, L]→(H, H)→[L, H]
  if (a_prev ==  LOW && b_prev == HIGH && a_curr == HIGH && b_curr ==  LOW) count_w++;
  if (a_prev == HIGH && b_prev ==  LOW && a_curr ==  LOW && b_curr == HIGH) count_w++;

  // 逆転 : [L, L]→(L, H)→[H, H]→(H, L)→[L, L]
  if (a_prev ==  LOW && b_prev ==  LOW && a_curr == HIGH && b_curr == HIGH) count_w--;
  if (a_prev == HIGH && b_prev == HIGH && a_curr ==  LOW && b_curr ==  LOW) count_w--;

  a_prev = a_curr;
  b_prev = b_curr;
}
