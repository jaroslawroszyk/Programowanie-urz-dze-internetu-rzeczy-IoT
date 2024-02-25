#define BUTTON 3
/*
Szkic Arduino Diody LED
Autor: Jaroslaw Roszyk ; 2024-02-25
*/
void setup(){
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop(){
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);

  if ( digitalRead(BUTTON) == HIGH ){
    for (int i=0; i<=2; i++){
      digitalWrite(i, HIGH);
      delay(500);
      digitalWrite(i+i, LOW);
      delay(500);
      digitalWrite(i+i, LOW);
      delay(500);
  }

  for (int i=10; i<=12; i++){
    digitalWrite(i, HIGH);
    delay(500);
    digitalWrite(i+i, LOW);
    delay(500);
    digitalWrite(i+i, LOW);
    delay(500);
}
}
}