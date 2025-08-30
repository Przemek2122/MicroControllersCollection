// OLED Connections
// GND→GND, VCC→3V3, D0→D18, D1→D23, RES→D4, DC→D2, CS→D15

// BME280 Connections
// VCC→3.3V, GND→GND, SDA→D21, SCL→D22

#include <string>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>

Adafruit_SSD1306 display(128, 64, 23, 18, 2, 4, 15);
Adafruit_BME280 bme;

bool bBMEFound = false;

void setup()
{
  Serial.begin(115200);

  Wire.begin(21, 22);

// Commented out as I do not care if it will use log when finished programming
/*
  // Wait for serial to connect but only 5 secs
  for (int i = 0; i < 50 && !Serial.available(); i++)
  {
    delay(100);
  }
*/

  Serial.println("Starting ESP32...");

  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("OLED Ready...");
  display.display();

  bBMEFound = bme.begin(0x76);
}

void loop()
{
  if (bBMEFound)
  {
    float temp = bme.readTemperature();
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure() / 100.0F;

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.print("Sensor readings");

    display.setCursor(0, 15);
    display.print("Temp:     ");
    display.print(temp);
    display.print(" C");

    display.setCursor(0, 25);
    display.print("Humidity: ");
    display.print(humidity);
    display.print(" %");

    display.setCursor(0, 35);
    display.print("Pressure: ");
    display.print(pressure);
    display.print(" hPa");

    
    display.setCursor(0, 50);
    display.print("Have a good day!");

    display.display();

    //delay(100);
  }
}