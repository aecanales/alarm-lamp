#include <LiquidCrystal.h>

const int PIN_RS = 8; 
const int PIN_EN = 9; 

const int PIN_D4 = 4; 
const int PIN_D5 = 5; 
const int PIN_D6 = 6; 
const int PIN_D7 = 7; 

const int PIN_BL = 10;  // Backlight pin.

LiquidCrystal lcd(PIN_RS,  PIN_EN,  PIN_D4,  PIN_D5,  PIN_D6,  PIN_D7);

void setup() {
 lcd.begin(16, 2);
 
 lcd.createChar(0, CLOCK_TOP_LEFT);
 lcd.createChar(1, CLOCK_TOP_RIGHT);
 lcd.createChar(2, CLOCK_BOTTOM_LEFT);
 lcd.createChar(3, CLOCK_BOTTOM_RIGHT);
 
 lcd.home();
 lcd.write(byte(0));
 lcd.setCursor(1, 0);
 lcd.write(1);
 lcd.setCursor(0, 1);
 lcd.write(2);
 lcd.setCursor(1, 1);
 lcd.write(3);

 pinMode(PIN_BL, OUTPUT);
 digitalWrite(PIN_BL, HIGH);
}

void loop() {

}