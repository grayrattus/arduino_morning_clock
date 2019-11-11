#include "ClockManager.h"
#include "Constants.h"

ClockManager::ClockManager(RTC_DS1307* rtc, CustomSoftwareSerial* pcSerial)
    : TimeTemplate(pcSerial) {
    this->rtc = rtc;
}

void ClockManager::sendSetDateToClock() {
    this->rtc->adjust(DateTime(0, 0, 0, this->getAcceptedTimeHours(),
                               this->getAcceptedTimeMinutes(),
                               this->getAcceptedTimeSeconds()));
};
