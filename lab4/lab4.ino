#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

const int trigPin = 3; // Pin trigger czujnika ultradźwiękowego
const int echoPin = 2; // Pin echo czujnika ultradźwiękowego

const int redPin = 11; // Pin czerwonej diody
const int greenPin = 12; // Pin zielonej diody
const int bluePin = 13; // Pin niebieskiej diody
const int buzzerPin = 4; // Pin buzzer

double cm;
double cale;

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Foo ");
  delay(3000);
  lcd.clear();

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  cm = 0.0344/2 * readUltrasonicDistance(trigPin, echoPin);
  cale = (cm / 2.54);

  // Wyswietl odleglosc na LCD
  lcd.setCursor(0,0);
  lcd.print("Cale");
  lcd.setCursor(4,0);
  lcd.setCursor(12,0);
  lcd.print("Cm");
  lcd.setCursor(1,1);
  lcd.print(cale, 1);
  lcd.setCursor(11,1);
  lcd.print(cm, 1);
  lcd.setCursor(14,1);

   
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);

  if (cm > 0 and cm <= 40) {
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);

    digitalWrite(buzzerPin, HIGH); // Uruchomienie dźwięku
    lcd.clear();
    lcd.print("Uwaga! Obiekt"); // Wyświetlenie komunikatu
    lcd.setCursor(0,1);
    lcd.print("blisko!");
    delay(1000); // Odczekanie przed zatrzymaniem dźwięku
    digitalWrite(buzzerPin, LOW); // Zatrzymanie dźwięku
  } else if (cm > 40 && cm <= 80) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(buzzerPin, LOW); // Wyłączenie dźwięku
  } else { // Powyżej 80 cm
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(buzzerPin, LOW); // Wyłączenie dźwięku
  }


 
  delay(2000);
  lcd.clear();
}
