// OLED Connections
// GND→GND, VCC→3V3, D0→D18, D1→D23, RES→D4, DC→D2, CS→D15

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, 23, 18, 2, 4, 15);

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.print("DZIAŁA!");
  display.display();
}

void loop()
{
  delay(1000);
}