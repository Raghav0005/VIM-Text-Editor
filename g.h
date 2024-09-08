#include "command.h"
#include "ncurses.h"

class CtrlG: public Command {
    Document *document;
    public:
    CtrlG(Document *document): Command(TypeOfCommand::CtrlG, false, document), document{document} {}
    void executeCommand() override {
        document->ctrlgPressed = true;
    }
};
