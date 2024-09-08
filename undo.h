#include "command.h"

class Undo: public Command {
    public:
    Undo(Document *document): Command(TypeOfCommand::Undo, false, document) {}
    void executeCommand() override {
        display->doUndo();
    }
};
