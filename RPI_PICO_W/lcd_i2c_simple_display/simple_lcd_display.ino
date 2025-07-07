// This code requires "LiquidCrystal I2C" library from Brabander
#include <LiquidCrystal_I2C.h>

const int externalLedPin = 5;   // GP5
const int buttonPin = 2;        // GP2
int number = 0;

// Adres I2C (0x27 lub 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  delay(5000);  // 5 sekund opóźnienia!

  // Enable build in LED
  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);
  
  Serial.println("Inicjalizacja LCD...");
  
  lcd.init();                    
  lcd.backlight();              
  lcd.clear();                  // Wyczyść ekran
  delay(500);
  
  lcd.home();                   // Powrót do 0,0
  lcd.print("Hej"); // Cała pierwsza linia
  lcd.setCursor(0, 1);          
  lcd.print("Testuje"); // Cała druga linia
  
  Serial.println("LCD gotowy!");
}

void loop()
{
  lcd.clear();                  // Wyczyść ekran
  lcd.print(number); // Cała druga linia
  number++;
  delay(1000);
}