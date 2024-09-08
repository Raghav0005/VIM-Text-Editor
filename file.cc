#include "file.h"
#include <fstream>

void File::executeCommand() { manageFile(); }

void WriteCommand::manageFile() {
    if (document->filename != "") {
        document->saveToFile(document->filename);
        document->saved = true;
    }
}

void WriteandQuitCommand::manageFile() {
    document->saveToFile(document->filename);
    document->saved = true;
    document->quit = true;
}

void QuitCommand::manageFile() {
    if (document->saved) {
        document->quit = true;
    }
}

void ForceQuitCommand::manageFile() {
    document->quit = true;
}

void ReadCommand::manageFile() {
    
    size_t l = display->currentCursor.line;
    ifstream f{newFileName};
    string line;
    while (getline(f, line)) {
        display->content.insert(display->content.begin() + ++l, line);
    }
    display->currentCursor.line++;
    display->currentCursor.column = 0;
    
    document->saved = true;
}
