#include <LiquidCrystal_I2C.h>
//wyswietlacz
#define I2C_ADDR 0x27
#define LCD_COLUMNS 16
#define LCD_LINES 2
#define HOT 6
#define NORMAL 4
#define COLD 2
//pomiar temperatury
float celsius = 0;
float hotTemp = 26;
float coldTemp = 15;
const float BETA = 3950; // powinien pasować do współczynnika Beta termistora

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);


void setup() {
//diody
pinMode(HOT, OUTPUT);
pinMode(NORMAL, OUTPUT);
pinMode(COLD, OUTPUT);
Serial.begin(9600);
//Lcd
lcd.init();
lcd.backlight();
// Początkowy tekst na wyswieltaczu
}



void loop() {
// odczytuje stan czujnika temperatury i konwertuje wynik na stopnie Celsjusza
int analogValue = analogRead(A0);
// konwertuje miliwolty na stopnie Celsjusza
float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) -
273.15;
Serial.print("Temperatura: ");
Serial.print(celsius);
Serial.println(" °C" );
delay(1000);
// obsługa przedziałów temperatur:
if ( celsius < coldTemp )
{
digitalWrite(COLD, HIGH);
delay(1000);
digitalWrite(COLD, LOW);
lcd.setCursor(0, 0);
lcd.print(celsius);
lcd.setCursor(0, 1);
lcd.print("Zimno-brr!");
}
else if ( celsius > coldTemp && celsius <= hotTemp )
{
digitalWrite(NORMAL, HIGH);
delay(1000);
digitalWrite(NORMAL, LOW);
lcd.setCursor(0, 0);
lcd.print(celsius);
lcd.setCursor(0, 1);
lcd.print("W sam raz - mozna zyc!");
}
else
{
// celsius > hotTemp
digitalWrite(HOT, HIGH);
delay(1000);
digitalWrite(HOT, LOW);
lcd.setCursor(0, 0);
lcd.print(celsius);
lcd.setCursor(0, 1);
lcd.print("Cieplo az za!");
}
}