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
unsigned long c_micros = 0;
unsigned long p_micros = 0;
unsigned long c_millis = 0;
unsigned long p_millis = 0;

int count = 0;
void loop() {
  int i, j = 0;
  c_micros = micros();
  c_millis = millis();

  if (c_micros - p_micros > 2500) {
    p_micros = c_micros;

    for (j = 0; j < 8; j++) {
      digitalWrite(j + 10, HIGH);
      for (i = 0; i < 8; i++) {
        if (num_all[count][j] & (0x80 >> i)) {
          digitalWrite(i + 2 , LOW);
        }
        else {
          digitalWrite(i + 2 , HIGH);
        }
      }

      //---------------------------OFF ALL
      for (i = 0; i < 18; i++) {
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

    count++;
    if (count >= 10)  count = 0;
  }

}
