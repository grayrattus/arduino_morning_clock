#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

#include <Arduino.h>
#include <SerialInputOutputTemplate.h>
#include <CustomSoftwareSerial.h>
#include <TMRpcm.h>
#include <WString.h>
#include <TimeTemplate.h>
#include <RTClib.h>

class ClockManager: public TimeTemplate {
   public:
    ClockManager(RTC_DS1307* rtc, CustomSoftwareSerial* pcSerial);
    void sendSetDateToClock();
   private:
    RTC_DS1307* rtc;
};

#endif