#include <Constants.h>
void clearPreviousLine(CustomSoftwareSerial* pcSerial) {
    pcSerial->print((char)ASCII_LINE_FEED);
    pcSerial->print("        ");
    pcSerial->print((char)ASCII_LINE_FEED);
}

void lcdClear(uint8_t row, LiquidCrystal& lcd) {
    lcd.setCursor(0, row);
    lcd.print("                ");
    lcd.setCursor(0, row);
}