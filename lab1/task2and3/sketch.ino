void setup() {
  /*
  Szkic: Arduino uno
  Author: Jaroslaw Roszyk; 2024-02-24
  */
  // pinMode(2, OUTPUT);
  // pinMode(3, OUTPUT);
  // pinMode(4, OUTPUT);
  // pinMode(5, OUTPUT);
  // pinMode(6, OUTPUT);
  for(int i = 2; i <= 6; ++i)
  {
    pinMode(i, OUTPUT);
  }
}

void task2()
{
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  delay(500);
  digitalWrite(6, LOW);

  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW);
}

void task3()
{
  int pins[] = {2, 3, 4, 5, 6};
  int pinCount = sizeof(pins) / sizeof(pins[0]);
  
  for (int i = 0; i < pinCount; i++)
  {
    digitalWrite(pins[i], HIGH);
    delay(500);
    digitalWrite(pins[i], LOW);
  }

  for(int i = 5; i >= 2; --i) {
    digitalWrite(i, HIGH);
    delay(500);
    digitalWrite(i, LOW);
  }
}


void loop() {
  task2();
}
