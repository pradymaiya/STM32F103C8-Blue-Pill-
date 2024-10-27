#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define the analog pin connected to the MQ-2 A0 output
#define MQ2_ANALOG_PIN PA0

float baselineValue = 0; // Baseline analog value in clean air

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.print(F("Calibrating..."));
  display.display();

  // Take a baseline reading in clean air
  long sum = 0;
  for (int i = 0; i < 100; i++) {
    sum += analogRead(MQ2_ANALOG_PIN);
    delay(50);
  }
  baselineValue = sum / 100.0;

  display.clearDisplay();
  display.setCursor(10, 10);
  display.print(F("Calibration done"));
  display.display();
  delay(2000); // Display calibration complete message
  display.clearDisplay();
}

void loop() {
  int analogValue = analogRead(MQ2_ANALOG_PIN); // Read the analog output from MQ-2 sensor
  float adjustedValue = analogValue - baselineValue; // Subtract baseline
  float gasLevel = (adjustedValue / 4095.0) * 100; // Calculate gas level percentage
  float smokeLevel = (adjustedValue / 4095.0) * 200; // Scale smoke level differently

  // Ensure levels don't go negative if baseline is higher
  gasLevel = gasLevel < 0 ? 0 : gasLevel;
  smokeLevel = smokeLevel < 0 ? 0 : smokeLevel;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);

  display.print("Gas Level: ");
  display.print(gasLevel, 1); // Display gas level with 1 decimal place
  display.println("%");

  display.print("Smoke Level: ");
  display.print(smokeLevel, 1); // Display smoke level with 1 decimal place
  display.display();

  delay(1000); // Update every second
}
