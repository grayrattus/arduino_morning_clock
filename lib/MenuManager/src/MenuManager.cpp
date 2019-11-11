#include "MenuManager.h"
#include "Constants.h"
#include "SerialInputOutputTemplate.h"

MenuManager::MenuManager(CustomSoftwareSerial* pcSerial)
    : SerialInputOutputTemplate(pcSerial) {
    this->currentCommand = MenuCommands::NONE_PRINT;
}

void MenuManager::handleEnter() {
    this->setCurrentCommand(this->currentInputMenu);
    this->currentInputMenu = "";
}

void MenuManager::handleBackspace() {
    if (this->currentInputMenu.length() > 0) {
        CustomSoftwareSerial* pcSerial = this->getPcSerial();
        clearPreviousLine(pcSerial);
        currentInputMenu.remove(this->currentInputMenu.length() - 1);
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
    } else if (inputCommand.compareTo("cset") == 0) {
        return MenuCommands::CSET;
    }
    return MenuCommands::NONE_PRINT;
}

MenuCommands MenuManager::getCurrentCommand() { return this->currentCommand; }

void MenuManager::setMenuCommand(MenuCommands command) {
    this->currentCommand = command;
}

void MenuManager::setCurrentCommand(String inputCommand) {
    this->getPcSerial()->println();
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
    }
    return "";
}
