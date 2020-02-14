//column 저항 연결
//2~9 column, 10~17 row
//column LOW, row에 HIGH 일 때 ON


void setup() {
  int i;

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

int num_all[10][8] = {
  {0x00, 0x38, 0x44, 0x4c, 0x54, 0x64, 0x44, 0x38},
  {0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c},
  {0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7c},
  {0x00, 0x38, 0x44, 0x04, 0x18, 0x04, 0x44, 0x38},
  {0x00, 0x08, 0x18, 0x28, 0x48, 0x7c, 0x08, 0x08},
  {0x00, 0x7c, 0x40, 0x78, 0x04, 0x04, 0x44, 0x38},
  {0x00, 0x38, 0x40, 0x40, 0x78, 0x44, 0x44, 0x38},
  {0x00, 0x7c, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20},
  {0x00, 0x38, 0x44, 0x44, 0x38, 0x44, 0x44, 0x38},
  {0x00, 0x38, 0x44, 0x44, 0x3c, 0x04, 0x44, 0x38}
};
int num[8] = {0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c};
unsigned long c_micros = 0;
unsigned long p_micros = 0;

void loop() {
  int i, j = 0;
  c_micros = micros();

  if (c_micros - p_micros > 2500) {
    p_micros = c_micros;

    //    //=================================
    //    for (int i = 10; i < 18; i++) {
    //      digitalWrite(i, LOW);
    //    }
    //    //---------------------------------
    //    // 2. colum value
    //    for (int i = 0; i < 8; i++) {
    //      if (num_all[1][j] & (0x80 >> i)) {
    //        digitalWrite(2 + i , LOW);
    //      }
    //      else {
    //        digitalWrite(2 + i , HIGH);
    //      }
    //    }
    //    //---------------------------------
    //    //3. row pin on
    //    digitalWrite(j + 10, HIGH);
    //
    //    //4. row pin 증가
    //    j++;
    //    if (j >= 8) j = 0;
    //  }






  }

  for (i = 0; i < 8; i++) {
    digitalWrite(2 + i, HIGH);
  }



  for (j = 0; j < 8; j++) {
    for (i = 0; i < 8; i++) {
      if (num[j] & (0x80 >> i)) {
        digitalWrite(2 + i , LOW);
        Serial.print('1');
      }
      else {
        digitalWrite(2 + i , HIGH);
        Serial.print('0');
      }

    }
    Serial.println();
    digitalWrite(j + 10, HIGH);
  }
  delay(1000);
}
