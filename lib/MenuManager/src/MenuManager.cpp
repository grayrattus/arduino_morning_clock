#include "MenuManager.h"

MenuManager::MenuManager(SoftwareSerial* pcSerial) {
    this->pcSerial = pcSerial;
    this->currentCommand = MenuCommands::MENU;
}

void MenuManager::setMenuCommandIfSerialAvailable() {
    if (this->pcSerial->available() > 0) {
        uint8_t readed = this->pcSerial->read();
        this->pcSerial->print((char)readed);
        if (readed == 13 || readed == 10) {
            this->setCurrentCommand(this->currentInputMenu);
            this->currentInputMenu = "";
        } else if (readed == 8) {
            if (this->currentInputMenu.length() > 0) {
                this->pcSerial->print((char)13);
                this->currentInputMenu.remove(this->currentInputMenu.length() -
                                              1);
                this->pcSerial->print("       ");
                this->pcSerial->print((char)13);
                this->pcSerial->print(this->currentInputMenu);
            }
        } else {
            this->currentInputMenu.concat((char)readed);
        }
    }
}

MenuCommands MenuManager::getCommand(String inputCommand) {
    if (inputCommand.compareTo("menu") == 0) {
        return MENU;
    } else if (inputCommand.compareTo("pring") == 0) {
        return PRING;
    } else if (inputCommand.compareTo("pset") == 0) {
        return PSET_DATE;
    }
    return MenuCommands::NONE_PRINT;
}

MenuCommands MenuManager::getCurrentCommand() { return this->currentCommand; }

void MenuManager::setMenuCommand(MenuCommands command) {
    this->currentCommand = command;
}

void MenuManager::setCurrentCommand(String inputCommand) {
    this->pcSerial->println("Set command:" + inputCommand);
    this->setMenuCommand(this->getCommand(inputCommand));
}

String MenuManager::getUserOutputForCommand() {
    switch (this->currentCommand) {
        case (MenuCommands::MENU):
            return this->outputMenuString;
            break;
        case (MenuCommands::PSET_DATE):
            return this->outputInputDateString;
            break;
        case (MenuCommands::PRING):
            return this->outputRighDateString;
            break;
    }
    return "";
}
