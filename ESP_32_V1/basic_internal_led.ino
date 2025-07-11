// ESP32 Internal LED Blink
void setup()
{
  // Initialize serial communication
  Serial.begin(115200);

  while (!Serial)
  {
    delay(100);
  }

  Serial.println("ESP32 LED Blink Starting...");
  
  // Set LED pin as output
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Turn off LED initially
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  // Turn LED on
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("LED ON");
  delay(1000);
  
  // Turn LED off
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("LED OFF");
  delay(1000);
}