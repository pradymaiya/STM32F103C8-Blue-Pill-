#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int sensorPin = PA0; // select the input pin for LDR (PA0 corresponds to A0 on STM32)
int sensorValue = 0; // variable to store the value coming from the sensor

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600); //sets serial port for communication
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("Light Intensity");
  delay(2000); // Pause for 2 seconds before starting the main loop
  lcd.clear();
}

void loop() {
  sensorValue = analogRead(sensorPin); // read the value from the LDR sensor (0-4095 for STM32)

  // Convert sensor value to light intensity percentage
  float lightIntensity = (sensorValue / 4095.0) * 100; // STM32 analogRead range is 0-4095

   // Display the light intensity percentage on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.print(lightIntensity);
  lcd.print(" %");

  delay(1000); // wait for a second before next reading
}
