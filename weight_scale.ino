#include <HX711.h>
#include <LiquidCrystal.h>

// HX711 Pins
#define DOUT_PIN  3
#define SCK_PIN   2

// LCD Pins (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

HX711 scale;

// Calibration factor — adjust this value after calibration
float calibration_factor = -7050.0;

void setup() {
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Digital Scale");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

  // Initialize HX711
  scale.begin(DOUT_PIN, SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare(); // Reset scale to 0

  lcd.setCursor(0, 0);
  lcd.print("Scale Ready!");
  lcd.setCursor(0, 1);
  lcd.print("Place object...");
  delay(1500);
  lcd.clear();
}

void loop() {
  if (scale.is_ready()) {
    float weight = scale.get_units(10); // Average of 10 readings

    // Prevent negative values
    if (weight < 0) weight = 0;

    // Display on LCD
    lcd.setCursor(0, 0);
    lcd.print("Weight:         ");
    lcd.setCursor(0, 1);
    lcd.print(weight, 2);
    lcd.print(" kg         ");

    // Print to Serial Monitor
    Serial.print("Weight: ");
    Serial.print(weight, 2);
    Serial.println(" kg");

  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    lcd.setCursor(0, 1);
    lcd.print("Check HX711");
    Serial.println("HX711 not found.");
  }

  delay(500);
}
