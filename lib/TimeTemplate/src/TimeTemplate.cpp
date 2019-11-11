#include "TimeTemplate.h"
#include "Constants.h"

TimeTemplate::TimeTemplate(CustomSoftwareSerial* pcSerial)
    : SerialInputOutputTemplate(pcSerial) {
    this->acceptedDate = "00:00:00";
    this->currentSetDate = "00:00:00";
}

void TimeTemplate::handleEnter() {
    if (this->isDateValid()) {
        this->timeAccepted = true;
        this->acceptedDate = this->currentSetDate;
        this->getPcSerial()->println();
    }
}

void TimeTemplate::handleBackspace() {
    if (this->currentSetDate.length() > 0) {
        CustomSoftwareSerial* pcSerial = this->getPcSerial();
        clearPreviousLine(pcSerial);
        this->currentSetDate.remove(this->currentSetDate.length() - 1);
        pcSerial->print(this->currentSetDate);
    }
}

void TimeTemplate::handleChange(uint8_t readed) {
    if (this->currentSetDate.length() > 7) {
        this->currentSetDate = "";
    }
    this->currentSetDate.concat((char)readed);
}

void TimeTemplate::handleBeforeSent() { this->timeAccepted = false; }

String TimeTemplate::getCurrentSetDate() { return this->currentSetDate; }
String TimeTemplate::getAcceptedDate() { return this->acceptedDate; }

boolean TimeTemplate::isDateValid() {
    return this->currentSetDate.length() == 8 &&
           this->currentSetDate.charAt(this->POSITION_OF_FIRST_SEMICOLON) ==
               ':' &&
           this->currentSetDate.charAt(this->POSITION_OF_SECOND_SEMICOLON) ==
               ':' &&
           this->getHours(this->currentSetDate) < 24 &&
           this->getMinutes(this->currentSetDate) < 60 &&
           this->getSeconds(this->currentSetDate) < 60;
}

boolean TimeTemplate::isTimeAccepted() { return this->timeAccepted; }

uint8_t TimeTemplate::getHours(String date) {
    date.remove(this->POSITION_OF_FIRST_SEMICOLON);
    return date.toInt();
}

uint8_t TimeTemplate::getMinutes(String date) {
    date.remove(0, this->POSITION_OF_FIRST_SEMICOLON + 1);
    date.remove(this->POSITION_OF_SECOND_SEMICOLON);
    return date.toInt();
}

uint8_t TimeTemplate::getSeconds(String date) {
    date.remove(0, this->POSITION_OF_SECOND_SEMICOLON + 1);
    return date.toInt();
}

uint8_t TimeTemplate::getAcceptedTimeSeconds() {
    return this->getSeconds(this->acceptedDate);
}

uint8_t TimeTemplate::getAcceptedTimeMinutes() {
    return this->getMinutes(this->acceptedDate);
}
uint8_t TimeTemplate::getAcceptedTimeHours() {
    return this->getHours(this->acceptedDate);
}

void TimeTemplate::startSettingNewDate() {
    this->currentSetDate = "";
    this->timeAccepted = false;
}