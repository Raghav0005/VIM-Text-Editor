#include "command.h"
#include <string>

using namespace std;

class Insert : public Command {
    string c;
    public:
    Insert(string c, Document *document);
    void executeCommand() override;
};

class Enter : public Command {
    public:
    Enter(Document *document);
    void executeCommand() override;
};

class Backspace : public Command {
    public:
    Backspace(Document *document);
    void executeCommand() override;
};

class Escape : public Command {
    public:
    Escape(Document *document);
    void executeCommand() override;
};

class InvalidCommand : public Command {
 public:
  InvalidCommand(Document *doc) : Command(TypeOfCommand::Undefined, false, doc) {}
  void executeCommand() override {}
};

