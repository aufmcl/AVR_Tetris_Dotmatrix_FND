//column 저항 연결
//2~9 column, 10~17 row
//column LOW, row에 HIGH 일 때 ON

const int block[4][8] = {
  {0x10, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x18, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x1C, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x08, 0x08, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}
};
int falling_block[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
int fallen_block[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
int show_block[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
int edge[8] = {0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF};
int rotate = 0;
int y = 0;
unsigned long c_micros = 0;
unsigned long p_micros = 0;
unsigned long c_millis = 0;
unsigned long p_millis = 0;


void setup() {
  //  TCCR1A = 0x00;
  //  TCCR1B = 0x04;
  //  TIMSK1 = 0x01;
  //  TCNT1 = 100;

  for (int i = 0; i < 16; i++) {
    pinMode(i + 2, OUTPUT);
  }

  //---------------------------OFF ALL
  for (int i = 0; i < 16; i++) {
    digitalWrite(i + 2, HIGH);

    if (i >= 8) {
      digitalWrite(i + 2, LOW);
    }
  }
  //---------------------------
  create_block();
  Serial.begin(9600);
}


int overlap_check(int flag) {
  if (flag == 0) {
    memmove(falling_block + 1, falling_block, sizeof(int) * 8);
    falling_block[0] = 0x00;
  }
  else if (flag == 1) {
    for (int i = 0; i < 8; i++) {
      falling_block[i] <<= 1;
    }
  }
  else if (flag == 2) {
    for (int i = 0; i < 8; i++) {
      falling_block[i] >>= 1;
    }
  }
  //------------------------------------------------------
  for (int i = 0; i < 8; i++) {
    if (edge[i] & falling_block[i]) {
      if (flag == 0) {
        y = 0;
        memmove(falling_block - 1, falling_block, sizeof(int) * 8);
        falling_block[7] = 0x00;
      }
      else if (flag == 1) {
        for (int i = 0; i < 8; i++) {
          falling_block[i] >>= 1;
        }
      }
      else if (flag == 2) {
        for (int i = 0; i < 8; i++) {
          falling_block[i] <<= 1;
        }
      }

      digitalWrite(18, HIGH);
      return 1;
    }
  }
  //------------------------------------------------------
  if (flag == 0) {
    memmove(falling_block - 1, falling_block, sizeof(int) * 8);
    falling_block[7] = 0x00;
  }
  else if (flag == 1) {
    for (int i = 0; i < 8; i++) {
      falling_block[i] >>= 1;
    }
  }
  else if (flag == 2) {
    for (int i = 0; i < 8; i++) {
      falling_block[i] <<= 1;
    }
  }
  digitalWrite(18, LOW);

  return 0;
}

void insert_block() {
  for (int i = 0; i < 8; i++) {
    edge[i] |= falling_block[i];
    fallen_block[i] |= falling_block[i];
  }
}

void create_block() {
  for (int i = 0; i < 8; i++) {
    falling_block[i] = block[0][i];
    show_block[i] = block[0][i];
    show_block[i] |= fallen_block[i];
  }
}



//ISR(TIMER1_OVF_vect)
//{
//  TCNT1 = 100;
//}



void loop() {
  c_micros = micros();
  c_millis = millis();


  //---------------------------KEY EVENT
  if (Serial.available()) {
    char key = Serial.read();

    if (key == 'a' || key == 'A') {
      if (!overlap_check(1)) {
        for (int i = 0; i < 8; i++) {
          falling_block[i] <<= 1;
          show_block[i] = falling_block[i];
          show_block[i] |= fallen_block[i];
        }
      }
    }
    else if (key == 'd' || key == 'D') {
      if (!overlap_check(2)) {
        for (int i = 0; i < 8; i++) {
          falling_block[i] >>= 1;
          show_block[i] = falling_block[i];
          show_block[i] |= fallen_block[i];
        }
      }
    }
    else if (key == 's' || key == 'S') {
      if (!overlap_check(0)) {
        y++;
        memmove(falling_block + 1, falling_block, sizeof(int) * 8);
        falling_block[0] = 0x00;

        for (int i = 0; i < 8; i++) {
          show_block[i] = falling_block[i];
          show_block[i] |= fallen_block[i];
        }
      }
    }
    else if (key == 'r' || key == 'R') {
      rotate++;

      if (rotate == 4) {
        rotate = 0;
      }

      for (int i = 0; i < 8; i++) {
        falling_block[i] = block[rotate][i];
      }
      memmove(falling_block + y, falling_block, sizeof(int) * 8);
      for (int i = 0; i < y; i++) {
        falling_block[i] = 0x00;        
      }

      for (int i = 0; i < 8; i++) {
        show_block[i] = falling_block[i];
        show_block[i] |= fallen_block[i];
      }
    }
  }
  //---------------------------

  if (c_millis - p_millis > 1000) {
    p_millis = c_millis;

    Serial.print("");
    if (!overlap_check(0)) {
      //---------------------------DOWN SHIFT
      y++;
      memmove(falling_block + 1, falling_block, sizeof(int) * 8);
      falling_block[0] = 0x00;
      //---------------------------
    }
    else {

      //---------------------------LINE CHECK
      for (int j = 0; j < 8; j++) {
        if (show_block[j] == 0x7E) {
          for (int i = j; i >= 0; i--) {
            show_block[i] = show_block[i - 1];
            falling_block[i] = falling_block[i - 1];
            fallen_block[i] = fallen_block[i - 1];
            edge[i] = edge[i - 1];
          }
          show_block[0] = 0x00;
          falling_block[0] = 0x00;
          fallen_block[0] = 0x00;
          edge[0] = 0x81;
        }
      }
      //---------------------------

      insert_block();
      create_block();
    }

    for (int i = 0; i < 8; i++) {
      show_block[i] = falling_block[i];
      show_block[i] |= fallen_block[i];
    }
  }

  if (c_micros - p_micros > 2500) {
    p_micros = c_micros;

    for (int j = 0; j < 8; j++) {
      digitalWrite(j + 10, HIGH);

      //---------------------------DRAW BLOCK
      for (int i = 0; i < 8; i++) {
        if (show_block[j] & (0x80 >> i)) {
          digitalWrite(i + 2 , LOW);
        }
        else {
          digitalWrite(i + 2 , HIGH);
        }
      }
      //---------------------------

      //---------------------------OFF ALL
      for (int i = 0; i < 16; i++) {
        digitalWrite(i + 2, HIGH);

        if (i >= 8) {
          digitalWrite(i + 2, LOW);
        }
      }
      //---------------------------
    }
  }
}
