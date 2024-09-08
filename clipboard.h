#include "command.h"

class Clipboard: public Command {
    public:
    Clipboard(Document *document, bool undo);
    void executeCommand() override;
    virtual void manageClipboard() = 0;
};

class xCommand: public Clipboard {
    public:
    xCommand(Document *document): Clipboard(document, false) {}
    void manageClipboard() override;
};

class XCommand: public Clipboard {
    public:
    XCommand(Document *document): Clipboard(document, false) {}
    void manageClipboard() override;
};

class pCommand: public Clipboard {
    public:
    pCommand(Document *document): Clipboard(document, true) {}
    void manageClipboard() override;
};

class PCommand: public Clipboard {
    public:
    PCommand(Document *document): Clipboard(document, true) {}
    void manageClipboard() override;
};

class yyCommand: public Clipboard {
    public:
    yyCommand(Document *document): Clipboard(document, true) {}
    void manageClipboard() override;
};

class yDollarCommand: public Clipboard {
    public:
    yDollarCommand(Document *document): Clipboard(document, true) {}
    void manageClipboard() override;
};

class yhCommand: public Clipboard {
    public:
    yhCommand(Document *document): Clipboard(document, true) {}
    void manageClipboard() override;
};

class ylCommand: public Clipboard {
    public:
    ylCommand(Document *document): Clipboard(document, true) {}
    void manageClipboard() override;
};

class yjCommand: public Clipboard {
    public:
    yjCommand(Document *document): Clipboard(document, true) {}
    void manageClipboard() override;
};

class ykCommand: public Clipboard {
    public:
    ykCommand(Document *document): Clipboard(document, true) {}
    void manageClipboard() override;
};

class yChevron: public Clipboard {
    public:
    yChevron(Document *document): Clipboard(document, true) {}
    void manageClipboard() override;
};

class yZero: public Clipboard {
    public:
    yZero(Document *document): Clipboard(document, true) {}
    void manageClipboard() override;
};
