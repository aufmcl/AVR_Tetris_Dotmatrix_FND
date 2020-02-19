//column 저항 연결
//2~9 column, 10~17 row
//column LOW, row에 HIGH 일 때 ON


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

  Serial.begin(9600);
}


int block[8] = {0x10, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
int background[8] = {0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF};
unsigned long c_micros = 0;
unsigned long p_micros = 0;
unsigned long c_millis = 0;
unsigned long p_millis = 0;

int count = 0;

//ISR(TIMER1_OVF_vect)
//{
//  TCNT1 = 100;
//}


int overlap_check() {
  for (int i = 8; i >= 0; i--) {
    block[i] = block[i - 1];
  }
  block[0] = 0x00;

  for (int j = 0; j < 8; j++) {
    if (block[j] & background[j]) {
      for (int i = 0; i < 8; i++) {
        block[i] = block[i + 1];
      }
      block[8] = 0x00;

      return 1;
    }
  }
  for (int i = 0; i < 8; i++) {
    block[i] = block[i + 1];
  }
  block[8] = 0x00;

  return 0;
}

void loop() {
  c_micros = micros();
  c_millis = millis();

  if (c_micros - p_micros > 2500) {
    p_micros = c_micros;

    for (int j = 0; j < 8; j++) {
      digitalWrite(j + 10, HIGH);
      for (int i = 0; i < 8; i++) {
        if (block[j] & (0x80 >> i)) {
          digitalWrite(i + 2 , LOW);
        }
        else {
          digitalWrite(i + 2 , HIGH);
        }
      }

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


  if (c_millis - p_millis >= 1000) {
    p_millis = c_millis;

    //---------------------------DOWN SHIFT
    if (!overlap_check()) {
      //memmove(block + 1, block, sizeof(int) * 8);
      for (int i = 8; i >= 0; i--) {
        block[i] = block[i - 1];
      }
      block[0] = 0x00;
    }
    //---------------------------
  }

}
