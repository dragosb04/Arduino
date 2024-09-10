#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with the I2C address (usually 0x27 or 0x3F) and size (16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int potPin = A0; // Potentiometer pin
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10}; // LED pins
const int numLeds = 9;

void setup() {
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight

  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT); // Set LED pins as outputs
  }
}

void loop() {
  int potValue = analogRead(potPin); // Read potentiometer value
  int ledIndex = map(potValue, 0, 1023, 0, numLeds); // Map value to number of LEDs

  if (ledIndex == 0) {
    // No LEDs lit
    displayMessage("Semafor Oprit");
    turnOffAllLeds(); // Ensure all LEDs are off
  } else if (ledIndex <= 3) {
    // Red
    setLeds(3, 'R'); // Always light 3 LEDs
  } else if (ledIndex <= 6) {
    // Yellow
    setLeds(3, 'Y'); // Always light 3 LEDs
  } else {
    // Green
    setLeds(3, 'G'); // Always light 3 LEDs
  }
}

void setLeds(int count, char color) {
  int startIdx = (color == 'R') ? 0 : (color == 'Y') ? 3 : 6;
  int endIdx = startIdx + 3;

  // Turn off all LEDs first
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  // Turn on the LEDs for the current color group
  for (int i = startIdx; i < startIdx + count; i++) {
    if (i < endIdx) {
      digitalWrite(ledPins[i], HIGH);
    }
  }

  // Update LCD based on the color
  displayMessage((color == 'G') ? "Start" : (color == 'Y') ? "Incetineste" : "Stop");
}

void turnOffAllLeds() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

void displayMessage(const char* message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Semafor Control");
  lcd.setCursor(0, 1);
  lcd.print(message);
  delay(1000);
}
