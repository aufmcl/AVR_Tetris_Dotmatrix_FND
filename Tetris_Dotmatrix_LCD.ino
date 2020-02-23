//column 저항 연결
//2~9 column, 10~17 row
//column LOW, row에 HIGH 일 때 ON

int edge[8] = {0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF};
int block[8] = {0x10, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned long c_micros = 0;
unsigned long p_micros = 0;
unsigned long c_millis = 0;
unsigned long p_millis = 0;
int falling_block[8] = {0x01, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
int fallen_block[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
int flag_crte = 1;


void setup() {
  int i;
  //  TCCR1A = 0x00;
  //  TCCR1B = 0x04;
  //  TIMSK1 = 0x01;
  //  TCNT1 = 100;

  for (i = 0; i < 16; i++) {
    pinMode(i + 2, OUTPUT);
  }

  for (i = 0; i < 18; i++) {
    digitalWrite(i + 2, HIGH);

    if (i >= 8) {
      digitalWrite(i + 2, LOW);
    }
  }

  create_block();

  Serial.begin(9600);
}

//ISR(TIMER1_OVF_vect)
//{
//  TCNT1 = 100;
//}

int overlap_check() {

  for (int i = 0; i < 8; i++) {
    if (fallen_block[i] & edge[i]) {
      return 1;
    }
  }
  return 0;
}

void insert_block() {
  for (int i = 0; i < 8; i++) {
    fallen_block[i] |= falling_block[i];
    edge[i] |= fallen_block[i];
  }
}

void create_block() {
  for (int i = 0; i < 8; i++) {
    falling_block[i] = block[i];
  }
}

void loop() {
  c_micros = micros();
  c_millis = millis();

  if (c_millis - p_millis >= 1000) {
    p_millis = c_millis;

    if (overlap_check()) {
      create_block();
      insert_block();
    }
    else {
      //---------------------------DOWN SHIFT
      for (int i = 8; i >= 0; i--) {
        falling_block[i] = falling_block[i - 1];
      }
      falling_block[0] = 0x00;
      //---------------------------

      for (int i = 0; i < 8; i++) {
        fallen_block[i] = falling_block[i];
      }
    }
  }

  if (c_micros - p_micros > 2500) {
    p_micros = c_micros;

    for (int j = 0; j < 8; j++) {
      digitalWrite(j + 10, HIGH);

      //---------------------------DRAW BLOCK
      for (int i = 0; i < 8; i++) {
        if (fallen_block[j] & (0x80 >> i)) {
          digitalWrite(i + 2 , LOW);
        }
        else {
          digitalWrite(i + 2 , HIGH);
        }
      }
      //---------------------------

      //---------------------------OFF ALL
      for (int i = 0; i < 18; i++) {
        digitalWrite(i + 2, HIGH);

        if (i >= 8) {
          digitalWrite(i + 2, LOW);
        }
      }
      //---------------------------
    }
  }
}
