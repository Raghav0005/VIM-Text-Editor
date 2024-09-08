#include "command.h"

void Command::manageCommand() {
    if (undo) {
        display->undoPush(*display);
        display->saved = false;
    }
    executeCommand();
}
