#include "SerialInputOutputTemplate.h"
#include "Constants.h"

SerialInputOutputTemplate::SerialInputOutputTemplate(CustomSoftwareSerial* pcSerial) {
    this->pcSerial = pcSerial;
}

void SerialInputOutputTemplate::setIfSerialAvailable() {
    if (this->pcSerial->available() > 0) {
        this->handleBeforeSent();
        uint8_t readed = this->pcSerial->read();
        this->pcSerial->print((char)readed);
        if (readed == ASCII_NEW_LINE || readed == ASCII_LINE_FEED) {
            this->handleEnter();
        } else if (readed == ASCII_BACKSPACE) {
            this->handleBackspace();
        } else {
            this->handleChange(readed);
        }
    }
}

CustomSoftwareSerial* SerialInputOutputTemplate::getPcSerial() {
    return this->pcSerial;
}

void SerialInputOutputTemplate::handleBeforeSent(){

}