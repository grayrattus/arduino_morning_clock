#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <WString.h>
#include <Arduino.h>
#include <TMRpcm.h>

class TimerManager {
    public:
        TimerManager(TMRpcm* tmrpcm);
        void setDateIfSerialAvailable();
        String getCurrentSetDate();
        boolean isDateValid();
        uint8_t getMinutes();
        uint8_t getSeconds();
        uint8_t getHours();
        void ring(uint8_t hours, uint8_t minutes, uint8_t seconds);
    private:
        uint8_t playbackTime = 0;
        String currentSetDate = "00:00:00";
        const uint8_t POSITION_OF_FIRST_SEMICOLON = 2;
        const uint8_t POSITION_OF_SECOND_SEMICOLON = 5;
        TMRpcm* tmrpcm;
        boolean shouldPlay = false;
};
#endif
