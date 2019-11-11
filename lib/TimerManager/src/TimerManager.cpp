#include "TimerManager.h"
#include "Constants.h"

TimerManager::TimerManager(TMRpcm* tmrpcm, CustomSoftwareSerial* pcSerial)
    : TimeTemplate(pcSerial) {
    this->tmrpcm = tmrpcm;
    this->fileName = "test.wav";
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
        this->tmrpcm->play(this->fileName.begin());
    }
}
