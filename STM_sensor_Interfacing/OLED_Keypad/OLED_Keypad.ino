#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {PA1, PA2, PA3, PA4}; // Row pins
byte colPins[COLS] = {PA5, PA6, PA7}; // Column pins (ensure these are different)


Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], INPUT); // Set as input
  }
  for (int j = 0; j < COLS; j++) {
    pinMode(colPins[j], INPUT); // Set as input
  }
}

void loop() {
  char key = keypad.getKey(); // Get the pressed key

  if (key) { // Check if a key is pressed
    // Check for debouncing
    if (millis() - lastDebounceTime > debounceDelay) {
      Serial.print("Pressed: ");
      Serial.println(key); // Print the key value to the Serial Monitor
      lastDebounceTime = millis(); // Reset the debounce timer
    }
  }
}
