#ifndef CONSTANTS_H
#define CONSTANTS_H

#define ASCII_NEW_LINE 10
#define ASCII_LINE_FEED 13
#define ASCII_BACKSPACE 8

#include <LiquidCrystal.h>
#include <CustomSoftwareSerial.h>

void clearPreviousLine(CustomSoftwareSerial* pcSerial);
void lcdClear(uint8_t row, LiquidCrystal& lcd); 

#endif