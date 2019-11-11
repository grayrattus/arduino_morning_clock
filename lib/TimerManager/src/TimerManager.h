#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <Arduino.h>
#include <TimeTemplate.h>
#include <CustomSoftwareSerial.h>
#include <TMRpcm.h>
#include <WString.h>

class TimerManager : public TimeTemplate {
   public:
    TimerManager(TMRpcm* tmrpcm, CustomSoftwareSerial* pcSerial);
    void ring(uint8_t hours, uint8_t minutes, uint8_t seconds);
   private:
    uint8_t playbackTime = 0;
    String fileName;
    TMRpcm* tmrpcm;
    boolean shouldPlay = false;
};
#endif
