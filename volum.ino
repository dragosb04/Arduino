#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inițializezi LCD-ul I2C la adresa 0x27 (16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definiți caractere personalizate pentru bara de volum
byte volume0[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000}; // gol
byte volume1[8] = {B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000}; // pe sfert
byte volume2[8] = {B11000, B11000, B11000, B11000, B11000, B11000, B11000, B11000}; // pe jumătate
byte volume3[8] = {B11100, B11100, B11100, B11100, B11100, B11100, B11100, B11100}; // aproape plin
byte volume4[8] = {B11110, B11110, B11110, B11110, B11110, B11110, B11110, B11110}; // plin

void setup() {
  lcd.init();
  lcd.backlight();

  // Creează caracterele personalizate
  lcd.createChar(0, volume0);
  lcd.createChar(1, volume1);
  lcd.createChar(2, volume2);
  lcd.createChar(3, volume3);
  lcd.createChar(4, volume4);

  // Afișează mesajul inițial
  lcd.setCursor(0, 0); // Plasează cursorul la începutul primei linii
  lcd.print("Volum: ");
}

void loop() {
  // Exemplu de actualizare a barei de volum
  int volume = analogRead(A0);  // Citește valoarea de pe pinul analog (0-1023)
  int volumeLevel = map(volume, 0, 1023, 0, 16);  // Mapăm valoarea la o scară de la 0 la 16 blocuri

  // Afișează bara de volum
  lcd.setCursor(0, 1); // Plasează cursorul la începutul celei de-a doua linii
  for (int i = 0; i < 16; i++) {
    if (i < volumeLevel) {
      lcd.write(byte(4));  // Afișează bloc plin
    } else {
      lcd.write(byte(0));  // Afișează bloc gol
    }
  }

  delay(500);  // Pauză între actualizări
}
