#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define pins for the ultrasonic sensor
const int trigPin = PB5;  // Trig pin connected to PB5
const int echoPin = PB4;  // Echo pin connected to PB4

// Variables for ultrasonic sensor
long duration;
int distance;

// Initialize the LCD with I2C address 0x27 and a 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT); // Set trigPin as an Output
  pinMode(echoPin, INPUT);  // Set echoPin as an Input

  // Initialize Serial communication for debugging
  Serial.begin(9600);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Distance Sensor");
  delay(2000); // Display welcome message for 2 seconds
  lcd.clear(); // Clear the display after welcome message
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
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance (duration * speed of sound / 2)
  distance = duration * 0.034 / 2;



  // Display the distance on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");

  delay(1000); // Update every second
}
