// This code requires "LiquidCrystal I2C" library from Brabander
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "pico/multicore.h"

enum class DisplayState : uint8_t
{
  None = 0,
  TEMPERATURE = 1,
  HUMIDITY = 2,
  PRESSURE = 3
};

DisplayState displayState = DisplayState::TEMPERATURE;
DisplayState previousDisplayState = DisplayState::None;

Adafruit_BME280 bme;

const int buttonPin = 3;        // GP3
const int button2Pin = 6;        // GP6
bool bAnyInputPressed = false;

// Adres I2C (0x27 lub 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void scanI2C() {
  Serial.println("Scanning I2C...");
  byte count = 0;
  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      Serial.println(i, HEX);
      count++;
    }
  }
  if (count == 0) Serial.println("No I2C devices found");
}

void initPins()
{
  Serial.println("Pins init ...");

  // Enable build in LED
  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  //Wire.setSDA(18);  // GP18 dla SDA
  //Wire.setSCL(19);  // GP19 dla SCL
  //Wire.begin();
  //delay(1500); 

  Serial.println("Pins init end");
}

void initLCD()
{
  Serial.println("LCD init ...");
  
  lcd.init();                    
  lcd.backlight();          
  lcd.clear();
  lcd.home();
  lcd.print("Hej"); 
  //lcd.setCursor(0, 1);          
  //lcd.print("Testuje");
  
  Serial.println("LCD init end");
}

void initSensor()
{
  bool status = bme.begin(0x76); // 0x76 or 0x77
  if (!status)
  {
    Serial.println("BME280 not found");
  }
  else
  {
    Serial.println("BME280 works");
  }
}

void setup()
{
  Serial.begin(115200);

  // wait for serial port to connect. Needed for native USB
  while (!Serial)
  {
    delay(200);
  }

  initLCD();
  initPins();
  scanI2C();
  initSensor();

  multicore_launch_core1(secondCoreTask);

  lcd.home();                  
  lcd.print("Sensor read"); 
}

void loop()
{
  delay(200);

  lcd.setCursor(0, 1);

  switch (displayState)
  {
    case DisplayState::TEMPERATURE:
    {
      lcd.print("Temperature ");
      lcd.print(bme.readTemperature());
      lcd.print("*C    ");
      
      break;
    }
    case DisplayState::HUMIDITY:
    {
      lcd.print("Humidity ");
      lcd.print(bme.readHumidity());
      lcd.print("%    ");
      
      break;
    }
    case DisplayState::PRESSURE:
    {
      lcd.print("Pressure ");
      lcd.print(bme.readPressure());
      lcd.print("hPa    ");
      
      break;
    }
  }

  // Read VSYS voltage (if powered via VSYS pin)
  float voltage = analogRead(29) * 3.3f / 1024.0f * 3.0f; // ADC_VREF pin

  if (voltage < 3.0)
  {
    Serial.println("LOW VOLTAGE WARNING!");
  }

  previousDisplayState = displayState;
}

void loopSecondCore()
{
  if (!bAnyInputPressed)
  {
    if (digitalRead(buttonPin) == LOW && static_cast<uint8_t>(displayState) > 1)
    {
      displayState = static_cast<DisplayState>(static_cast<uint8_t>(displayState) - static_cast<uint8_t>(1));

      bAnyInputPressed = true;
    }
    else if (digitalRead(button2Pin) == LOW && static_cast<uint8_t>(displayState) < 3)
    {
      displayState = static_cast<DisplayState>(static_cast<uint8_t>(displayState) + static_cast<uint8_t>(1));

      bAnyInputPressed = true;
    }
  }
  else if (digitalRead(buttonPin) == HIGH && digitalRead(button2Pin) == HIGH)
  {
      bAnyInputPressed = false;
  }
}

void secondCoreTask()
{
  while (true)
  {
    loopSecondCore();

    delay(50);
  }
}