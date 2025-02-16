// Rain gauge callibration code
// Inspired by MicroPython code by Christopher Barnett
// License: MIT: https://cahamo.mit-license.org

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ezButton.h>

#define LCD_WIDTH   16
#define LCD_HEIGHT   2

LiquidCrystal_I2C lcd(0x27, LCD_WIDTH, LCD_HEIGHT);

#define REED_SWITCH_PIN 6
#define RESET_SWITCH_PIN 2
#define DEBOUNCE_DELAY 50

ezButton btnReed(REED_SWITCH_PIN, INPUT_PULLUP);
ezButton btnReset(RESET_SWITCH_PIN, INPUT_PULLUP);

void printCount();

void setup() {
  Serial.begin(115200);
  btnReed.setDebounceTime(DEBOUNCE_DELAY);
  btnReed.setCountMode(COUNT_FALLING);
  btnReset.setDebounceTime(DEBOUNCE_DELAY);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready ...");
  Serial.println("Ready ...");
}

void loop() {
    // MUST call the .loop() method for every ezButton each time round the loop
    btnReed.loop();
    btnReset.loop();

    if (btnReed.isPressed()) {
      printCount();
    }

    if (btnReset.isPressed()) {
      Serial.println("Reset");
      btnReed.resetCount();
      printCount();
    }
}

void printCount() {
  unsigned long count = btnReed.getCount();
  Serial.print("Count = ");
  Serial.println(count);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Count = ");
  lcd.print(String(count));
}