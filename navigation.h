#include "command.h"
#include <map>
#include <string>

class Navigation : public Command {
    protected:
    size_t &column; // this is using references - any modification will impact the actual currentCursor value
    size_t &line; // this is using references - any modification will impact the actual currentCursor value

    public:
    Navigation(Document *document);
    void executeCommand() override; // whenever this command gets executed,
    // it ends up calling the manageNavigation command, which is virtual for its own subclasses
    virtual void manageNavigation() = 0;
};

class iCommand: public Navigation {
    public:
    iCommand(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class hCommand: public Navigation {
    public:
    hCommand(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class jCommand: public Navigation {
    public:
    jCommand(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class kCommand: public Navigation {
    public:
    kCommand(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class lCommand: public Navigation {
    public:
    lCommand(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class aCommand: public Navigation {
    public:
    aCommand(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class Dollar: public Navigation {
    public:
    Dollar(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class Chevron: public Navigation {
    public:
    Chevron(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class ZeroCommand: public Navigation {
    public:
    ZeroCommand(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class bCommand: public Navigation {
    public:
    bCommand(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class wCommand: public Navigation {
    public:
    wCommand(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class ColonFirstLine: public Navigation {
    public:
    ColonFirstLine(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class ColonLastLine: public Navigation {
    public:
    ColonLastLine(Document *document): Navigation(document) {}
    void manageNavigation() override;
};

class ColonSpecificLine: public Navigation {
    size_t lineToNavigate;
    size_t lengthOfFile;

    public:
    ColonSpecificLine(Document *document, size_t lineToNavigate, size_t lengthOfFile): 
    Navigation(document), lineToNavigate(lineToNavigate), lengthOfFile(lengthOfFile) {}
    void manageNavigation() override;
};

class fcCommand: public Navigation {
    char character;
    public:
    fcCommand(Document *document, char character): Navigation(document), character{character} {}
    void manageNavigation() override;
};

class FcCommand: public Navigation {
    char character;
    public:
    FcCommand(Document *document, char character): Navigation(document), character{character} {}
    void manageNavigation() override;
};

class Percent: public Navigation {
    const map<char, char> forward = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
    const map<char, char> backward = {{')', '('}, {']', '['}, {'}', '{'}};

    public:
    Percent(Document *document): Navigation(document) {}
    void manageNavigation() override;
};
