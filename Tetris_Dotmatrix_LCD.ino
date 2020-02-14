//column 저항 연결
//2~10 column, 11~18 row
//row에 HIGH, columndp LOW일 때 ON


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

void loop() {
  int i;
  
  for (i = 0; i < 18; i++) {
    digitalWrite(i + 2, LOW);

    if (i >= 8) {
      digitalWrite(i + 2, HIGH);
    }
  }
}
