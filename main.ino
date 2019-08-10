#include <LiquidCrystal.h>
#include <DS3231.h>

const int PIN_RS = 8; 
const int PIN_EN = 9; 

const int PIN_D4 = 4; 
const int PIN_D5 = 5; 
const int PIN_D6 = 6; 
const int PIN_D7 = 7; 

const int PIN_BL = 10;  // Backlight pin.

LiquidCrystal lcd(PIN_RS,  PIN_EN,  PIN_D4,  PIN_D5,  PIN_D6,  PIN_D7);
DS3231  rtc(A4, A5);

// Draws the 6 character clock icon at a specified (x, y) position.
void drawClock(int x=0, int y=0) {
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 3; i++) {
            lcd.setCursor(x+i, y+j);
            lcd.write(i + (j == 1 ? 3:0));  //If drawing bottom row start at 3, if not, start at 0.
        }
    }   
}

void drawTime(int x=4, int y=0) {
    lcd.setCursor(x, y);
    lcd.print(rtc.getTimeStr());
}

void setup() {
 lcd.begin(16, 2);
 
 lcd.createChar(0, CLOCK_TOP_LEFT);
 lcd.createChar(1, CLOCK_TOP_MIDDLE);
 lcd.createChar(2, CLOCK_TOP_RIGHT);
 lcd.createChar(3, CLOCK_BOTTOM_LEFT);
 lcd.createChar(4, CLOCK_BOTTOM_MIDDLE);
 lcd.createChar(5, CLOCK_BOTTOM_RIGHT);

 drawClock();

 pinMode(PIN_BL, OUTPUT);
 digitalWrite(PIN_BL, HIGH);

 rtc.begin();
}

void loop() {
    drawTime();
    delay(1000);
}

