#include <Arduino.h>
#include <LiquidCrystal.h>
#include <MenuManager.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <TMRpcm.h>
#include <TimerManager.h>
#include <Wire.h>

#define SD_ChipSelectPin 10
RTC_DS1307 RTC;
TMRpcm tmrpcm;
SoftwareSerial pcSerial(0, 1);
MenuManager menuManager(&pcSerial);
TimerManager timerManager(&tmrpcm, &pcSerial);

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void printDateFromRtc(uint8_t hour, uint8_t minute, uint8_t second) {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(hour);
    lcd.print(':');
    lcd.print(minute);
    lcd.print(':');
    lcd.print(second);
}

void setup() {
    tmrpcm.speakerPin = 9;
    pcSerial.begin(9600);
    pcSerial.println("Restarting");

    if (!SD.begin(SD_ChipSelectPin)) {
        pcSerial.print("SD fail");
        return;
    }
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    RTC.begin();
    // Check to see if the RTC is keeping time.  If it is, load the time from
    // your computer.
    if (!RTC.isrunning()) {
        pcSerial.println("RTC is NOT running!");
        // This will reflect the time that your sketch was compiled
        RTC.adjust(DateTime(__DATE__, __TIME__));
        return;
    }
    lcd.setCursor(0, 1);
    lcd.print("Date:" + timerManager.getCurrentSetDate());
}

void loop() {
    DateTime now = RTC.now();
    uint8_t hour = now.hour();
    uint8_t minute = now.minute();
    uint8_t second = now.second();
    timerManager.ring(hour, minute, second);
    printDateFromRtc(hour, minute, second);

    menuManager.setMenuCommandIfSerialAvailable();

    const MenuCommands currentCommand = menuManager.getCurrentCommand();

    if (currentCommand == MenuCommands::MENU) {
        pcSerial.println(menuManager.getUserOutputForCommand());
        pcSerial.println("menu - show menu");
        pcSerial.println("pring - show time of ring");
        pcSerial.println("pset - set ring");
        menuManager.setMenuCommand(MenuCommands::PRING);
    }

    if (currentCommand == MenuCommands::PSET_DATE) {
        timerManager.startSettingNewDate();
        while (!timerManager.isTimeAccepted()) {
            timerManager.setDateIfSerialAvailable();
            DateTime lnow = RTC.now();
            uint8_t lhour = lnow.hour();
            uint8_t lminute = lnow.minute();
            uint8_t lsecond = lnow.second();
            timerManager.ring(lhour, lminute, lsecond);
            printDateFromRtc(lhour, lminute, lsecond);
            lcd.setCursor(0, 1);
            lcd.print("                ");
            lcd.setCursor(0, 1);
            lcd.print("Date:" + timerManager.getCurrentSetDate());
            delay(250);
        }
        menuManager.setMenuCommand(MenuCommands::PRING);
    }
    if (currentCommand == MenuCommands::PRING) {
        uint8_t hours = timerManager.getAcceptedTimeHours();
        uint8_t minutes = timerManager.getAcceptedTimeMinutes();
        uint8_t seconds = timerManager.getAcceptedTimeSeconds();

        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("RingAt:");
        lcd.print(hours);
        lcd.print(':');
        lcd.print(minutes);
        lcd.print(':');
        lcd.print(seconds);
        menuManager.setMenuCommand(MenuCommands::NONE_PRINT);
    }
    delay(250);
}
