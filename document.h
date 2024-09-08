#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <ncurses.h>

#include <cstddef>
#include <string>
#include <vector>

#include "command.h"

using namespace std;

class Command;

struct Posn {
    size_t column;
    size_t line;
};

class Document {
    bool commandMode = true;
    inline static stack<Document> undoHistory;

    string clipboard;
    string search;

    public:
    vector<string> content = {""};
    Posn currentCursor = {0,0};
    size_t topLine = 1;
    
    bool copyLine = false;
    bool copyMultiple = false;
    bool searchForward = true;
    bool saved = true;
    bool quit = false;
    bool ctrlgPressed = false;

    string intermediateCommand = "";
    string filename;
    size_t windowSize;

    Document(const string& fname = "", size_t windowSize = 1) : filename(fname), windowSize{windowSize} {
        if (!filename.empty()) {
            loadFromFile(filename);
        }
    }
    Document(const Document &other);
    Document& operator=(Document other);

    void setClipboard(const string &str) { clipboard = str; }
    string &getClipboard() { return clipboard; }

    void updateContent(WINDOW *window, WINDOW *statusBar, int max_x, int max_y);
    
    void setCommandMode(bool commandMode);
    bool getCommandMode() const;

    string getSearch() const { return search; }
    void setSearch(const string &str) {search = str;}

    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);

    void undoPush(Document d);
    void doUndo();

    void printInfo(WINDOW *statusBar);

    ~Document() = default;
};
#endif
