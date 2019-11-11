#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <Arduino.h>
#include <SerialInputOutputTemplate.h>
#include <SoftwareSerial.h>
#include <TMRpcm.h>
#include <WString.h>

class TimerManager : public SerialInputOutputTemplate {
   public:
    TimerManager(TMRpcm* tmrpcm, SoftwareSerial* pcSerial);
    String getCurrentSetDate();
    String getAcceptedDate();
    boolean isDateValid();
    uint8_t getAcceptedTimeSeconds();
    uint8_t getAcceptedTimeMinutes();
    uint8_t getAcceptedTimeHours();
    void ring(uint8_t hours, uint8_t minutes, uint8_t seconds);
    boolean isTimeAccepted();
    void startSettingNewDate();
    virtual void handleEnter();
    virtual void handleBackspace();
    virtual void handleChange(uint8_t readed);
    virtual void handleBeforeSent();

   private:
    uint8_t playbackTime = 0;
    String currentSetDate ;
    String acceptedDate;
    String fileName;
    const uint8_t POSITION_OF_FIRST_SEMICOLON = 2;
    const uint8_t POSITION_OF_SECOND_SEMICOLON = 5;
    TMRpcm* tmrpcm;
    boolean shouldPlay = false;
    boolean timeAccepted = false;
    uint8_t getMinutes(String date);
    uint8_t getSeconds(String date);
    uint8_t getHours(String date);
};
#endif
