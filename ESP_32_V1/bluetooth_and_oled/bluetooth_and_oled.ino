// OLED Connections
// GND→GND, VCC→3V3, D0→D18, D1→D23, RES→D4, DC→D2, CS→D15

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BluetoothSerial.h"

BluetoothSerial serialBT;

Adafruit_SSD1306 display(128, 64, 23, 18, 2, 4, 15);

void setup()
{
  Serial.begin(115200);
  serialBT.begin("ESP32test");

  delay(500);

  Serial.println("Urządzenie gotowe do parowania!");

  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.print("Ready to connect!");
  display.display();
}

void loop()
{
  // Odbieranie danych z Bluetooth i wysyłanie do Serial
  if (serialBT.available())
  {
    String message = serialBT.readString();
    Serial.println("Odebrano: " + message);
  }
  
  // Odbieranie danych z Serial i wysyłanie przez Bluetooth
  if (Serial.available())
  {
    String message = Serial.readString();
    serialBT.println("ESP32 mówi: " + message);
  }
}