#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27. Adjust if needed.
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the keypad size and keys
const byte ROWS = 4;  // Four rows
const byte COLS = 3;  // Three columns

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {PA0, PA1, PA2, PA3}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {PA4, PA5, PA6};     // Connect to the column pinouts of the keypad

// Create the keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Keypad + LCD");

  delay(2000); // Wait for 2 seconds
  lcd.clear();
}

void loop() {
  // Get the key pressed on the keypad
  char key = keypad.getKey();

  // If a key is pressed, display it on the LCD
  if (key) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Key Pressed:");
    lcd.setCursor(0, 1);
    lcd.print(key);

    Serial.println(key); // Print key to Serial Monitor as well
  }
}
