#include <WiFi.h>
#include <WebServer.h>
#include "config.h"

// Connections
// Buzer -> ESP32
// Buzzer+ to VN
// Buzzer- to D5
// Buzzer- to D4 (optional)

#define BUZZER_PIN_1 5   // D5
#define BUZZER_PIN_2 4   // 4

void setup()
{
  Serial.begin(115200);
  
  delay(2000);

  pinMode(BUZZER_PIN_1, OUTPUT);
  pinMode(BUZZER_PIN_2, OUTPUT);
  
  Serial.println("Simple Buzzer Test Started");
  Serial.println("Wiring: Buzzer + → GPIO2, Buzzer out- → GND");
}

void loop()
{
  Serial.println("Buzzer ON");
  digitalWrite(BUZZER_PIN_1, HIGH);  // Give power to buzzer
  delay(1000);

  Serial.println("Buzzer ON2");
  digitalWrite(BUZZER_PIN_2, HIGH);  // Give power to buzzer
  delay(1000);
  
  Serial.println("Buzzer OFF1");
  digitalWrite(BUZZER_PIN_1, LOW);   // Remove power from buzzer
  delay(1000);
  
  Serial.println("Buzzer OFF2");
  digitalWrite(BUZZER_PIN_2, LOW);   // Remove power from buzzer
  delay(1000);
}