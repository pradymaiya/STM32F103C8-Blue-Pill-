#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16x2 display

void setup() {
  // Initialize Serial Monitor for debugging (optional)
  Serial.begin(9600);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Print "Hello, World!" on the LCD
  lcd.setCursor(0, 0);       // Set cursor to the first column, first row
  lcd.print("Hello, World!"); // Display the message
}

void loop() {
  // Nothing to do in the loop for this example
}