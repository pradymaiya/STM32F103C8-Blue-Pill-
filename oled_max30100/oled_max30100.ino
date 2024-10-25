#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define REPORTING_PERIOD_MS 1000
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

PulseOximeter pox;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
uint32_t tsLastReport = 0;

void onBeatDetected() {
    Serial.println("Beat detected!");
}

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing MAX30100...");

    // Initialize the OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Stop if OLED initialization fails
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 0);
    display.print(F("Initializing..."));
    display.display();

    // Initialize the sensor
    if (!pox.begin()) {
        Serial.println("Failed to initialize MAX30100");
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Sensor Init Fail");
        display.display();
        while (1);
    }

    // Configure the sensor
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Place Finger...");
    display.display();
    Serial.println("Place your finger on the sensor...");
}

void loop() {
    // Update the sensor readings
    pox.update();

    // Print and display the heart rate and SpO2 value
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        float heartRate = pox.getHeartRate();
        float spO2 = pox.getSpO2();

        // Print to Serial Monitor
        Serial.print("Heart rate: ");
        Serial.print(heartRate);
        Serial.print(" bpm / SpO2: ");
        Serial.print(spO2);
        Serial.println(" %");

        // Display on the OLED
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("HR: ");
        display.print(heartRate);
        display.print(" bpm");

        display.setCursor(0, 16);
        display.print("SpO2: ");
        display.print(spO2);
        display.print(" %");
        display.display();

        tsLastReport = millis();
    }
}
