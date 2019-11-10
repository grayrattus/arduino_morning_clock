#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TMRpcm.h>
#include <WString.h>

enum MenuCommands { MENU, PRING, PSET_DATE, NONE_PRINT };

class MenuManager {
   public:
    MenuManager(SoftwareSerial* pcSerial);
    static MenuCommands getCommand(String inputCommand);
    MenuCommands getCurrentCommand();
    String getUserOutputForCommand();
    void setMenuCommandIfSerialAvailable();
    void setMenuCommand(MenuCommands command);

   private:
    MenuCommands currentCommand;
    String currentInputMenu = "";
    String outputMenuString = "Menu description";
    String outputInputDateString = "Put date:";
    String outputRighDateString = "Showing ring date";
    void setCurrentCommand(String inputCommand);
    SoftwareSerial* pcSerial;
};

#endif