#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();

  display.setTextSize(1);             // Set text size to normal
  display.setTextColor(SSD1306_WHITE); // Set text color to white
  display.setCursor(10, 10);           // Set cursor to position (10, 10)
  display.print(F("OLED working")); // Display the message
  display.display();                   // Render the text to the screen
}

void loop() {
  // Nothing to do in the loop
}
