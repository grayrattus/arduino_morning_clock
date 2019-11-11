#include <Arduino.h>
#include <LiquidCrystal.h>
#include <MenuManager.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <CustomSoftwareSerial.h>
#include <Constants.h>
#include <TMRpcm.h>
#include <TimerManager.h>
#include <ClockManager.h>
#include <Wire.h>

#define SD_ChipSelectPin 10
RTC_DS1307 RTC;
TMRpcm tmrpcm;
CustomSoftwareSerial pcSerial(0, 1);
MenuManager menuManager(&pcSerial);
TimerManager timerManager(&tmrpcm, &pcSerial);

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void printTimeFromRtc(uint8_t hour, uint8_t minute, uint8_t second) {
    lcdClear(0, lcd);
    lcd.print(hour);
    lcd.print(':');
    lcd.print(minute);
    lcd.print(':');
    lcd.print(second);
}

void setup() {
    tmrpcm.speakerPin = 9;
    pcSerial.begin(9600, CSERIAL_8N1);

    if (!SD.begin(SD_ChipSelectPin)) {
        pcSerial.print("SD fail");
        return;
    }
    // set up the LCD's number of columns and rows:
    const int NUM_COLS = 16;
    const int NUM_ROWS = 2;
    lcd.begin(NUM_COLS, NUM_ROWS);
    // Print a message to the LCD.
    RTC.begin();
    // Check to see if the RTC is keeping time.  If it is, load the time from
    // your computer.
    if (!RTC.isrunning()) {
        pcSerial.println("RTC fail");
        // This will reflect the time that your sketch was compiled
        RTC.adjust(DateTime(__DATE__, __TIME__));
        return;
    }
}

void loop() {
    DateTime now = RTC.now();
    uint8_t hour = now.hour();
    uint8_t minute = now.minute();
    uint8_t second = now.second();
    timerManager.ring(hour, minute, second);
    printTimeFromRtc(hour, minute, second);

    menuManager.setIfSerialAvailable();

    const MenuCommands currentCommand = menuManager.getCurrentCommand();

    if (currentCommand == MenuCommands::MENU) {
        pcSerial.println(menuManager.getUserOutputForCommand());
        pcSerial.println(F("menu - show menu"));
        pcSerial.println(F("pset - set ring"));
        pcSerial.println(F("cset - set clock"));
        menuManager.setMenuCommand(MenuCommands::NONE_PRINT);
    }

    if (currentCommand == MenuCommands::CSET) {
        ClockManager clockManager(&RTC, &pcSerial);
        clockManager.startSettingNewDate();
        while (!clockManager.isTimeAccepted()) {
            clockManager.setIfSerialAvailable();
            lcdClear(1, lcd);
            lcd.print("Clock: " + clockManager.getCurrentSetDate());
            delay(100);
        }
        clockManager.sendSetDateToClock();
        menuManager.setMenuCommand(MenuCommands::PRING);
    }

    if (currentCommand == MenuCommands::PSET) {
        timerManager.startSettingNewDate();
        while (!timerManager.isTimeAccepted()) {
            timerManager.setIfSerialAvailable();
            DateTime lnow = RTC.now();
            uint8_t lhour = lnow.hour();
            uint8_t lminute = lnow.minute();
            uint8_t lsecond = lnow.second();
            timerManager.ring(lhour, lminute, lsecond);
            printTimeFromRtc(lhour, lminute, lsecond);
            lcdClear(1, lcd);
            lcd.print("Date:" + timerManager.getCurrentSetDate());
            delay(100);
        }
        menuManager.setMenuCommand(MenuCommands::PRING);
    }
    if (currentCommand == MenuCommands::PRING) {
        uint8_t hours = timerManager.getAcceptedTimeHours();
        uint8_t minutes = timerManager.getAcceptedTimeMinutes();
        uint8_t seconds = timerManager.getAcceptedTimeSeconds();

        lcdClear(1, lcd);
        lcd.print("RingAt:");
        lcd.print(hours);
        lcd.print(':');
        lcd.print(minutes);
        lcd.print(':');
        lcd.print(seconds);
        menuManager.setMenuCommand(MenuCommands::NONE_PRINT);
    }
    delay(100);
}
