#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <WString.h>
#include <Arduino.h>
#include <TMRpcm.h>
#include <SoftwareSerial.h>

class TimerManager {
    public:
        TimerManager(TMRpcm* tmrpcm, SoftwareSerial* pcSerial);
        void setDateIfSerialAvailable();
        String getCurrentSetDate();
        String getAcceptedDate();
        boolean isDateValid();
        uint8_t getAcceptedTimeSeconds();
        uint8_t getAcceptedTimeMinutes();
        uint8_t getAcceptedTimeHours();
        void ring(uint8_t hours, uint8_t minutes, uint8_t seconds);
        boolean isTimeAccepted();
        void startSettingNewDate();
    private:
        uint8_t playbackTime = 0;
        String currentSetDate = "00:00:00";
        String acceptedDate = "00:00:00";
        const uint8_t POSITION_OF_FIRST_SEMICOLON = 2;
        const uint8_t POSITION_OF_SECOND_SEMICOLON = 5;
        TMRpcm* tmrpcm;
        SoftwareSerial* pcSerial;
        boolean shouldPlay = false;
        boolean timeAccepted = false;
        uint8_t getMinutes(String date);
        uint8_t getSeconds(String date);
        uint8_t getHours(String date);
};
#endif
