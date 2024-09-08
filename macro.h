#include "command.h"
#include <string>
#include <queue>
#include <memory>

using namespace std;

class Macro: public Command {
    public:
    Macro(Document *document);
    void executeCommand() override;
    virtual void manageMacro() = 0;
};

class qRegister: public Macro {
    string key;

    public:
    qRegister(Document *document);
    void manageMacro() override;
};

class qCommand: public Macro {
    string currentKey;
    queue<shared_ptr<Command>> commandsQueue;
    
    public:
    qCommand(Document *document);
    void manageMacro() override;
};

class atRegister: public Macro {
    queue<shared_ptr<Command>> commandsQueue;

    public:
    atRegister(Document *document, queue<shared_ptr<Command>> commandsQueue);
    void manageMacro() override;
};
