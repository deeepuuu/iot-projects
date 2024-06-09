/*************************************************************************
    PROJECT NAME: Temperature and humidity monitoring
   AUTHOR: Bharat Pi
   CREATED DATE: 08/11/2023
   COPYRIGHT: BharatPi @MIT license for usage on Bharat Pi boards
   VERSION: 0.1.0

   DESCRIPTION: Bharat Pi Lora_Rx

   REVISION HISTORY TABLE:
   ------------------------------------------
   Date      | Firmware Version | Comments
   ------------------------------------------
  08/11/2023 -    0.1.0       -     Initial release of sample script.
 *************************************************************************/#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// Define the pin and type of DHT sensor
#define DHTPIN 33
#define DHTTYPE DHT11

// Initialize the LCD and DHT objects
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change to 0x3F if 0x27 doesn't work
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize the Serial Monitor
  Serial.begin(115200);
  
  // Initialize the DHT sensor
  dht.begin();
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Display initial message
  lcd.setCursor(0, 0);
  lcd.print("Welcome to ");
  lcd.setCursor(0, 1);
  lcd.print("Bharat Pi");
  delay(2000);
  lcd.clear();
  
  // Check if LCD is initialized correctly
  Serial.println("LCD initialized and message displayed.");
}

void loop() {
  // Read sensor values
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Clear the LCD before displaying new values
  lcd.clear();
  
  // Check if any reads failed and display error message
  if (isnan(humidity) || isnan(temperature)) {
    displayError();
    Serial.println("Error: Failed to read from DHT sensor!");
  } else {
    displayValues(temperature, humidity);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
  
  // Wait before next reading
  delay(2000);
}

void displayError() {
  lcd.setCursor(0, 0);
  lcd.print("Sensor Error");
}

void displayValues(float temp, float hum) {
  // Display temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print((char)223); // Degree symbol
  lcd.print("C");
  
  // Display humidity
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(hum);
  lcd.print("%");
}
