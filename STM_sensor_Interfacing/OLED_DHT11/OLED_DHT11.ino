#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHT_PIN PA4  
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {

  Serial.begin(9600);

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.print(F("Initializing..."));
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  float temperature = dht.readTemperature(); 
  float humidity = dht.readHumidity();       

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT11 sensor!"));

    display.clearDisplay();
    display.setCursor(10, 10);
    display.print(F("DHT11 Error!"));
    display.display();

  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Display temperature and humidity on OLED
    display.clearDisplay();

    display.setCursor(0, 0);
    display.print("Temp: ");
    display.print(temperature, 1); // One decimal place
    display.print(" C");

    display.setCursor(0, 16);
    display.print("Humidity: ");
    display.print(humidity, 1); // One decimal place
    display.print(" %");

    display.display();
  }

  // Wait for 2 seconds before next reading
  delay(2000);
}
