#include "command.h"

class File: public Command {
    protected:
    Document *document;

    public:
    File(Document *document): Command(TypeOfCommand::File, false, document), document{document} {}
    void executeCommand() override;
    virtual void manageFile() = 0;
};

class WriteCommand: public File {
    public:
    WriteCommand(Document *document): File(document) {}
    void manageFile() override;
};

class WriteandQuitCommand: public File {
    public:
    WriteandQuitCommand(Document *document): File(document) {}
    void manageFile() override;
};

class QuitCommand: public File {
    public:
    QuitCommand(Document *document): File(document) {}
    void manageFile() override;
};

class ForceQuitCommand: public File {
    public:
    ForceQuitCommand(Document *document): File(document) {}
    void manageFile() override;
};

class ReadCommand: public File {
    string newFileName;
    public:
    ReadCommand(Document *document, string newFileName): File(document), newFileName{newFileName} {}
    void manageFile() override;
};
