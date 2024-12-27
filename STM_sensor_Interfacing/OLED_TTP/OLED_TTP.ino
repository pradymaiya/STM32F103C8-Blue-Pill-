#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TOUCH_PIN PA8  // Pin connected to the touch sensor

void setup() {
  Serial.begin(9600);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Touch Sensor Test"));
  display.display(); // Render the initial message

  // Initialize the touch sensor pin
  pinMode(TOUCH_PIN, INPUT);
  Serial.println("Touch sensor initialized!");
}

void loop() {
  int touchState = digitalRead(TOUCH_PIN); // Read the state of the touch sensor

  // Display touch status on the Serial Monitor
  if (touchState == HIGH) {
    Serial.println("Touch detected!");
  } else {
    Serial.println("No touch detected.");
  }

  // Display touch status on the OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Touch Status:");
  display.setCursor(0, 16);
  
  if (touchState == HIGH) {
    display.print("Detected");
  } else {
    display.print("Not Detected");
  }
  display.display();

  delay(500); // Delay for readability
}
