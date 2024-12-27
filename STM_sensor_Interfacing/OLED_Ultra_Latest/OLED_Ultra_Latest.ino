#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Ultrasonic Sensor Pins
#define TRIG_PIN PA0
#define ECHO_PIN PA1

void setup() {
  // Initialize Serial Communication
  Serial.begin(9600);

  // Initialize Ultrasonic Sensor Pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();                // Clear OLED screen
  display.setTextSize(1);                // Set text size to normal
  display.setTextColor(SSD1306_WHITE);   // Set text color to white
  display.setCursor(10, 10);             // Set initial message position
  display.print(F("Initializing..."));   // Display startup message
  display.display();                     // Render to OLED
  delay(2000);                           // Wait for 2 seconds
  display.clearDisplay();                // Clear the screen
}

float getDistance() {
  float totalDistance = 0;
  const int samples = 10; // Number of readings to average

  for (int i = 0; i < samples; i++) {
    // Send ultrasonic pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Measure the pulse duration
    long duration = pulseIn(ECHO_PIN, HIGH);

    // Calculate distance in cm
    float distance = duration * 0.034 / 2;
    totalDistance += distance;

    delay(50); // Short delay between readings
  }

  // Return the average distance
  return totalDistance / samples;
}

void loop() {
  float distance = getDistance();

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Display distance on OLED
  display.clearDisplay();                // Clear the OLED screen
  display.setTextSize(1);                // Set text size
  display.setCursor(0, 10);              // Set cursor position
  display.print("Distance: ");           // Print label
  display.print(distance, 2);            // Print distance with 2 decimal places
  display.print(" cm");                  // Add "cm" unit
  display.display();                     // Render the text to the screen

  delay(500); // Wait before the next measurement
}
