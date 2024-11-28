#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define GPS_BAUD 9600

void setup() {
  Serial.begin(9600);
  Serial1.begin(GPS_BAUD);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Waiting for GPS fix...");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  if (Serial1.available()) {
    String gpsData = Serial1.readStringUntil('\n');

    if (gpsData.startsWith("$GPGGA")) {
      String latitude = parseLatitude(gpsData);
      String longitude = parseLongitude(gpsData);

      if (latitude != "" && longitude != "") {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.setTextSize(1);
        display.print("Latitude: ");
        display.print(latitude);
        display.setCursor(0, 10);
        display.print("Longitude: ");
        display.print(longitude);
        display.setCursor(0, 20); // Move cursor down for dashes
        display.print("-------------");
        display.setCursor(0, 30); // Move cursor down for dashes
        display.print("-------------");
        display.display();

        Serial.print("Latitude: ");
        Serial.println(latitude);
        Serial.print("Longitude: ");
        Serial.println(longitude);
      } else {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("No GPS Fix");
        display.display();
      }
      delay(1000);
    }
  }
}

// Function to parse latitude from $GPGGA sentence
String parseLatitude(String sentence) {
  int thirdComma = nthIndex(sentence, ',', 2);
  int fourthComma = nthIndex(sentence, ',', 3);
  int fifthComma = nthIndex(sentence, ',', 4);

  String latitude = sentence.substring(thirdComma + 1, fourthComma);
  String latDir = sentence.substring(fourthComma + 1, fifthComma);

  if (latitude != "") {
    return convertToDegrees(latitude, 2) + " " + latDir;
  }
  return "";
}

// Function to parse longitude from $GPGGA sentence
String parseLongitude(String sentence) {
  int fifthComma = nthIndex(sentence, ',', 4);
  int sixthComma = nthIndex(sentence, ',', 5);
  int seventhComma = nthIndex(sentence, ',', 6);

  String longitude = sentence.substring(fifthComma + 1, sixthComma);
  String longDir = sentence.substring(sixthComma + 1, seventhComma);

  if (longitude != "") {
    return convertToDegrees(longitude, 3) + " " + longDir;
  }
  return "";
}

// Helper function to convert from ddmm.mmmm or dddmm.mmmm to dd° mm.mmmm' format
String convertToDegrees(String coord, int degreesLength) {
  String degrees = coord.substring(0, degreesLength);
  String minutes = coord.substring(degreesLength);

  return degrees + "° " + minutes + "'";
}

// Helper function to find the nth occurrence of a character
int nthIndex(String str, char ch, int n) {
  int index = -1;
  while (n-- > 0) {
    index = str.indexOf(ch, index + 1);
    if (index == -1) break;
  }
  return index;
}
