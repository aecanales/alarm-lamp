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

// Draws the 1 character clock icon and the current time from the RTC module.
void drawTime(int x=5, int y=0) {
    lcd.setCursor(x, y);
    lcd.write(6);

    lcd.setCursor(x+2, y);
    lcd.print(rtc.getTimeStr());
}

// Draws the 1 character bell icon and the time the alarm is currently set to.
void drawSetAlarm(int x=5, int y=1) {
    lcd.setCursor(x, y+1);
    lcd.write(7);

    lcd.setCursor(x+2, y+1);
    lcd.print("OFF");
}

// Draws the main menu including clock icon, current time, and alamt set time.
void drawMenu() {
    drawClock();
    drawTime();
    drawSetAlarm();
}

/* Initializes the custom LCD characters. 
   0-6 are the clock drawing, while 6 is a clock and 7 is a bell. */
void createCharacters() {
    lcd.createChar(0, CLOCK_TOP_LEFT);
    lcd.createChar(1, CLOCK_TOP_MIDDLE);
    lcd.createChar(2, CLOCK_TOP_RIGHT);
    lcd.createChar(3, CLOCK_BOTTOM_LEFT);
    lcd.createChar(4, CLOCK_BOTTOM_MIDDLE);
    lcd.createChar(5, CLOCK_BOTTOM_RIGHT);
    lcd.createChar(6, CLOCK);
    lcd.createChar(7, BELL);
}

void setup() {
    lcd.begin(16, 2);
    createCharacters();

    // Initialize the LCD backlight to ON. 
    pinMode(PIN_BL, OUTPUT);
    digitalWrite(PIN_BL, HIGH); 
    
    rtc.begin();
}

void loop() {
    drawMenu();
    delay(1000);
}

