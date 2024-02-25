/*
Szkic Arduino Diody LED
Autor: Jaroslaw Roszyk ; 2024-02-25
*/

#define BUTTON1 13
#define BUTTON2 9

#define EAST_GREEN 0
#define EAST_YELLOW 1
#define EAST_RED 2

#define WEST_GREEN 10
#define WEST_YELLOW 11
#define WEST_RED 12

void setup() {
  pinMode(EAST_GREEN, OUTPUT);
  pinMode(EAST_YELLOW, OUTPUT);
  pinMode(EAST_RED, OUTPUT);
  pinMode(WEST_GREEN, OUTPUT);
  pinMode(WEST_YELLOW, OUTPUT);
  pinMode(WEST_RED, OUTPUT);
  
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  
  // Początkowy stan sygnalizacji
  digitalWrite(EAST_GREEN, HIGH);
  digitalWrite(WEST_RED, HIGH);
}

void loop() {
  if (digitalRead(BUTTON1) == HIGH) { 
    // Samochód na wschód chce przejechać
    // Zmiana świateł na wschodniej stronie mostu
    digitalWrite(EAST_GREEN, LOW);
    digitalWrite(EAST_YELLOW, HIGH);
    delay(1000); // Opóźnienie dla sygnału żółtego
    digitalWrite(EAST_YELLOW, LOW);
    digitalWrite(EAST_RED, HIGH);
    
    // Oczekiwanie na opuszczenie mostu przez pojazdy
    delay(5000); // Przyjmujemy, że opuszczanie mostu trwa 5 sekund
    
    // Włączenie zielonego światła na zachodniej stronie mostu
    digitalWrite(WEST_RED, LOW);
    digitalWrite(WEST_GREEN, HIGH);
    delay(1000); // Opóźnienie dla sygnału zielonego
    
    // Powrót do początkowego stanu
    digitalWrite(WEST_GREEN, LOW);
    digitalWrite(WEST_RED, HIGH);
    digitalWrite(EAST_RED, LOW);
    digitalWrite(EAST_GREEN, HIGH);
  }

  if (digitalRead(BUTTON2) == HIGH) { // Samochód na zachód chce przejechać
    // Zmiana świateł na zachodniej stronie mostu
    digitalWrite(WEST_GREEN, LOW);
    digitalWrite(WEST_YELLOW, HIGH);
    delay(1000); // Opóźnienie dla sygnału żółtego
    digitalWrite(WEST_YELLOW, LOW);
    digitalWrite(WEST_RED, HIGH);
    
    // Oczekiwanie na opuszczenie mostu przez pojazdy
    delay(5000); // Przyjmujemy, że opuszczanie mostu trwa 5 sekund
    
    // Włączenie zielonego światła na wschodniej stronie mostu
    digitalWrite(EAST_RED, LOW);
    digitalWrite(EAST_GREEN, HIGH);
    delay(1000); // Opóźnienie dla sygnału zielonego
    
    // Powrót do początkowego stanu
    digitalWrite(EAST_GREEN, LOW);
    digitalWrite(EAST_RED, HIGH);
    digitalWrite(WEST_RED, LOW);
    digitalWrite(WEST_GREEN, HIGH);
  }
}
