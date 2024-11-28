#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define S0 PB13
#define S1 PB14
#define S2 PB4
#define S3 PB3
#define sensorOut PB5

// OLED screen settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int redFrequency = 0, greenFrequency = 0, blueFrequency = 0;

// Define tolerance range for color detection
const int tolerance = 5; // Reduced tolerance to tighten the color ranges

void setup() {
  // Configure pins for TCS3200 color sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Initialize Serial for debugging
  Serial.begin(9600);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Infinite loop if display fails
  }

  display.clearDisplay();
  display.setTextSize(1);             // Set text size to normal
  display.setTextColor(SSD1306_WHITE); // Set text color to white
}

void loop() {
  // Read Red
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);

  // Read Green
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);

  // Read Blue
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);

  // Print RGB values on Serial Monitor (for debugging)
  Serial.print("R= ");
  Serial.print(redFrequency);
  Serial.print(" G= ");
  Serial.print(greenFrequency);
  Serial.print(" B= ");
  Serial.print(blueFrequency);
  Serial.print(" -> Detected Color: ");

  // Display RGB values on OLED
  display.clearDisplay();
  display.setCursor(0, 0);            // Start at the top left corner
  display.print("R: ");
  display.print(redFrequency);
  display.setCursor(0, 10);           // Move cursor to next line
  display.print("G: ");
  display.print(greenFrequency);
  display.setCursor(0, 20);           // Move cursor to next line
  display.print("B: ");
  display.print(blueFrequency);
  
  display.display();                  // Render the text to the screen

  delay(1000); // Update every second
}
