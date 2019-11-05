#include <Arduino.h>
#include <LiquidCrystal.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>
#include <TimerManager.h>
#include <Wire.h>

#define SD_ChipSelectPin 10
RTC_DS1307 RTC;
TMRpcm tmrpcm;
TimerManager timerManager(&tmrpcm);

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
    tmrpcm.speakerPin = 9;
    Serial.begin(9600);

    if (!SD.begin(SD_ChipSelectPin)) {
        Serial.print("SD fail");
        return;
    }
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    RTC.begin();
    // Check to see if the RTC is keeping time.  If it is, load the time from
    // your computer.
    if (!RTC.isrunning()) {
        Serial.println("RTC is NOT running!");
        // This will reflect the time that your sketch was compiled
        RTC.adjust(DateTime(__DATE__, __TIME__));
    }
}

void loop() {
    DateTime now = RTC.now();

    timerManager.setDateIfSerialAvailable();
    lcd.clear();
    uint8_t hour = now.hour();
    uint8_t minute = now.minute();
    uint8_t second = now.second();
    lcd.print(hour);
    lcd.print(':');
    lcd.print(minute);
    lcd.print(':');
    lcd.print(second);

    lcd.setCursor(0, 1);
    if (timerManager.isDateValid()) {
        uint8_t hours = timerManager.getHours();
        uint8_t minutes = timerManager.getMinutes();
        uint8_t seconds = timerManager.getSeconds();

        lcd.print("RingAt:");
        lcd.print(hours);
        lcd.print(':');
        lcd.print(minutes);
        lcd.print(':');
        lcd.print(seconds);

        timerManager.ring(hour, minute, second);
    } else {
        lcd.print("Date:" + timerManager.getCurrentSetDate());
    }

    delay(1000);
}
