#ifndef SERIAL_INPUT_OUTPUT_TEMPLATE_H_H
#define SERIAL_INPUT_OUTPUT_TEMPLATE_H_H

#include <Arduino.h>
#include <CustomSoftwareSerial.h>
#include <TMRpcm.h>
#include <WString.h>

class SerialInputOutputTemplate {
   public:
    SerialInputOutputTemplate(CustomSoftwareSerial* pcSerial);
    void setIfSerialAvailable();
    virtual void handleEnter();
    virtual void handleBackspace();
    virtual void handleChange(uint8_t readed);
    virtual void handleBeforeSent();
    CustomSoftwareSerial* getPcSerial();
   private:
    CustomSoftwareSerial* pcSerial;
};

#endif