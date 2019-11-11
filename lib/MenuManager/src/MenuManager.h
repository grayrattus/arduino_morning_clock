#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <Arduino.h>
#include <SerialInputOutputTemplate.h>
#include <CustomSoftwareSerial.h>
#include <TMRpcm.h>
#include <WString.h>

enum MenuCommands { MENU, PRING, PSET, CSET, NONE_PRINT };

class MenuManager: public SerialInputOutputTemplate {
   public:
    MenuManager(CustomSoftwareSerial* pcSerial);
    static MenuCommands getCommand(String inputCommand);
    MenuCommands getCurrentCommand();
    String getUserOutputForCommand();
    void setMenuCommand(MenuCommands command);
    virtual void handleEnter();
    virtual void handleBackspace();
    virtual void handleChange(uint8_t readed);

   private:
    MenuCommands currentCommand;
    String currentInputMenu = "";
    String outputMenuString = "Menu description";
    String outputInputDateString = "Put date:";
    String outputRighDateString = "Showing ring date";
    void setCurrentCommand(String inputCommand);
};

#endif