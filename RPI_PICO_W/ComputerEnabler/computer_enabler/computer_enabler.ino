#define RELAY_PIN 15
#define BUTTON_PIN 14  // Przycisk z obudowy
#define LED_PIN LED_BUILTIN

unsigned long lastBlink = 0;
bool ledState = false;

bool lastButtonState = HIGH;

/*
 * Script for remotly enabling something like computer by connecting GND
 * Required RPI PICO W + 1 Relay module
 * 
 * PINOUT FOR MODULE:
 * VCC → VBUS (pin 40 Pico) - 5V
 * GND → GND (pin 38 Pico)
 * IN → GP15 (pin 20 Pico)
 * 
 * PINOUT FOR CASE BUTTON:
 * GP14 (pin 19 Pico) → Case button
 * GND (pin 18 lub inne) → Case button second cable
 */

void triggerRelay()
{
  Serial.println("triggerRelay");

  digitalWrite(RELAY_PIN, HIGH);
  delay(350);
  digitalWrite(RELAY_PIN, LOW);
}

void setup()
{
  Serial.begin(115200);
  while(!Serial && millis() < 5000); 

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Pullup - LOW gdy naciśnięty
  pinMode(LED_PIN, OUTPUT);
  
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  lastButtonState = digitalRead(BUTTON_PIN);
  
  Serial.println("Ready");
}

void loop()
{
  // Serial command
  if (Serial.available())
  {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "ON")
    {
      Serial.println("OK");

      triggerRelay();
    }
  }
  
  // Button to enable manually
  bool buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != lastButtonState)
  {
    lastButtonState = buttonState;

    if (buttonState == LOW)
    {
      Serial.println("Button pressed");

      triggerRelay();
    }
  }
  
  // Flash internal LED every 1s
  if (millis() - lastBlink >= 500)
  {
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }

  delay(150);
}