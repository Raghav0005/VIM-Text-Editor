#include "macro.h"
#include <iostream>

Macro::Macro(Document *document): Command(TypeOfCommand::Macro, false, document) {}

void Macro::executeCommand() {
    manageMacro();
}

qRegister::qRegister(Document *document): Macro(document) {}

qCommand::qCommand(Document *document): Macro(document) {}

atRegister::atRegister(Document *document, queue<shared_ptr<Command>> commandsQueue): Macro(document), commandsQueue{commandsQueue} {}

void qRegister::manageMacro() {}

void qCommand::manageMacro() {}

void atRegister::manageMacro() {
    while (!commandsQueue.empty()) {
        shared_ptr<Command> commandPtr = commandsQueue.front();
        commandsQueue.pop();
        if (commandPtr) {
            commandPtr->manageCommand();
        }
    }
}
