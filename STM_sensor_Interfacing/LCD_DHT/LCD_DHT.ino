#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>

DHT11 dht11(PB9); // DHT11 sensor connected to pin PB9
LiquidCrystal_I2C lcd(0x27,16,2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("DHT11 Sensor");
  lcd.setCursor(0,1);
  lcd.print("Initializing...");
  delay(2000); // Pause for 2 seconds before starting the main loop
  lcd.clear();
}

void loop() {
  int temperature = 0;
  int humidity = 0;

  // Attempt to read the temperature and humidity values from the DHT11 sensor
  int result = dht11.readTemperatureHumidity(temperature, humidity);
  
  if (result == 0) {
    // Successfully read from DHT11, display temperature and humidity
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");
    
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print(" %");
    
    // For debugging in Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    // Print error message based on the error code
    lcd.clear();
    lcd.print("Error: ");
    lcd.print(DHT11::getErrorString(result));
    
    // For debugging in Serial Monitor
    Serial.print("Error: ");
    Serial.println(DHT11::getErrorString(result));
  }

  delay(2000); // Wait for 2 seconds before the next reading
}
