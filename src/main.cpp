#include <Arduino.h>
#include <LiquidCrystal.h>
#include <RTClib.h>
#include <Wire.h>
#include <TMRpcm.h>
#include <SPI.h>
#include <SD.h>

#define SD_ChipSelectPin 10
RTC_DS1307 RTC;
TMRpcm tmrpcm;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  tmrpcm.speakerPin=9;
  Serial.begin(9600);

  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.print("SD fail");
    return;
  }
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  RTC.begin();
  // Check to see if the RTC is keeping time.  If it is, load the time from your computer.
  if (!RTC.isrunning())
  {
    Serial.println("RTC is NOT running!");
    // This will reflect the time that your sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  tmrpcm.setVolume(5);
  tmrpcm.play("bonito.wav");
}

void loop()
{
  DateTime now = RTC.now();

  lcd.clear();
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  delay(1000);
}
