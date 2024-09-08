#ifndef COMMAND_H
#define COMMAND_H
#include <ncurses.h>

#include <map>
#include <stack>

#include "document.h"

using namespace std;

class Document;

enum class TypeOfCommand {
    Navigation,
    Clipboard,
    Editing,
    Macro,
    File,
    Search,
    Scroll,
    Insert,
    Undo,
    Dot,
    Semicolon,
    Undefined,
    Enter,
    Backspace,
    Escape,
    CtrlG
};

class Command {
    TypeOfCommand cmd;
    bool undo;

    protected:
    Document *display;
    virtual void executeCommand() = 0;
    
    public:
    Command(TypeOfCommand tpe, bool undo, Document *display): cmd{tpe}, undo{undo}, display{display} {}
    void manageCommand();
    virtual ~Command() = default;


};
#endif
