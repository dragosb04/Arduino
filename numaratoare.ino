#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inițializezi LCD-ul I2C la adresa 0x27 (sau 0x3F, în funcție de model)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Pornești LCD-ul
  lcd.init();
  
  // Activezi iluminarea de fundal
  lcd.backlight();
}

void loop() {
  for (int i = 0; i >= -10; i--){
      lcd.print("Counter: ");
      lcd.setCursor(9, 0);
      lcd.print(i);
      delay(500);
      lcd.clear();
  }

}
