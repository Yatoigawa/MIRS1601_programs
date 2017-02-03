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

  attachInterrupt(digitalPinToInterrupt(44), enc_change_n, CHANGE);
  attachInterrupt(digitalPinToInterrupt(46), enc_change_e, CHANGE);
  attachInterrupt(digitalPinToInterrupt(48), enc_change_s, CHANGE);
  attachInterrupt(digitalPinToInterrupt(50), enc_change_w, CHANGE);
}

void encoder_get(long *cnt_n, long *cnt_s, long *cnt_e, long *cnt_w) {
  *cnt_n = count_n;
  *cnt_e = count_e;
  *cnt_s = count_s;
  *cnt_w = count_w;

  // エンコーダ回転方向の補正
  //*cnt_n *= -1;
  //*cnt_e *= -1;
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
  static int b_prev = LOW;

  a_curr = digitalRead(ENC_N1);
  b_curr = digitalRead(ENC_N2);

  // 正転 : [L, H]→(L, L)→[H, L]→(H, H)→[L, H]
  if (a_curr) {
    if (b_prev && !b_curr) { // up
      count_n++;
    } else { // down
      count_n--;
    }
  } else {
    if (b_prev && !b_curr) { // down
      count_n--;
    } else { // up
      count_n++;
    }
  }

  b_prev = b_curr;
}

static void enc_change_e() {
  int a_curr, b_curr;
  static int  b_prev = LOW;

  a_curr = digitalRead(ENC_E1);
  b_curr = digitalRead(ENC_E2);

  // 正転 : [L, H]→(L, L)→[H, L]→(H, H)→[L, H]
  if (a_curr) {
    if (b_prev && !b_curr) { // up
      count_e++;
    } else { // down
      count_e--;
    }
  } else {
    if (b_prev && !b_curr) { // down
      count_e--;
    } else { // up
      count_e++;
    }
  }

  b_prev = b_curr;
}


static void enc_change_s() {
  int a_curr, b_curr;
  static int b_prev = LOW;

  a_curr = digitalRead(ENC_S1);
  b_curr = digitalRead(ENC_S2);

  // 正転 : [L, H]→(L, L)→[H, L]→(H, H)→[L, H]
  if (a_curr) {
    if (b_prev && !b_curr) { // up
      count_s++;
    } else { // down
      count_s--;
    }
  } else {
    if (b_prev && !b_curr) { // down
      count_s--;
    } else { // up
      count_s++;
    }
  }

  b_prev = b_curr;
}

static void enc_change_w() {
  int a_curr, b_curr;
  static int b_prev = LOW;

  a_curr = digitalRead(ENC_W1);
  b_curr = digitalRead(ENC_W2);

  // 正転 : [L, H]→(L, L)→[H, L]→(H, H)→[L, H]
  if (a_curr) {
    if (b_prev && !b_curr) { // up
      count_w++;
    } else { // down
      count_w--;
    }
  } else {
    if (b_prev && !b_curr) { // down
      count_w--;
    } else { // up
      count_w++;
    }
  }

  b_prev = b_curr;
}
