#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width in pixels
#define SCREEN_HEIGHT 64 // OLED display height in pixels
#define OLED_RESET    -1 // Reset pin (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int Vibration_signal = PA2; // Pin connected to the vibration sensor
int Sensor_State = 0;

void setup() {
  pinMode(Vibration_signal, INPUT); 
  Serial.begin(9600);               // Start the serial communication

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Adjust address if necessary
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Halt if display initialization fails
  }
  display.clearDisplay(); // Clear the display buffer
}

void loop() {
  Sensor_State = digitalRead(Vibration_signal); // Read the sensor state

  // Clear the display before printing new content
  display.clearDisplay();
  display.setTextSize(1);               // Set text size
  display.setTextColor(SSD1306_WHITE);  // Set text color
  display.setCursor(0, 0);              // Set cursor position

  if (Sensor_State == HIGH) {
    Serial.println("Sensing vibration");
    display.print("Vibration status: Sensing vibration");
  } else {
    Serial.println("No vibration");
    display.print("Vibration status: No vibration");
  }

  display.display(); // Update display with new content
  delay(500); // Delay for readability
}
