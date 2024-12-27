#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define pins for the ultrasonic sensor
const int trigPin = PB5;  // Trig pin connected to PB5
const int echoPin = PB4;  // Echo pin connected to PB4

// Define pin for TTP223 touch sensor
const int touchPin = PB8; // TTP223 connected to PB8

// Variables for ultrasonic sensor
long duration;
int distance;

// State variable for locked/unlocked
bool isLocked = true;
bool lastTouchState = LOW;  // To detect state change of touch sensor

// Initialize the LCD with I2C address 0x27 and a 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT); // Set trigPin as an Output
  pinMode(echoPin, INPUT);  // Set echoPin as an Input

  // Set up TTP223 touch sensor pin
  pinMode(touchPin, INPUT);

  // Initialize Serial communication for debugging
  Serial.begin(9600);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sensor Kit");
  lcd.setCursor(0, 1);
    lcd.print("Initializing...");
  delay(2000); // Display welcome message for 2 seconds
  lcd.clear(); // Clear the display after welcome message
}

void loop() {
  // Read the current state of the touch sensor
  bool currentTouchState = digitalRead(touchPin);

  // Detect a rising edge (press) on the touch sensor to toggle the state
  if (currentTouchState == HIGH && lastTouchState == LOW) {
    isLocked = !isLocked;  // Toggle between locked and unlocked
    lcd.clear();           // Clear the LCD for new message
  }

  // Update the lastTouchState for the next loop iteration
  lastTouchState = currentTouchState;

  // Check if the system is locked or unlocked
  if (isLocked) {
    // If locked, show "Locked" on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Locked");
  } else {
    // If unlocked, show "Unlocked" and display the ultrasonic distance
    lcd.setCursor(0, 0);
    lcd.print("Unlocked");

    // Ultrasonic distance measurement process
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
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm");
  }

  delay(200); // Small delay to avoid bouncing and ensure stable sensor reading
}
