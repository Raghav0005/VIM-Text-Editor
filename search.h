#include "command.h"

class Search: public Command {
    public:
    Search(Document *document);
    void executeCommand() override;
    virtual void manageSearch() = 0;
};

class Slash: public Search {
    string pattern;
    public:
    Slash(Document *document, const string &pattern):
    Search(document), pattern{pattern} {
        display->setSearch(pattern);
        display->searchForward = true;
    }
    void manageSearch() override;    
};

class Question: public Search {
    string pattern;
    public:
    Question(Document *document, const string& pattern):
    Search(document), pattern{pattern} {
        display->setSearch(pattern);
        display->searchForward = false;
    }
    void manageSearch() override;
};

class nCommand: public Search {
    public:
    nCommand(Document *document): Search(document) {}
    void manageSearch() override;
};

class NCommand: public Search {
    public:
    NCommand(Document *document): Search(document) {}
    void manageSearch() override;
};

void searchBackward(const string &pattern, Document *display);
void searchForward(const string &pattern, Document *display);
