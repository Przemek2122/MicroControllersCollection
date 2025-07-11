#include <WiFi.h>
#include <WebServer.h>
#include "config.h"

#define BUZZER_PIN 5   // D2 on the board = GPIO2 in code

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(100);
  }

  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.println("Simple Buzzer Test Started");
  Serial.println("Wiring: Buzzer + → GPIO2, Buzzer out- → GND");
}

void loop() {
  Serial.println("Buzzer ON");
  digitalWrite(BUZZER_PIN, HIGH);  // Give power to buzzer
  delay(1000);
  
  Serial.println("Buzzer OFF");
  digitalWrite(BUZZER_PIN, LOW);   // Remove power from buzzer
  delay(1000);
}