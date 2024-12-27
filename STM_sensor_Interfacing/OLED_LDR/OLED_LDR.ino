#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int sensorPin = PA3; 
int sensorValue = 0; 

void setup() {
  Serial.begin(9600); // Initialize Serial communication

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Loop forever if initialization fails
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Light Intensity:"));
  display.display();
  delay(2000); // Pause for 2 seconds before starting the main loop
}

void loop() {
  // Read the value from the LDR sensor (0-4095 for STM32)
  sensorValue = analogRead(sensorPin);

  // Convert the sensor value to light intensity percentage
  float lightIntensity = (sensorValue / 4095.0) * 100; // STM32 analogRead range is 0-4095

  // Debugging: Print light intensity to Serial Monitor
  Serial.print("Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.println(" %");

  // Display light intensity on the OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Title
  display.setCursor(0, 0);
  display.print(F("Light Intensity:"));

  // Light intensity value
  display.setCursor(0, 16);
  display.print(lightIntensity, 1); // Display with 1 decimal precision
  display.print(" %");

  display.display();

  delay(1000); // Wait for a second before the next reading
}
