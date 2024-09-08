#include "command.h"

class Scroll: public Command {
    protected:
    size_t windowSize;
    size_t &tpLine;
    public:
    Scroll(Document *document): Command(TypeOfCommand::Scroll, false, document), windowSize{document->windowSize}, tpLine{document->topLine} {}
    void executeCommand() override;
    virtual void manageScroll() = 0;
};

class CtrlBCommand: public Scroll {
    public:
    CtrlBCommand(Document *document): Scroll(document) {}
    void manageScroll() override;
};

class CtrlDCommand: public Scroll {
    public:
    CtrlDCommand(Document *document): Scroll(document) {}
    void manageScroll() override;
};

class CtrlFCommand: public Scroll {
    public:
    CtrlFCommand(Document *document): Scroll(document) {}
    void manageScroll() override;
};

class CtrlUCommand: public Scroll {
    public:
    CtrlUCommand(Document *document): Scroll(document) {}
    void manageScroll() override;
};

