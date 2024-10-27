#include <Wire.h>
#include <BMP180advanced.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

BMP180advanced myBMP(BMP180_ULTRAHIGHRES);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(F("Initializing BMP180..."));
    display.display();

    if (!myBMP.begin()) {
        Serial.println("BMP180 Initialization failed");
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("BMP180 Init Fail");
        display.display();
        while (1);
    }
    delay(1000);
}

void loop() {
    display.clearDisplay();

    float temperature = myBMP.getTemperature() - 6.9;
    float pressure = myBMP.getPressure_hPa();
    float seaLevelPressure = myBMP.getSeaLevelPressure_hPa(893);  // Using altitude 893 meters

    // Display temperature
    display.setCursor(0, 0);
    display.print("Temp: ");
    display.print(temperature);
    display.print(" C");

    // Display pressure
    display.setCursor(0, 10);
    display.print("Pressure: ");
    display.print(pressure);
    display.print(" hPa");

    // Display sea level pressure
    display.setCursor(0, 20);
    display.print("Sea Level: ");
    display.print(seaLevelPressure);
    display.print(" hPa");

    display.display();

    delay(10000);  // Longer delay for more stable readings
}
