#include "TimerManager.h"

TimerManager::TimerManager(TMRpcm* tmrpcm) { this->tmrpcm = tmrpcm; }

void TimerManager::setDateIfSerialAvailable() {
    if (Serial.available() > 0) {
        // read the incoming byte:
        uint8_t readed = Serial.read();
        Serial.print(readed);
        if (this->currentSetDate.length() < 8) {
            if (readed == 8 && this->currentSetDate.length() > 0) {
                this->currentSetDate.remove(this->currentSetDate.length() - 1);
            } else {
                this->currentSetDate.concat((char)readed);
            }
        } else {
            this->currentSetDate = "";
            this->currentSetDate.concat((char)readed);
        }
    }
}

String TimerManager::getCurrentSetDate() { return this->currentSetDate; }

boolean TimerManager::isDateValid() {
    return this->currentSetDate.length() == 8 &&
           this->currentSetDate.charAt(this->POSITION_OF_FIRST_SEMICOLON) ==
               ':' &&
           this->currentSetDate.charAt(this->POSITION_OF_SECOND_SEMICOLON) ==
               ':' &&
           this->getHours() < 24 && this->getMinutes() < 60 &&
           this->getSeconds() < 60;
}

uint8_t TimerManager::getHours() {
    String date = this->currentSetDate;
    date.remove(this->POSITION_OF_FIRST_SEMICOLON);
    return date.toInt();
}

uint8_t TimerManager::getMinutes() {
    String date = this->currentSetDate;
    date.remove(0, this->POSITION_OF_FIRST_SEMICOLON + 1);
    date.remove(this->POSITION_OF_SECOND_SEMICOLON);
    return date.toInt();
}

uint8_t TimerManager::getSeconds() {
    String date = this->currentSetDate;
    date.remove(0, this->POSITION_OF_SECOND_SEMICOLON + 1);
    return date.toInt();
}
void TimerManager::ring(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    if (shouldPlay) {
        this->playbackTime++;
        if (this->playbackTime == 20) {
            this->playbackTime = 0;
            this->shouldPlay = false;
            tmrpcm->stopPlayback();
        }
    }
    if (this->getHours() == hours && this->getMinutes() == minutes &&
        this->getSeconds() == seconds) {
        this->shouldPlay = true;
        this->tmrpcm->volume(5);
        this->tmrpcm->play("bonito.wav");
    }
}