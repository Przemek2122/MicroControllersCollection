const int externalLedPin = 5;   // GP5
const int buttonPin = 2;        // GP2

void setup()
{
  // Enable build in LED
  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);

  pinMode(externalLedPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(buttonPin) == LOW)
  {
    digitalWrite(externalLedPin, HIGH);
  }
  else
  {
    digitalWrite(externalLedPin, LOW);
  }

  delay(10);
}