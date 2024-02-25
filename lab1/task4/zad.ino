#define LED 12
#define BUTTON 7

void setup() {
  /*
  Szkic: Arduino uno
  Author: Jaroslaw Roszyk; 2024-02-24
  */
 pinMode(2, INPUT_PULLUP);
 pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
}

void loop()
{
  if(digitalRead(2) == LOW)
  {
    digitalWrite(3, HIGH);
    delay(2000);
    digitalWrite(3, LOW);
  }
}
