#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define pins for the ultrasonic sensor
const int trigPin = PA0;  // Trig pin connected to PB5
const int echoPin = PA1;  // Echo pin connected to PB4

// Variables for ultrasonic sensor
long duration;
int distance;

// Initialize the OLED display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // -1 for reset pin

void setup() {
  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT); // Set trigPin as an Output
  pinMode(echoPin, INPUT);  // Set echoPin as an Input

  // Initialize Serial communication for debugging
  Serial.begin(9600);

  // Initialize the OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // I2C address 0x3C
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.println("Distance Sensor");
  display.display();
  delay(2000); // Display welcome message for 2 seconds
  display.clearDisplay(); // Clear the display after the welcome message
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond pulse to the trigPin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin and calculate the time taken for the pulse
  duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout

  // Check if the duration is valid
  if (duration == 0) {
    display.clearDisplay(); // Clear the display
    display.setCursor(0, 0); // Set cursor to the top-left corner
    display.println("Sensor not detected");
    display.display(); // Update the display
  } else {
    // Calculate the distance (duration * speed of sound / 2)
    distance = duration * 0.034 / 2;

    // Display the distance on the OLED
    display.clearDisplay(); // Clear the display
    display.setCursor(0, 0); // Set cursor to the top-left corner
    display.print("Distance: ");
    display.print(distance);
    display.println(" cm");
    display.display(); // Update the display
  }

  delay(1000); // Update every second
}
