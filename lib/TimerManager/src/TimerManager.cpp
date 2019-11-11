#include "TimerManager.h"
#include "Constants.h"

TimerManager::TimerManager(TMRpcm* tmrpcm, SoftwareSerial* pcSerial) {
    this->tmrpcm = tmrpcm;
    this->pcSerial = pcSerial;
}

void TimerManager::setDateIfSerialAvailable() {
    if (this->pcSerial->available() > 0) {
        uint8_t readed = this->pcSerial->read();
        this->timeAccepted = false;
        this->pcSerial->print((char)readed);
        if (readed == ASCII_NEW_LINE || readed == ASCII_LINE_FEED) {
            if (this->isDateValid()) {
                this->timeAccepted = true;
                this->acceptedDate = this->currentSetDate;
                this->pcSerial->println();
            }
        } else if (readed == ASCII_BACKSPACE) {
            if (this->currentSetDate.length() > 0) {
                this->pcSerial->print((char)ASCII_LINE_FEED);
                this->currentSetDate.remove(this->currentSetDate.length() - 1);
                this->pcSerial->print("        ");
                this->pcSerial->print((char)ASCII_LINE_FEED);
                this->pcSerial->print(this->currentSetDate);
            }
        } else {
            if (this->currentSetDate.length() > 8) {
                this->currentSetDate = "";
            }
            this->currentSetDate.concat((char)readed);
        }
    }
}

String TimerManager::getCurrentSetDate() { return this->currentSetDate; }
String TimerManager::getAcceptedDate() { return this->acceptedDate; }

boolean TimerManager::isDateValid() {
    return this->currentSetDate.length() == 8 &&
           this->currentSetDate.charAt(this->POSITION_OF_FIRST_SEMICOLON) ==
               ':' &&
           this->currentSetDate.charAt(this->POSITION_OF_SECOND_SEMICOLON) ==
               ':' &&
           this->getHours(this->currentSetDate) < 24 &&
           this->getMinutes(this->currentSetDate) < 60 &&
           this->getSeconds(this->currentSetDate) < 60;
}

boolean TimerManager::isTimeAccepted() { return this->timeAccepted; }

uint8_t TimerManager::getHours(String date) {
    date.remove(this->POSITION_OF_FIRST_SEMICOLON);
    return date.toInt();
}

uint8_t TimerManager::getMinutes(String date) {
    date.remove(0, this->POSITION_OF_FIRST_SEMICOLON + 1);
    date.remove(this->POSITION_OF_SECOND_SEMICOLON);
    return date.toInt();
}

uint8_t TimerManager::getSeconds(String date) {
    date.remove(0, this->POSITION_OF_SECOND_SEMICOLON + 1);
    return date.toInt();
}

uint8_t TimerManager::getAcceptedTimeSeconds() {
    return this->getSeconds(this->acceptedDate);
}

uint8_t TimerManager::getAcceptedTimeMinutes() {
    return this->getMinutes(this->acceptedDate);
}
uint8_t TimerManager::getAcceptedTimeHours() {
    return this->getHours(this->acceptedDate);
}

void TimerManager::ring(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    if (shouldPlay) {
        this->playbackTime++;
        if (this->playbackTime == 40) {
            this->playbackTime = 0;
            this->shouldPlay = false;
            tmrpcm->disable();
        }
    } else if (this->getAcceptedTimeHours() == hours &&
               this->getAcceptedTimeMinutes() == minutes &&
               this->getAcceptedTimeSeconds() == seconds &&
               this->shouldPlay == false) {
        this->shouldPlay = true;
        if (this->tmrpcm->isPlaying()) {
            this->tmrpcm->stopPlayback();
            this->playbackTime = 0;
        }
        this->tmrpcm->setVolume(5);
        this->tmrpcm->play("bonito.wav");
    }
}

void TimerManager::startSettingNewDate() {
    this->currentSetDate = "";
    this->timeAccepted = false;
}