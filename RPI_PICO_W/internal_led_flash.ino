const int ledPin = 25; // Wbudowana dioda LED na Raspberry Pi Pico

void setup()
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, HIGH); // Włącz diodę
  delay(500);                 // Poczekaj 0.5 sekundy
  digitalWrite(ledPin, LOW);  // Wyłącz diodę
  delay(500);                 // Poczekaj 0.5 sekundy
}