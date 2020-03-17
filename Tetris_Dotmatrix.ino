//column 저항 연결
//2~9 column, 10~17 row
//column LOW, row에 HIGH 일 때 ON

const int block[7][4][8] = {
  { {0x10, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},//└
    {0x18, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x1C, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x08, 0x08, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}
  },
  { {0x04, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},//┘
    {0x10, 0x10, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x1C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00}
  },
  { {0x18, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},//┐
    {0x08, 0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00},//└
    {0x18, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x08, 0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00}
  },
  { {0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},//┌
    {0x10, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00},//┘
    {0x1C, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x10, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00}
  },
  { {0x08, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},//┴
    {0x10, 0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x1C, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00}
  },
  { {0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},//□
    {0x18, 0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}
  },
  { {0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00},//│
    {0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00},
    {0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
  },
};
unsigned long c_micros = 0;
unsigned long p_micros = 0;
unsigned long c_millis = 0;
unsigned long p_millis = 0;
unsigned short rotate = 0;
unsigned short y = 0;
unsigned short shape = 0;
unsigned short score = 0;
bool flag_right = false, flag_left = false;
bool flag_up = false, flag_down = false;
bool flag_start = false;
int falling_block[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
int fallen_block[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
int show_block[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
int edge[8] = {0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF};
char key;


void setup() {
  //  TCCR1A = 0x00;
  //  TCCR1B = 0x04;
  //  TIMSK1 = 0x01;
  //  TCNT1 = 100;
  ADMUX = 0x40;
  ADCSRA = 0x87;

  //Serial.begin(9600);
  UBRR0 = 103;    //9600 baudrate
  UCSR0A = 0x00;  //U2X = 0
  UCSR0B = 0x98;  //TX, RX enable
  UCSR0C = 0x06;  //Async, no Parity, 1 stop, 8bit

  for (int i = 0; i < 16; i++) {
    pinMode(i + 2, OUTPUT);
  }

  //===========================OFF ALL
  for (int i = 0; i < 16; i++) {
    digitalWrite(i + 2, HIGH);

    if (i >= 8) {
      digitalWrite(i + 2, LOW);
    }
  }
  //===========================  
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
  else if (flag == 3) {
    for (int i = 0; i < 8; i++) {
      falling_block[i] = block[shape][rotate + 1][i];
    }
  }
  //===========================---------------------------
  for (int i = 0; i < 8; i++) {
    if (edge[i] & falling_block[i]) {
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
      else if (flag == 3) {
        for (int i = 0; i < 8; i++) {
          falling_block[i] = block[shape][rotate][i];
        }
      }

      digitalWrite(18, HIGH);
      return 1;
    }
  }
  //===========================---------------------------
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
  else if (flag == 3) {
    for (int i = 0; i < 8; i++) {
      falling_block[i] = block[shape][rotate][i];
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
  y = 0;
  rotate = 0;
  shape = random() % 7;

  for (int i = 0; i < 8; i++) {
    falling_block[i] = block[shape][0][i];
    show_block[i] = block[shape][0][i];
    show_block[i] |= fallen_block[i];
  }
}



//ISR(TIMER1_OVF_vect)
//{
//  TCNT1 = 100;
//}



void loop() {
  create_block();
  
  while (flag_start == true) {
    c_micros = micros();
    c_millis = millis();

    //===========================Analog Read
    ADMUX = 0x44;
    ADCSRA |= 0x40;
    while (!(ADCSRA & 0x10));
    ADCSRA |= 0x10;
    int x_value = ADC;

    ADMUX = 0x45;
    ADCSRA |= 0x40;
    while (!(ADCSRA & 0x10));
    ADCSRA |= 0x10;
    int y_value = ADC;
    //===========================

    //===========================KEY EVENT (ADC)
    //---------------------------X
    if (x_value >= 700 && x_value <= 1023) {
      if (flag_right) {
        flag_right = false;
        flag_left = true;

        if (!overlap_check(2)) {
          for (int i = 0; i < 8; i++) {
            falling_block[i] >>= 1;
            show_block[i] = falling_block[i];
            show_block[i] |= fallen_block[i];
          }
        }
      }
    }
    else if (x_value <= 400 && x_value >= 0) {
      if (flag_left) {
        flag_left = false;
        flag_right = true;

        if (!overlap_check(1)) {
          for (int i = 0; i < 8; i++) {
            falling_block[i] <<= 1;
            show_block[i] = falling_block[i];
            show_block[i] |= fallen_block[i];
          }
        }
      }
    }
    else {
      flag_left = true;
      flag_right = true;
    }
    //---------------------------Y
    if (y_value <= 400 && y_value >= 0) {
      if (flag_up) {
        flag_up = false;
        flag_down = true;

        if (!overlap_check(3)) {
          rotate++;

          if (rotate == 4) {
            rotate = 0;
          }

          for (int i = 0; i < 8; i++) {
            falling_block[i] = block[shape][rotate][i];
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
    }
    else if (y_value >= 700 && y_value <= 1023) {
      if (flag_down) {
        flag_down = false;
        flag_up = true;

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
    }
    else {
      flag_down = true;
      flag_up = true;
    }
    //===========================

    //===========================1000 mills Delay
    if (c_millis - p_millis > 1000) {
      p_millis = c_millis;

      //Serial.print("");
      if (!overlap_check(0)) {
        //===========================DOWN SHIFT
        y++;
        memmove(falling_block + 1, falling_block, sizeof(int) * 8);
        falling_block[0] = 0x00;
        //===========================
      }
      else {
        //===========================LINE CHECK

        //---------------------------GAME OVER
        for (int j = 0; j < 8; j++) {
          if (show_block[0] & 0x7E) {
            flag_start = false;

            while (!(UCSR0A & 0x20));
            UDR0 = 0x71;
          }

          if (show_block[j] == 0x7E) {

            //---------------------------Serial.write(1)
            while (!(UCSR0A & 0x20));
            UDR0 = 0x31;

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
        //===========================

        insert_block();
        create_block();
      }

      for (int i = 0; i < 8; i++) {
        show_block[i] = falling_block[i];
        show_block[i] |= fallen_block[i];
      }
    }
    //===========================

    //===========================2500 micros Delay
    if (c_micros - p_micros > 2500) {
      p_micros = c_micros;

      for (int j = 0; j < 8; j++) {
        digitalWrite(j + 10, HIGH);

        //===========================DRAW BLOCK
        for (int i = 0; i < 8; i++) {
          if (show_block[j] & (0x80 >> i)) {
            digitalWrite(i + 2 , LOW);
          }
          else {
            digitalWrite(i + 2 , HIGH);
          }
        }
        //===========================

        //===========================OFF ALL
        for (int i = 0; i < 16; i++) {
          digitalWrite(i + 2, HIGH);

          if (i >= 8) {
            digitalWrite(i + 2, LOW);
          }
        }
        //===========================
      }
    }
  }

  for (int i = 0; i < 8; i++) {
    falling_block[i] = 0x00;
    fallen_block[i] = 0x00;
    show_block[i] = 0x00;
    edge[i] = 0x81;
  }
  edge[7] = 0xFF;
}

ISR(USART_RX_vect) {
  if (UCSR0A & 0x80) { // Serial.availabe()
    key = UDR0;

    while (!(UCSR0A & 0x20));

    if (key == 'A') {
      if (!overlap_check(1)) {
        for (int i = 0; i < 8; i++) {
          falling_block[i] <<= 1;
          show_block[i] = falling_block[i];
          show_block[i] |= fallen_block[i];
        }
      }
    }
    else if (key == 'D') {
      if (!overlap_check(2)) {
        for (int i = 0; i < 8; i++) {
          falling_block[i] >>= 1;
          show_block[i] = falling_block[i];
          show_block[i] |= fallen_block[i];
        }
      }
    }
    else if (key == 'S') {
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
    else if (key == 'R') {
      if (!overlap_check(3)) {
        rotate++;

        if (rotate == 4) {
          rotate = 0;
        }

        for (int i = 0; i < 8; i++) {
          falling_block[i] = block[shape][rotate][i];
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
    else if (key == '1') {
      flag_start = true;
    }
    else if (key == '0') {
      flag_start = false;
    }
  }
}
