#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <map>
#include <ncurses.h>

using namespace std;

class Document;
class Command;

class Keyboard {
    string input = "";
    inline static shared_ptr<Command> lastCommand = nullptr;
    //inline static shared_ptr<Command> lastFCommand = nullptr;
    //inline static shared_ptr<Command> lastfCommand = nullptr;
    inline static map<string, queue<shared_ptr<Command>>> macros = map<string, queue<shared_ptr<Command>>>();
    inline static bool macroOn = false;
    inline static queue<shared_ptr<Command>> commandsMacro;
    inline static string macroRegister = "";
    inline static string lastKey = "";
    

    shared_ptr<Command> Nav(Document *document);
    shared_ptr<Command> navWithInsert(Document *document);
    shared_ptr<Command> clipboardCommands(Document *document);
    shared_ptr<Command> colonCommands(Document *document, WINDOW *window, WINDOW *statusBar);
    shared_ptr<Command> editingCommands(Document *document);
    shared_ptr<Command> searchCommands(Document *document, WINDOW *window, WINDOW *statusBar);
    shared_ptr<Command> macroCommands(Document *document);

    public:
    
    Keyboard() = default;
    Keyboard(char c);
    Keyboard(const string &str);
    shared_ptr<Command> convert(Document *document, WINDOW *window, WINDOW *statusBar);
    ~Keyboard() = default;
};

#endif
