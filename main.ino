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

// Each value (hour, minute and second) are represented by their two digits for easier input.
int alarmTime[6];

// Tracks current menu. 0 is the main menu, 1 is the alarm setting menu.
int menuState = 0;


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

// Draws menu where you can set the alarm.
void drawAlarmConfiguration(int x=4, int y=0) {
    drawClock();
    
    lcd.setCursor(x, y);
    lcd.print("Set alarm:");

    lcd.setCursor(x, y+1);
    for (int i = 0; i < 6; i++) {
        lcd.print(alarmTime[i]);
        
        if (i == 1 || i == 3) { 
            lcd.print(":"); 
        }
    }
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

// Returns an int between 0 and 5 inclusive depending on the button pressed. 
int readButtonPress() {
    int read;
    read = analogRead(A0);

    if      (read < 60 ) { return 1; }  // Right
    else if (read < 200) { return 2; }  // Up
    else if (read < 400) { return 3; }  // Down
    else if (read < 600) { return 4; }  // Left
    else if (read < 800) { return 5; }  // Select
    else                 { return 0; }  // Nothing pressed
} 

// Switches to another menu.
void switchToMenu(int newMenu = 0) {
    lcd.clear();
    menuState = newMenu;
    delay(1000);  // Time to allow the user to let go of the button.
}

void setup() {
    lcd.begin(16, 2);
    createCharacters();

    // Initialize the LCD backlight to ON. 
    pinMode(PIN_BL, OUTPUT);
    digitalWrite(PIN_BL, HIGH); 
    
    rtc.begin();

    Serial.begin(9600);
}

void loop() {
    switch (menuState) {
        case 0:
            drawMenu();
            if (readButtonPress() == 5) { switchToMenu(1); }
            break;
        case 1:
            drawAlarmConfiguration();
            if (readButtonPress() == 5) { switchToMenu(0); }
            break;
    }

}

