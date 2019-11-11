#include "MenuManager.h"
#include "Constants.h"
#include "SerialInputOutputTemplate.h"

MenuManager::MenuManager(SoftwareSerial* pcSerial)
    : SerialInputOutputTemplate(pcSerial) {
    this->currentCommand = MenuCommands::NONE_PRINT;
}

void MenuManager::handleEnter() {
    this->setCurrentCommand(this->currentInputMenu);
    this->currentInputMenu = "";
}

void MenuManager::handleBackspace() {
    if (this->currentInputMenu.length() > 0) {
        SoftwareSerial* pcSerial = this->getPcSerial();
        pcSerial->print((char)ASCII_LINE_FEED);
        currentInputMenu.remove(this->currentInputMenu.length() - 1);
        pcSerial->print("       ");
        pcSerial->print((char)ASCII_LINE_FEED);
        pcSerial->print(this->currentInputMenu);
    }
}

void MenuManager::handleChange(uint8_t readed) {
    this->currentInputMenu.concat((char)readed);
}

MenuCommands MenuManager::getCommand(String inputCommand) {
    if (inputCommand.compareTo("menu") == 0) {
        return MenuCommands::MENU;
    } else if (inputCommand.compareTo("pring") == 0) {
        return MenuCommands::PRING;
    } else if (inputCommand.compareTo("pset") == 0) {
        return MenuCommands::PSET;
    }
    return MenuCommands::NONE_PRINT;
}

MenuCommands MenuManager::getCurrentCommand() { return this->currentCommand; }

void MenuManager::setMenuCommand(MenuCommands command) {
    this->currentCommand = command;
}

void MenuManager::setCurrentCommand(String inputCommand) {
    this->getPcSerial()->println("Set command:" + inputCommand);
    this->setMenuCommand(this->getCommand(inputCommand));
}

String MenuManager::getUserOutputForCommand() {
    switch (this->currentCommand) {
        case (MenuCommands::MENU):
            return this->outputMenuString;
            break;
        case (MenuCommands::PSET):
            return this->outputInputDateString;
            break;
        case (MenuCommands::PRING):
            return this->outputRighDateString;
            break;
    }
    return "";
}
