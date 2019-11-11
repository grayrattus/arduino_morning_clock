#ifndef TIME_TEMPLATE_H
#define TIME_TEMPLATE_H

#include <Arduino.h>
#include <SerialInputOutputTemplate.h>
#include <CustomSoftwareSerial.h>
#include <TMRpcm.h>
#include <WString.h>

class TimeTemplate : public SerialInputOutputTemplate {
   public:
    TimeTemplate(CustomSoftwareSerial* pcSerial);
    String getCurrentSetDate();
    String getAcceptedDate();
    boolean isDateValid();
    uint8_t getAcceptedTimeSeconds();
    uint8_t getAcceptedTimeMinutes();
    uint8_t getAcceptedTimeHours();
    boolean isTimeAccepted();
    void startSettingNewDate();
    virtual void handleEnter();
    virtual void handleBackspace();
    virtual void handleChange(uint8_t readed);
    virtual void handleBeforeSent();

   private:
    String currentSetDate ;
    String acceptedDate;
    boolean timeAccepted = false;
    const uint8_t POSITION_OF_FIRST_SEMICOLON = 2;
    const uint8_t POSITION_OF_SECOND_SEMICOLON = 5;
    uint8_t getMinutes(String date);
    uint8_t getSeconds(String date);
    uint8_t getHours(String date);
};
#endif
