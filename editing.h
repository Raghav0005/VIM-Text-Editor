#include "command.h"

class Editing: public Command {
    public:
    Editing(Document *document);
    void executeCommand() override;
    virtual void manageEditing() = 0;
};

class sCommand: public Editing {
    public:
    sCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class oCommand: public Editing {
    public:
    oCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class OCommand: public Editing {
    public:
    OCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class JCommand: public Editing {
    public:
    JCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class rcCommand: public Editing {
    char character;
    public:
    rcCommand(Document *document, char character): Editing(document), character{character} {}
    void manageEditing() override;
};

class SCommand: public Editing { //  same as ccCommand
    public:
    SCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class ddCommand: public Editing {
    public:
    ddCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class cDollarCommand: public Editing {
    public:
    cDollarCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class dwCommand: public Editing {
    public:
    dwCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class cwCommand: public Editing {
    public:
    cwCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class dDollarCommand: public Editing {
    public:
    dDollarCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class dlCommand: public Editing {
    public:
    dlCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class dhCommand: public Editing {
    public:
    dhCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class dkCommand: public Editing {
    public:
    dkCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class djCommand: public Editing {
    public:
    djCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

// ch and cl same as dh and dl, respectively

class ckCommand: public Editing {
    public:
    ckCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class cjCommand: public Editing {
    public:
    cjCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class dChevronCommand: public Editing {
    public:
    dChevronCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

class dZeroCommand: public Editing {
    public:
    dZeroCommand(Document *document): Editing(document) {}
    void manageEditing() override;
};

