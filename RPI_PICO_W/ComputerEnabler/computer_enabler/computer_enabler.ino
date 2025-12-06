#define RELAY_PIN 15
#define LED_PIN LED_BUILTIN

unsigned long lastBlink = 0;
bool ledState = false;

/*
 * Script for remotly enabling something like computer by connecting GND
 * Required RPI PICO W + 1 Relay module
 * 
 * PINOUT FOR MODULE
 * VCC → VBUS (pin 40 Pico) - to 5V
 * GND → GND (pin 38 Pico)
 * IN → GP15 (pin 20 Pico)
 */

void setup()
{
  Serial.begin(115200);

  // Limited wait for serial
  while(!Serial && millis() < 5000); 

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  Serial.println("Ready");
}

void loop()
{
  // Serial
  if (Serial.available())
  {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "ON")
    {
      digitalWrite(RELAY_PIN, HIGH);
      delay(200);
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("OK");
    }
  }
  
  // Flash internal LED every 1s
  if (millis() - lastBlink >= 1000) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    lastBlink = millis();
  }
}